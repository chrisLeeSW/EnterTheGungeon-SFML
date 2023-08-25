#include "stdafx.h"
#include "EnemyShotGun.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Enemy.h"

EnemyShotGun::EnemyShotGun(const std::string& textureId, const std::string& n) : Weapon(textureId,n)
{



	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/ShotGunIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/ShotGunShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(2.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

	sortLayer = -1;

	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4 };
}

void EnemyShotGun::Init()
{
}

void EnemyShotGun::Release()
{
}

void EnemyShotGun::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void EnemyShotGun::Update(float dt)
{

	gun.Update(dt);
	SetOrigin(Origins::BL);
	SetPosition(enemy->GetPosition() + gunPos);

	float angle = Utils::Angle(monsterlook);
	sf::Vector2f gunOffset = Utils::RotateVector(gunOffset1, angle);

	monsterlook = Utils::Normalize(player->GetPosition() - enemy->GetPosition());


	SetGunFlipx(!enemy->GetFlipX());

	if (flipX)
	{
		gunOffset = Utils::RotateVector(gunOffset2, angle);
		angle += FLIP_ANGLE_X;
	}
	sprite.setRotation(angle);



	gunend.setPosition(gunPoint);
	gunPoint = enemy->GetPosition();
	gunPoint += gunOffset;

	if (enemy->GetEnemyState() == Enemy::State::Attack)
	{
		if (gun.GetCurrentClipId() != "Shoot")
		{
			gun.Play("Shoot");
		}

		if (gun.GetCurFrame() == 5)
		{
			state = Weapon::State::Shoot;
		}
	}
	else
	{
		gun.Play("Idle");
		state = Weapon::State::Idle;
	}
}


void EnemyShotGun::Draw(sf::RenderWindow& window)
{

	SpriteGo::Draw(window);
	window.draw(gunend);
}

void EnemyShotGun::SetGunFlipx(bool flipX)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

	gunPos.x = !this->flipX ? abs(gunPos.x) : -abs(gunPos.x);
}
