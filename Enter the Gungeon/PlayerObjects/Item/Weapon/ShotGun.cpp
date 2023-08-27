#include "stdafx.h"
#include "ShotGun.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "PlayerUI.h"

ShotGun::ShotGun(const std::string& textureId, const std::string& n)
{
	player = PLAYER_MGR.GetPlayer();

	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PlayerShotGunIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PlayerShotGunShoot.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PlayerShotGunReload.csv"));

	//effect.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotShootEffect.csv"));

	//effect.SetTarget(&shooteffect);

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Transparent);
	gunend.setOutlineThickness(2.f);
	gunend.setSize(sf::Vector2f{ 5,5 });


	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4 };

}

void ShotGun::Init()
{
	player = PLAYER_MGR.GetPlayer();
	SetType(Types::ShotGun);
	tick = attackrate;
	reloadtick = reload;
	currentbulletcount = bulletcount;
	currentbulletmax = bulletmax;
}

void ShotGun::Release()
{
}

void ShotGun::Reset()
{
}

void ShotGun::Update(float dt)
{
	Weapon::Update(dt);
	if (!player->isRolling())
	{
		SetOrigin(Origins::BL);
		gun.Update(dt);
		effect.Update(dt);


		SetPosition(player->PlayerHandPos());

		float angle = Utils::Angle(look);
		sf::Vector2f gunOffset = Utils::RotateVector(gunOffset1, angle);

		SetGunFlipx(player->GetFilpX());

		if (flipX)
		{
			gunOffset = Utils::RotateVector(gunOffset2, angle);
			angle += FLIP_ANGLE_X;
		}

		sprite.setRotation(angle);



		gunend.setPosition(gunPoint);
		gunPoint = player->PlayerHandPos();
		gunPoint += gunOffset;

		shooteffect.setOrigin(shooteffect.getLocalBounds().left, shooteffect.getLocalBounds().height / 2);
		shooteffect.setRotation(angle);
		shooteffect.setPosition(gunPoint);

		if (!isreload)
		{
			tick -= dt;

			if (INPUT_MGR.GetKeyDown(sf::Keyboard::R) && currentbulletcount != bulletcount && currentbulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Reload");
				reloadtick = 0.f;
				isreload = true;
				player->playerUI->ShootWeapon();

			}
			else if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && currentbulletcount == 0 && currentbulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Reload");
				reloadtick = 0.f;
				isreload = true;

			}

			if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && tick <= 0.f && currentbulletcount > 0 && currentbulletmax >= 0)
			{
				--currentbulletcount;
				--currentbulletmax;

				state = State::Shoot;

				gun.Play("Shoot");
				//effect.Play("Effect");
				for(int i = 0; i < 4; ++i)
				{
					player->Shoot(bulletType, gunPoint, look, santan * Utils::RandomValue());
				}


				tick = attackrate;
			}
			if (gun.GetCurrentClipId() == "Shoot" && gun.AnimationEnd())
			{
				gun.Play("Idle");
				state = State::Idle;
			}

		}
		else if (isreload)
		{
			reloadtick += dt; // 재장전 시간 감소
			if (reloadtick >= reload)
			{
				currentbulletcount = bulletcount; // 재장전 완료되면 탄창을 최대치로 채움
				player->playerUI->ShootWeapon();
				state = State::Idle;
				gun.Play("Idle");
				isreload = false; // 재장전 플래그 해제
			}
		}
	}
	else if (player->isRolling() && state == State::Reload)
	{
		reloadtick += dt; // 재장전 시간 감소
		if (reloadtick >= reload)
		{
			currentbulletcount = bulletcount; // 재장전 완료되면 탄창을 최대치로 채움
			player->playerUI->ShootWeapon();
			state = State::Idle;
			gun.Play("Idle");
			isreload = false; // 재장전 플래그 해제
		}
	}
}

void ShotGun::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
	window.draw(shooteffect);
	window.draw(gunend);
}
