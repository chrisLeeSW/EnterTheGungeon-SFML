#include "stdafx.h"
#include "PilotWeapon.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"


PilotWeapon::PilotWeapon(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	SetType(Types::PilotWeapon);

	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponShoot.csv"));

	gun.SetTarget(&sprite);

	SetType(Types::PilotWeapon);

	SpriteGo::Reset();

	gun.Play("Idle");

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(2.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

}

void PilotWeapon::Init()
{
	player = PLAYER_MGR.GetPlayer();
	std::cout << sprite.getOrigin().x << std::endl;
}

void PilotWeapon::Release()
{
}

void PilotWeapon::Reset()
{
	player = PLAYER_MGR.GetPlayer();

}

void PilotWeapon::Update(float dt)
{
	Weapon::Update(dt);
	if (!player->isRolling())
	{
		gun.Update(dt);
		SetPosition(player->PlayerHandPos());
		SetOrigin(Origins::BL);

		sprite.setRotation(Utils::Angle(look));
		if (flipX) sprite.setRotation(FLIP_ANGLE_X + Utils::Angle(look));

		SetGunFlipx(player->GetFilpX());


		gunend.setPosition(gunPoint);
		gunPoint = position + look * sprite.getLocalBounds().width;

		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			gun.Play("Shoot");
			WEAPON_MGR.Shoot(bulletType, gunPoint, look);
		}

	}
}

void PilotWeapon::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
		window.draw(gunend);
}

void PilotWeapon::SetGunFlipx(bool flipX)
{

	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

}


void PilotWeapon::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	bulletType = (Bullet::Types)info->bulletType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}
