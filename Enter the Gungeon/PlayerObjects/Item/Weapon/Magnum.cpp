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


	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Transparent);
	gunend.setOutlineThickness(1.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

	sortLayer = -1;

	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4 };

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
	gunPoint = enemy->GetPosition() + gunPos;
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
			enemy->SetIsShoot(true);
		}
	}
	else
	{
		gun.Play("Idle");
		state = Weapon::State::Idle;
		enemy->SetIsShoot(false);
	}

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

	gunPos.x = !this->flipX ? abs(gunPos.x) : -abs(gunPos.x);
}