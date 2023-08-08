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
		PilotBullet,
		PrisonerBullet,
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
	void Fire(sf::Vector2f pos, sf::Vector2f dir);
};

