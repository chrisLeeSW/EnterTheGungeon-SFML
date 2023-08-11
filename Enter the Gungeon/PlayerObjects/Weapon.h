#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "AnimationController.h"

class Player;
class Bullet;

class Weapon : public SpriteGo
{
public:

	enum class Types
	{
		None,
		PilotWeapon,
		PrisonerWeapon,
		Ak47,
	};

protected:

	Bullet* bullet;
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> poolBullets;

	sf::Vector2f mousePos;
	sf::Vector2f look;

	AnimationController animation;

	std::vector<AnimationController> shootEffect;

	Player* player;

	Types weaponType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	float reload;
	int santan;

public:

	Weapon(const std::string& textureId = "", const std::string& n = "");
	//Weapon(Types type);
	virtual ~Weapon() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetPlayer(Player* player);


	void Shoot(Weapon::Types type);
	void SetType(Types t);
};