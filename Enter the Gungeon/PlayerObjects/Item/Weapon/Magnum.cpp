#include "stdafx.h"
#include "Magnum.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Enemy.h"

Magnum::Magnum(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	SetType(Types::Magnum);


	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");


	//SetScale(0.5f,0.5f);

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(1.f);
	gunend.setSize(sf::Vector2f{ 5,5 });



}

void Magnum::Init()
{
	//gun.Play("Idle");
}

void Magnum::Release()
{
}

void Magnum::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void Magnum::Update(float dt)
{
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

void Magnum::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(gunend);
}

void Magnum::SetGunFlipx(bool flipX)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Magnum::SetType(Weapon::Types t)
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

void Magnum::SetEnemy(Enemy* enemy)
{
	this->enemy = enemy;
	sprite.setOrigin(this->enemy->GetHandOrigin().x, this->enemy->GetHandOrigin().y);
}
