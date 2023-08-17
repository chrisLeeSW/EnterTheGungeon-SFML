#include "stdafx.h"
#include "Winchester.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Enemy.h"

Winchester::Winchester(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	//SetType(Types::ShotGun);


	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/WinchesterIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/WinchesterShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);


	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(2.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4 };
}

void Winchester::Init()
{
}

void Winchester::Release()
{
}

void Winchester::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void Winchester::Update(float dt)
{
	//Weapon::Update(dt);


	gun.Update(dt);
	SetPosition(enemy->GetPosition());
	SetOrigin(Origins::BL);

	float angle = Utils::Angle(look);
	sf::Vector2f gunOffset = Utils::RotateVector(gunOffset1, angle);

	look = Utils::Normalize(player->GetPosition() - enemy->GetPosition());


	SetGunFlipx(!enemy->GetFlipX());

	if (flipX)
	{
		gunOffset = Utils::RotateVector(gunOffset2, angle);
		angle += FLIP_ANGLE_X;
	}
	sprite.setRotation(angle);

	//SetGunFlipx(player->GetFilpX());


	gunend.setPosition(gunPoint);
	gunPoint = enemy->GetPosition();
	gunPoint += gunOffset;



}


void Winchester::Draw(sf::RenderWindow& window)
{

	SpriteGo::Draw(window);
	window.draw(gunend);
}

void Winchester::SetGunFlipx(bool flipX)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Winchester::SetType(Types t)
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
