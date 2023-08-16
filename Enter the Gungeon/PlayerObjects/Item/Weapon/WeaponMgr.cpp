#include "stdafx.h"
#include "WeaponMgr.h"
#include "WeaponTable.h"
#include "DataTableMgr.h"
#include "Weapon.h"
#include "Scene.h"
#include "SceneGame.h"
#include "PilotWeapon.h"
#include "PrisonerWeapon.h"
#include "Ak47.h"


void WeaponMgr::Init()
{

	if (!weapons.empty())
	{
		Release();
	}


	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr](Bullet* bullet) {
		bullet->pool = ptr;
	};
	poolBullets.Init();

	withWeapon = true;

	scene = SCENE_MGR.GetGameScene();
	sceneGame = dynamic_cast<SceneGame*>(scene);
}


void WeaponMgr::Enter(Weapon::Types type)
{
	if (!weapons.empty())
	{
		Release();
	}


	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr](Bullet* bullet) {
		bullet->pool = ptr;
	};
	poolBullets.Init();

	withWeapon = true;
	
	scene = SCENE_MGR.GetCurrScene();
	sceneGame = dynamic_cast<SceneGame*>(scene);

}



void WeaponMgr::Release()
{
	if (weapons.empty())
	{
		return;
	}

	for (auto weapon : weapons)
	{
		//scene->Release();
		delete weapon;
	}
	weapons.clear();

	currentWeaponType = Weapon::Types::None;
}


void WeaponMgr::Draw(sf::RenderWindow& window)
{
	currentWeapon->Draw(window);
}

void WeaponMgr::SetPlayer(Player* player)
{
	this->player = player;
}

Player* WeaponMgr::GetPlayer()
{
	return player;
}

bool WeaponMgr::GetWithWeapon()
{
	return withWeapon;
}

void WeaponMgr::Shoot(Bullet::Types type, sf::Vector2f pos, sf::Vector2f dir)
{
	bullet = poolBullets.Get();
	bullet->SetBullet(type,pos,dir);
	sceneGame->AddGo(bullet);
}



void WeaponMgr::SetWeaPonFlipx(bool flip)
{
	currentWeapon->SetGunFlipx(flip);
}

Weapon::Types WeaponMgr::GetCurrentWeapon() const
{
	return currentWeaponType;
}

const void WeaponMgr::GetWeapon(Weapon::Types id)
{
	auto find = mapweapons.find(id);
	if (find == mapweapons.end())
	{
		std::cout << "ÃÑ ¸øÃ£¾ÒÀ½" << std::endl;
	}
	else
	{
		for (const auto& pair : mapweapons)
		{
			weapons.push_back(pair.second);
			break;
		}
	}
}
