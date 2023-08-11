#pragma once
#include "Weapon.h"
#include "Singleton.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"

class Weapon;

class WeaponMgr : public Singleton<WeaponMgr>
{
	friend Singleton<WeaponMgr>;


public:



protected:

	Bullet* bullet;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> poolBullets;

    std::vector<Weapon*> weapons;
	Weapon* pilotgun;
	Weapon* prisonergun;
	Weapon* ak47;



	WeaponMgr() = default;
	virtual ~WeaponMgr() override = default;


	std::unordered_map<Weapon::Types, Weapon*> mapweapons;


	Weapon::Types currentWeapon;

	std::function<void(Weapon*)> weaponSetType;

public:

	void Init();
	void Release();

    void SwapWeapon(int swap);


	void SetType(Weapon::Types t);

	Weapon::Types GetCurrentWeapon() const;
	const void AddWeapon(Weapon::Types id);
};

#define WEAPON_MGR (WeaponMgr::Instance())
