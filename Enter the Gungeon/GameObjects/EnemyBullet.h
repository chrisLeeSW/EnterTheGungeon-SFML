#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class Player;

class EnemyBullet : public SpriteGo
{
protected:
	AnimationController animation;
	Player* player;

	sf::Vector2f direction;
	float speed = 0.0f;
	int damage = 1;
	float range = 1000.0f;
	
	bool isBlink = false;

	sf::FloatRect wall;
	float wallTop = 0.0f;
	float wallBottom = 0.0f;
	float wallLeft = 0.0f;
	float wallRight = 0.0f;

public:
	ObjectPool<EnemyBullet>* pool;

	EnemyBullet(std::string textureId = "", std::string name = "");
	virtual ~EnemyBullet() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetWall(const sf::FloatRect& wall);

	void SetPlayer(Player* player);
	void SetBullet(bool isBlink = false);
	void Shoot(sf::Vector2f dir, float speed, float range = 1000.0f, int damage = 1);

	bool IsBlink() const;
};