#include "stdafx.h"
#include "WeaponMgr.h"

void WeaponMgr::Init()
{
	if (!weapons.empty())
	{
		Release();
	}
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
	}
	else
	{
		std::cout << "Invalid weapon index!" << std::endl;
	}
}


Weapon::Types WeaponMgr::GetCurrentWeapon() const
{
	return currentWeapon;
}

const void WeaponMgr::AddWeapon(Weapon::Types id)
{
	auto find = findweapon.find(id);
	if (find == findweapon.end())
	{
		std::cout << "ÃÑ ¸øÃ£¾ÒÀ½" << std::endl;
	}

	weapons.push_back(find->second);
}