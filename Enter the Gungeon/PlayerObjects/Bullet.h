#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "Weapon.h"
#include "AnimationController.h"

class Bullet : public SpriteGo
{


public:

	enum class Types
	{
		None,
		PilotBullet,
		PrisonerBullet,
		Ak47,
	};


protected:

	AnimationController animation;


	sf::Vector2f direction;
	sf::Vector2f position;

	Types bulletType;
	int speed;
	int damage;
	int range;
	int knockback;

	SpriteGo* bullet;

public:

	ObjectPool<Bullet>* pool;
	Bullet(const std::string& textureId = "", const std::string& n = "");
	virtual ~Bullet() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetType(int types);
	void Shoot(Types type);
	void Fire(sf::Vector2f pos, sf::Vector2f dir);
};

class PilotGun : public Bullet
{
public:
	PilotGun(Types tpye);
	void Update(float dt) override;


};

class PrisonerGun : public Bullet
{
public:
	PrisonerGun();
	void Update(float dt) override;
};

class Ak47 : public Bullet
{
public:
	Ak47();
	void Update(float dt) override;
};