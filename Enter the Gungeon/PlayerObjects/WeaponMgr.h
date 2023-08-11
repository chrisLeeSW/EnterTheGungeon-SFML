#pragma once
#include "Weapon.h"
#include "Singleton.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"

class Weapon;
class Player;

class WeaponMgr : public Singleton<WeaponMgr>
{
	friend Singleton<WeaponMgr>;

	
public:



protected:

	float orix;
	float oriy;

	Player* player = nullptr;

	Bullet* bullet;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> poolBullets;

    std::vector<Weapon*> weapons;
	Weapon* pilotgun;
	Weapon* prisonergun;
	Weapon* ak47;

	Weapon* currentWeapon = nullptr;

	bool withWeapon = false;


	WeaponMgr() = default;
	virtual ~WeaponMgr() override = default;


	std::unordered_map<Weapon::Types, Weapon*> mapweapons;


	Weapon::Types currentWeaponType;

	std::function<void(Weapon*)> weaponSetType;

public:

	void Init();
	void Enter(Weapon::Types type);
	void Release();


    void SwapWeapon(int swap);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void SetWeaPonFlipx(bool flip);
	bool GetWithWeapon();

	void SetPlayer(Player* player);
	Player* GetPlayer();


	void SetHandOrigin(sf::Vector2f handori);
	sf::Vector2f GetHandOrigin();


	Weapon::Types GetCurrentWeapon() const;
	const void GetWeapon(Weapon::Types id);
};

#define WEAPON_MGR (WeaponMgr::Instance())
