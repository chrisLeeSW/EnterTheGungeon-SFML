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


	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/WinchesterIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/WinchesterShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);


	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Transparent);
	gunend.setOutlineThickness(1.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

	sortLayer = -1;

	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 3 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 3 };
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
	SetPosition(enemy->GetPosition() + gunPos);
	SetOrigin(Origins::BL);

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

	gunPos.x = !this->flipX ? abs(gunPos.x) : -abs(gunPos.x);
}