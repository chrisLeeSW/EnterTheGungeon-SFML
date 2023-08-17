#include "stdafx.h"
#include "PilotWeapon.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"


PilotWeapon::PilotWeapon(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	SetType(Types::PilotWeapon);

	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponShoot.csv"));

	gun.SetTarget(&sprite);

	SpriteGo::Reset();

	gun.Play("Idle");

	gunend.setFillColor(sf::Color::Transparent);
	gunend.setOutlineColor(sf::Color::Red);
	gunend.setOutlineThickness(2.f);
	gunend.setSize(sf::Vector2f{ 5,5 });

	tick = attackrate;
	reloadtick = reload;

	gunOffset1 = { sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height + 4};
	gunOffset2 = { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height - 4};

	currentbulletcount = bulletcount;

	Weapon::Init();
}

void PilotWeapon::Init()
{
	player = PLAYER_MGR.GetPlayer();
}

void PilotWeapon::Release()
{
}

void PilotWeapon::Reset()
{
	player = PLAYER_MGR.GetPlayer();

}

void PilotWeapon::Update(float dt)
{

	Weapon::Update(dt);
	if (!player->isRolling())
	{
		SetOrigin(Origins::BL);
		gun.Update(dt);
		SetPosition(player->PlayerHandPos());

		float angle = Utils::Angle(look);
		sf::Vector2f gunOffset = Utils::RotateVector(gunOffset1, angle);

		//이거 마우스인데 플레이어랑 몬스터 포지션 뺀걸 노멀라이즈해서 넣어야될듯
		if (flipX)
		{
			gunOffset = Utils::RotateVector(gunOffset2, angle);
			angle += FLIP_ANGLE_X;
		}

		sprite.setRotation(angle);


		SetGunFlipx(player->GetFilpX());


		gunend.setPosition(gunPoint);
		gunPoint = player->PlayerHandPos();
		gunPoint += gunOffset;


		if (!isreload)
		{
			tick -= dt;
			if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && tick <= 0.f && currentbulletcount > 0 && bulletmax >= 0)
			{

				--currentbulletcount;
				--bulletmax;
				gun.Play("Shoot");
				Weapon::Shoot(bulletType, gunPoint, look);

				std::cout << "현재 탄창 : " << currentbulletcount << std::endl;
				std::cout << "총 탄창 : " << bulletmax << std::endl;
				tick = attackrate;
			}

			if (INPUT_MGR.GetKeyDown(sf::Keyboard::R) && currentbulletcount != bulletcount && bulletmax >= 0)
			{
				reloadtick = reload;
				isreload = true;
			}
		}
		else if (isreload)
		{
			reloadtick -= dt; // 재장전 시간 감소
			if (reloadtick <= 0.f)
			{
				currentbulletcount = bulletcount; // 재장전 완료되면 탄창을 최대치로 채움
				isreload = false; // 재장전 플래그 해제
				std::cout << "장전완료" << std::endl;
			}
		}
	}
}

void PilotWeapon::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
		window.draw(gunend);
}

void PilotWeapon::SetGunFlipx(bool flipX)
{

	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

}


void PilotWeapon::SetType(Types t)
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
