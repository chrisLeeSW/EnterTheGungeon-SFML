#pragma once
#include "Item.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"
#include "SceneGame.h"

#define FLIP_ANGLE_X 180

class Player;
class Bullet;
class GameObject;
class Enemy;

class Weapon : public Item
{
public:

	enum class Types
	{
		None,
		PilotWeapon,
		PrisonerWeapon,
		Ak47,
		Magnum,
		ShotGun,
		Pad,
	};

	enum class State
	{
		Idle,
		Shoot,
		Reload,
		Roll,
	};

protected:

	//�Ҹ� Ǯ��
	Bullet* bullet = nullptr;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> poolBullets;

	sf::Vector2f mousePos;
	sf::Vector2f look;
	sf::Vector2f monsterlook;

	State state;

	AnimationController animation;

	std::vector<AnimationController> shootEffect;

	float reload;
	float reloadtick;

	Player* player;


	sf::Vector2f handPos;
	sf::Vector2f gunPoint;

	bool flipX = false;
	
	float currentbulletcount;
	float bulletcount;
	float bulletmax;

	sf::Vector2f gunOffset1;
	sf::Vector2f gunOffset2;

	SceneGame* sceneGame;

	//Enemy ����
	std::list<Enemy*> enemylist;
	Enemy* enemy;


	std::unordered_map<sf::Keyboard::Key, int> keyToIndexMap = {
	{sf::Keyboard::Num1, 1},
	{sf::Keyboard::Num2, 2},
	{sf::Keyboard::Num3, 3},
	{sf::Keyboard::Num4, 4},
	{sf::Keyboard::Num5, 5},
	{sf::Keyboard::Num6, 6},
	{sf::Keyboard::Num7, 7},
	{sf::Keyboard::Num8, 8},
	{sf::Keyboard::Num9, 9},
	};


public:

	Weapon(const std::string& textureId = "", const std::string& n = "");
	//Weapon(Types type);
	virtual ~Weapon() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPlayer(Player* player);
	virtual void Shoot(Bullet::Types type, sf::Vector2f pos, sf::Vector2f dir);
	virtual void SetType(Types t);
	virtual void SetGunFlipx(bool flip) = 0;
	virtual Types GetWeaponType() = 0;
	virtual Bullet::Types GetBulletType() = 0;
	virtual void RequestReload() { currentbulletcount = bulletcount; };
	virtual void SwapWeapon();

	virtual float GetReloadTime() { return reload; }
	virtual float GetCurrentReloadTime() { return reloadtick; }
	virtual float GetCurrentBulleCount()  { return currentbulletcount; }
	virtual float GetRemainingAmmo()  { return bulletmax; }

	virtual sf::Vector2f Look();
	virtual void SetEnemy(Enemy* enemy);

	virtual AnimationController* GetWeaponAnimation() { return &animation; }

	virtual State GetWeaponState() { return state; }

};