#include "stdafx.h"
#include "Pad.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Bullet.h"



Pad::Pad(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	SetType(Types::Pad);
	player = PLAYER_MGR.GetPlayer();

	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadShoot.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadRelode.csv"));

	//effect.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PadShootEffect.csv"));

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
		SetOrigin(Origins::MC);
		gun.Update(dt);
		//effect.Update(dt);
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



		gunPoint = position + look * sprite.getLocalBounds().width;
		gunend.setPosition(gunPoint);


		//shooteffect.setOrigin(shooteffect.getLocalBounds().left, shooteffect.getLocalBounds().height / 2);
		//shooteffect.setRotation(angle);
		//shooteffect.setPosition(gunPoint);

		if (!isreload)
		{
			tick -= dt;
			if(commandtick >= 0.f)
			commandtick -= dt;

			if (INPUT_MGR.GetKeyUp(sf::Keyboard::S)) {
				sKeyPressed = true;
				commandtick = 0.5f;
			}

			if (commandtick >= 0.f && sKeyPressed && INPUT_MGR.GetKeyUp(sf::Keyboard::D)) {
				dKeyPressed = true;
			}

			if (commandtick >= 0.f && dKeyPressed && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left)) {
				mouseClicked = true;
			}

			if (sKeyPressed && dKeyPressed && mouseClicked && tick <= 0.f && currentbulletcount > 0 && bulletmax >= 0 ) 
			{
				// ���⼭ �߻� ���� ����
				gun.Play("Shoot");
				int shootCount = 4;
				float patternAngle = 360.f / shootCount;
				for (int i = 0; i < shootCount; ++i) 
				{
					player->Shoot(Bullet::Types::PadFire, gunPoint, Utils::RotateVector(look, patternAngle * i));
				}

				sKeyPressed = false;
				dKeyPressed = false;
				mouseClicked = false;
			}
			if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && tick <= 0.f && currentbulletcount > 0 && bulletmax >= 0)
			{
				--currentbulletcount;
				--bulletmax;

				state = State::Shoot;

				gun.Play("Shoot");
				int shootCount = 4;
				float pattenAngle = 360.f / shootCount;
				for(int i = 0; i < shootCount; ++i)
				{
					player->Shoot(bulletType, gunPoint, Utils::RotateVector(look, pattenAngle*i));
				}

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

void Pad::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);

	//window.draw(shooteffect);
	window.draw(gunend);
}

void Pad::SetGunFlipx(bool flipX)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

	//scale = shooteffect.getScale();
	//scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	//shooteffect.setScale(scale);
}

void Pad::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = info->weaponType;
	bulletType = (Bullet::Types)info->bulletType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}

