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
		Magnum,
	};


protected:

	AnimationController animation;


	sf::Vector2f direction;
	sf::Vector2f position;

	Types bulletType;
	float speed;
	float damage;
	int range;
	int knockback;

	std::string anistirng;

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

	void SetBullet(int types, sf::Vector2f pos, sf::Vector2f dir);
	void Shoot(Types type);
	void Fire(sf::Vector2f pos, sf::Vector2f dir);
};