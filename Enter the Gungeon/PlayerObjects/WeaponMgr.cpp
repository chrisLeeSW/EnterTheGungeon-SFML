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

	//Scene* scene = SCENE_MGR.GetGameScene();
	//SceneGame* SG = dynamic_cast<SceneGame*>(scene);
	//
	//weapons.push_back(new PilotWeapon());
	//prisonergun = (Weapon*)SG->AddGo(new Weapon());
	//ak47 = (Weapon*)SG->AddGo(new Weapon());
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

	currentWeapon = Weapon::Types::None;
}

void WeaponMgr::SwapWeapon(int swap)
{
	if (swap >= 0 && swap < weapons.size())
	{
		currentWeapon = (Weapon::Types)swap;
		SetType(currentWeapon);
	}
	else
	{
		std::cout << "Invalid weapon index!" << std::endl;
	}
}

void WeaponMgr::SetType(Weapon::Types t)
{

	Weapon::Types settype = t;
	weaponSetType = [this, settype](Weapon* weapon)
	{
		weapon->SetType(settype);
	};

}
Weapon::Types WeaponMgr::GetCurrentWeapon() const
{
	return currentWeapon;
}

const void WeaponMgr::AddWeapon(Weapon::Types id)
{
	auto find = mapweapons.find(id);
	if (find == mapweapons.end())
	{
		std::cout << "ÃÑ ¸øÃ£¾ÒÀ½" << std::endl;
	}

	switch (id)
	{
	case Weapon::Types::PilotWeapon:
		weapons.push_back(new PilotWeapon());
		break;
	case Weapon::Types::PrisonerWeapon:
		weapons.push_back(new PrisonerWeapon());
		break;
	case ::Weapon::Types::Ak47:
		weapons.push_back(new Ak47());
		break;
	}
}