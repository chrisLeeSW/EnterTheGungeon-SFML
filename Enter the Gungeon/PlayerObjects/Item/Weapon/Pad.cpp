#include "stdafx.h"
#include "Pad.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"



Pad::Pad(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	SetType(Types::Pad);

	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadShoot.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadRelode.csv"));

	effect.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadShootEffect.csv"));

	effect.SetTarget(&shooteffect);
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

}

void Pad::Init()
{
	player = PLAYER_MGR.GetPlayer();
}

void Pad::Release()
{
}

void Pad::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void Pad::Update(float dt)
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
			if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && tick <= 0.f && currentbulletcount > 0 && bulletmax >= 0)
			{
				--currentbulletcount;
				--bulletmax;

				state = State::Shoot;

				gun.Play("Shoot");
				effect.Play("Effect");
				Weapon::Shoot(bulletType, gunPoint, look);

				std::cout << "���� źâ : " << currentbulletcount << std::endl;
				std::cout << "�� źâ : " << bulletmax << std::endl;
				tick = attackrate;
			}
			if (gun.GetCurrentClipId() == "Shoot" && gun.AnimationEnd())
			{
				state = State::Idle;
			}
			if (INPUT_MGR.GetKeyDown(sf::Keyboard::R) && currentbulletcount != bulletcount && bulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Relode");
				reloadtick = reload;
				isreload = true;
			}
		}
		else if (isreload)
		{
			reloadtick -= dt; // ������ �ð� ����
			if (reloadtick <= 0.f)
			{
				currentbulletcount = bulletcount; // ������ �Ϸ�Ǹ� źâ�� �ִ�ġ�� ä��
				isreload = false; // ������ �÷��� ����
				std::cout << "�����Ϸ�" << std::endl;

				state = State::Idle;

				gun.Play("Idle");
			}
		}
	}
}

void Pad::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
	window.draw(shooteffect);
	window.draw(gunend);
}

void Pad::SetGunFlipx(bool flipX)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

	scale = shooteffect.getScale();
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	shooteffect.setScale(scale);
}

void Pad::SetType(Types t)
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