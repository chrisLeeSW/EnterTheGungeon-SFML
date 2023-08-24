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
class Enemy;

class WeaponMgr : public Singleton<WeaponMgr>
{
	friend Singleton<WeaponMgr>;

public:



protected:

	float orix;
	float oriy;

	Player* player = nullptr;


	Weapon* currentWeapon = nullptr;

	bool withWeapon = false;

	Scene* scene;
	SceneGame* sceneGame;

	WeaponMgr() = default;
	virtual ~WeaponMgr() override = default;


	std::unordered_map<Weapon::Types, Weapon*> mapweapons;

	std::list<Enemy*> enemylist;

	Weapon::Types currentWeaponType;


public:

	void Init();
	void Enter(Weapon::Types type);
	void Release();

	void Draw(sf::RenderWindow& window);



	void SetEnemyList(std::list<Enemy*> enemylist) { this->enemylist = enemylist; }
	std::list<Enemy*> GetEnemyList() { return enemylist; }

};

#define WEAPON_MGR (WeaponMgr::Instance())
