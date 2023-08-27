#include "stdafx.h"
#include "Pad.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "PlayerUI.h"



Pad::Pad(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{

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


	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4 };
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4 };

}

void Pad::Init()
{
	player = PLAYER_MGR.GetPlayer();
	SetType(Types::Pad);
	tick = attackrate;
	reloadtick = reload;
	currentbulletcount = bulletcount;
	currentbulletmax = bulletmax;
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

		//이거 마우스인데 플레이어랑 몬스터 포지션 뺀걸 노멀라이즈해서 넣어야될듯
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

			if (INPUT_MGR.GetKeyDown(sf::Keyboard::R) && currentbulletcount != bulletcount && currentbulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Reload");
				reloadtick = 0.f;
				isreload = true;
			}
			else if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && currentbulletcount == 0 && currentbulletmax >= 0)
			{
				state = State::Reload;

				gun.Play("Reload");
				reloadtick = 0.f;
				isreload = true;
			}

			if (sKeyPressed && dKeyPressed && mouseClicked && tick <= 0.f && currentbulletcount > 0 && bulletmax >= 0 ) 
			{
				// 여기서 발사 로직 수행
				gun.Play("Shoot");
				int shootCount = 4;
				float patternAngle = 360.f / shootCount;
				for (int i = 0; i < shootCount; ++i) 
				{
					player->Shoot(Bullet::Types::PadFire, gunPoint, Utils::RotateVector(look, patternAngle * i), santan);
				}

				sKeyPressed = false;
				dKeyPressed = false;
				mouseClicked = false;
			}
			if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && tick <= 0.f && currentbulletcount > 0 && currentbulletmax >= 0)
			{
				--currentbulletcount;
				--currentbulletmax;

				state = State::Shoot;

				gun.Play("Shoot");
				int shootCount = 4;
				float pattenAngle = 360.f / shootCount;
				for(int i = 0; i < shootCount; ++i)
				{
					player->Shoot(bulletType, gunPoint, Utils::RotateVector(look, pattenAngle*i), santan);
				}

				std::cout << "현재 탄창 : " << currentbulletcount << std::endl;
				std::cout << "총 탄창 : " << currentbulletmax << std::endl;
				tick = attackrate;
			}
			if (gun.GetCurrentClipId() == "Shoot" && gun.AnimationEnd())
			{
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
				std::cout << "장전완료" << std::endl;
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

