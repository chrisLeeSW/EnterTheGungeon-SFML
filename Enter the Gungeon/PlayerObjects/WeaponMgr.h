#pragma once
#include "Weapon.h"
#include "Singleton.h"

class WeaponMgr : public Singleton<WeaponMgr>
{
	friend Singleton<WeaponMgr>;


public:


	//enum class WeaponTypes
	//{

	//	PilotGun,
	//	PrisonerGun,
	//	Ak47,
	//};

protected:

	WeaponMgr() = default;
	virtual ~WeaponMgr() override = default;


	std::unordered_map<Weapon::Types, Weapon*> findweapon;

    std::vector<Weapon*> weapons;

	Weapon::Types currentWeapon;


public:

	void Init();
	void Release();

    void SwapWeapon(int swap);


	Weapon::Types GetCurrentWeapon() const;
	const void AddWeapon(Weapon::Types id);
};

#define WEAPON_MGR (WeaponMgr::Instance())
