#pragma once
#include "Item.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"
#include "SceneGame.h"

#define FLIP_ANGLE_X 180

class Player;
class Bullet;
class Enemy;
class PlayerUI;

class Weapon : public Item
{
public:

	enum class Types
	{
		None,
		PilotWeapon,
		PrisonerWeapon,
		Pad,
		ShotGun,
		Count,
		Ak47,
		Magnum,
	};

	enum class State
	{
		Idle,
		Shoot,
		Reload,
		Roll,
	};

protected:

	AnimationController gun;
	AnimationController effect;

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	PlayerUI* playerui = nullptr;

	Types weaponType;
	Bullet::Types bulletType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	int currentbulletcount;
	int currentbulletmax;
	float reload;
	int santan;
	float tick;
	float reloadtick;
	bool isreload = false;
	bool flipX = false;
	sf::RectangleShape gunend;
	float WeaponXpos = 9.f;

	sf::Vector2f mousePos;
	sf::Vector2f look;
	sf::Vector2f monsterlook;

	State state;


	sf::Vector2f handPos;
	sf::Vector2f gunPoint;
	sf::Vector2f gunPos;
	

	sf::Vector2f gunOffset1;
	sf::Vector2f gunOffset2;

	SceneGame* sceneGame;

	sf::Sprite shooteffect;


public:

	Weapon(const std::string& textureId = "", const std::string& n = "");
	virtual ~Weapon() override { Release(); }

	virtual void Init()= 0;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPlayer(Player* player);
	virtual void SetType(Types t);

	virtual void SetGunFlipx(bool flip);
	virtual Types GetWeaponType() { return weaponType; }
	virtual Bullet::Types GetBulletType() { return bulletType; }

	virtual void RequestReload() { currentbulletcount = bulletcount; };
	virtual void SwapWeapon();
	virtual void GetAmmunition() { currentbulletmax = bulletmax; }

	virtual float GetReloadTime() { return reload; }
	virtual float GetCurrentReloadTime() { return reloadtick; }
	virtual int GetCurrentBulleCount()  { return currentbulletcount; }
	virtual int GetRemainingAmmo()  { return bulletmax; }
	virtual int GetCurrentRamainingAmmo() { return currentbulletmax; }


	virtual sf::Vector2f GetGunPoint() { return gunPoint; }


	virtual void SetEnemy(Enemy* enemy);

	virtual AnimationController* GetWeaponAnimation() { return &gun; }

	virtual State GetWeaponState() { return state; }
};