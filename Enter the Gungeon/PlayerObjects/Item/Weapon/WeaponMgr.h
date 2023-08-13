#pragma once
#include "Weapon.h"
#include "Singleton.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"

class Weapon;
class Player;
class SceneGame;
class Scene;

class WeaponMgr : public Singleton<WeaponMgr>
{
	friend Singleton<WeaponMgr>;

	
public:



protected:

	float orix;
	float oriy;

	Player* player = nullptr;

	Bullet* bullet = nullptr;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> poolBullets;

    std::vector<Weapon*> weapons;
	Weapon* pilotgun;
	Weapon* prisonergun;
	Weapon* ak47;

	Weapon* currentWeapon = nullptr;

	bool withWeapon = false;

	Scene* scene;
	SceneGame* sceneGame;

	WeaponMgr() = default;
	virtual ~WeaponMgr() override = default;


	std::unordered_map<Weapon::Types, Weapon*> mapweapons;


	Weapon::Types currentWeaponType;


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
	void TestAddWeapon();
	void Shoot();


	Weapon::Types GetCurrentWeapon() const;
	const void GetWeapon(Weapon::Types id);
};

#define WEAPON_MGR (WeaponMgr::Instance())
