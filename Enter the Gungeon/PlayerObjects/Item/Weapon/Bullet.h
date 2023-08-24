#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "Weapon.h"
#include "AnimationController.h"
#include "Enemy.h"

class Enemy;

class Bullet : public SpriteGo
{

public:

	enum class Types
	{
		None,
		PilotBullet,
		PrisonerBullet,
		Ak47,
		Magnum,
		Pad,
		PadFire,
	};


protected:

	AnimationController animation;


	sf::Vector2f direction;
	sf::Vector2f position;


	//BulletInfo
	Types bulletType;
	std::string bulletid;
	float speed;
	float damage;
	float range;
	float knockback;

	float santan1 = 1.3;

	float santan2 = 0.7f;

	std::string anistring;

	SpriteGo* bullet;

	//Enemy
	Enemy* enemy;
	std::list<Enemy*> enemylist;


public:
	ObjectPool<Bullet>* pool;

	Bullet(const std::string& textureId = "", const std::string& n = "");
	virtual ~Bullet() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetBullet(Types types, sf::Vector2f pos, sf::Vector2f dir, float santan);
	void Fire(sf::Vector2f pos, sf::Vector2f dir);
	void SetEnemy(std::list<Enemy*> enemylist) { this->enemylist = enemylist; }

	void HitEnemy();
};