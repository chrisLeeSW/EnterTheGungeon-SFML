#include "stdafx.h"
#include "PrisonerWeapon.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "PlayerUI.h"


PrisonerWeapon::PrisonerWeapon(const std::string& textureId, const std::string& n)
{
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerWeaponIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerWeaponShoot.csv"));

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

void PrisonerWeapon::Init()
{
	player = PLAYER_MGR.GetPlayer();
	SetType(Types::PrisonerWeapon);
	tick = attackrate;
	reloadtick = reload;
	currentbulletcount = bulletcount;
	currentbulletmax = bulletmax;
}

void PrisonerWeapon::Release()
{
}

void PrisonerWeapon::Reset()
{
	SpriteGo::Reset();
}

void PrisonerWeapon::Update(float dt)
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

		//�̰� ���콺�ε� �÷��̾�� ���� ������ ���� ��ֶ������ؼ� �־�ߵɵ�
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

				tick = attackrate;
			}
			if (gun.GetCurrentClipId() == "Shoot" && gun.AnimationEnd())
			{
				state = State::Idle;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::R) && currentbulletcount != bulletcount && currentbulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Relode");
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
				player->playerUI->ShootWeapon();
				state = State::Idle;
				gun.Play("Idle");
				isreload = false; // ������ �÷��� ����
			}
		}
	}
	else if (player->isRolling() && state == State::Reload)
	{
		reloadtick += dt; // ������ �ð� ����
		if (reloadtick >= reload)
		{
			currentbulletcount = bulletcount; // ������ �Ϸ�Ǹ� źâ�� �ִ�ġ�� ä��
			player->playerUI->ShootWeapon();
			state = State::Idle;
			gun.Play("Idle");
			isreload = false; // ������ �÷��� ����
		}
	}
}

void PrisonerWeapon::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
	window.draw(gunend);
}


