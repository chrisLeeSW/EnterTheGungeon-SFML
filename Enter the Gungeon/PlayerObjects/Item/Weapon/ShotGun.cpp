#include "stdafx.h"
#include "ShotGun.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"

ShotGun::ShotGun(const std::string& textureId, const std::string& n)
{
	SetType(Types::ShotGun);
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
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(2.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

	tick = attackrate;
	reloadtick = reload;

	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4 };

	currentbulletcount = bulletcount;
	currentbulletmax = bulletmax;
}

void ShotGun::Init()
{
	player = PLAYER_MGR.GetPlayer();
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
			if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && tick <= 0.f && currentbulletcount > 0 && currentbulletmax >= 0)
			{
				--currentbulletcount;
				--currentbulletmax;

				state = State::Shoot;

				gun.Play("Shoot");
				effect.Play("Effect");
				player->Shoot(bulletType, gunPoint, look, santan);

				std::cout << "���� źâ : " << currentbulletcount << std::endl;
				std::cout << "�� źâ : " << currentbulletmax << std::endl;
				tick = attackrate;
			}
			if (gun.GetCurrentClipId() == "Shoot" && gun.AnimationEnd())
			{
				gun.Play("Idle");
				state = State::Idle;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::R) && currentbulletcount != bulletcount && currentbulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Reload");
				reloadtick = 0.f;
				isreload = true;
			}
		}
		else if (isreload)
		{
			reloadtick += dt; // ������ �ð� ����
			if (reloadtick >= reload)
			{
				currentbulletcount = bulletcount; // ������ �Ϸ�Ǹ� źâ�� �ִ�ġ�� ä��
				isreload = false; // ������ �÷��� ����
				std::cout << "�����Ϸ�" << std::endl;

				state = State::Idle;

				gun.Play("Idle");
			}
		}
	}
	else
		state = State::Roll;
}

void ShotGun::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
	window.draw(shooteffect);
	window.draw(gunend);
}

void ShotGun::SetType(Types t)
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
