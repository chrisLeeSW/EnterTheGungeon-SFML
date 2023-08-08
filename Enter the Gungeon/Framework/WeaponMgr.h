#pragma once
#include "Weapon.h"
#include "Singleton.h"

class WeaponMgr : public Singleton<WeaponMgr>
{
	friend Singleton<WeaponMgr>;

protected:

	WeaponMgr() = default;
	virtual ~WeaponMgr() override = default;

    std::vector<Weapon*> weapons;

	Weapon::Types currentWeapon = Weapon::Types::Pilot;


public:

	void Init();
	void Release();

    void AddWeapon(Weapon::Types type);

    void SwapWeapon(int swap);

    void ChangeCurrentWeapon(int weaponIndex);

	Weapon::Types GetCurrentWeapon() const;
};

#define WEAPON_MGR (WeaponMgr::Instance())
