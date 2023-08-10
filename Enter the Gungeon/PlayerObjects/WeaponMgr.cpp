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

	currentWeapon = Weapon::Types::Pilot;
}


void WeaponMgr::SwapWeapon(int swap)
{
	ChangeCurrentWeapon(swap);
}

void WeaponMgr::ChangeCurrentWeapon(int weaponIndex)
{
	if (weaponIndex >= 0 && weaponIndex < weapons.size())
	{
		currentWeapon = (Weapon::Types)weaponIndex;
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
