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

}


void WeaponMgr::Enter(Weapon::Types type)
{
	if (!weapons.empty())
	{
		Release();
	}

	switch (type)
	{
	case Weapon::Types::PilotWeapon :
		weapons.push_back(new PilotWeapon());
		currentWeapon = weapons.front();
		//currentWeapon->Init();
		std::cout << "웨폰매니저 엔터 : 타입 파일럿 웨폰";
		break;

	case Weapon::Types::PrisonerWeapon : 
		weapons.push_back(new PrisonerWeapon());
		currentWeapon = weapons.front();
		std::cout << "웨폰매니저 엔터 : 타입 프리즈너 웨폰";
		break;
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

void WeaponMgr::SwapWeapon(int swap)
{
	if (swap >= 0 && swap <= weapons.size())
	{
		swap--;
		currentWeapon = weapons[swap];
		std::cout << "int swap 의 값 : " << swap << std::endl;
	}
	else
	{
		std::cout << "Invalid weapon index!" << std::endl;
	}
}

void WeaponMgr::Update(float dt)
{
	currentWeapon->Update(dt);
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

void WeaponMgr::Shoot()
{
	bullet = poolBullets.Get();
	bullet->SetBullet((int)currentWeapon->GetWeaponType(), currentWeapon->GetPosition(), currentWeapon->Look());
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
		std::cout << "총 못찾았음" << std::endl;
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

void WeaponMgr::TestAddWeapon()
{
	weapons.push_back(new PrisonerWeapon());
	std::cout << "테스트 무기 추가" << std::endl;
}