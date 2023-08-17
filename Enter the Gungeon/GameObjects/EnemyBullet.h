#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

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

public:
	EnemyBullet(std::string textureId = "", std::string name = "");
	virtual ~EnemyBullet() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetPlayer(Player* player);
	void SetBullet(bool isBlink = false);
	void Shoot(sf::Vector2f dir, float speed, float range = 1000.0f, int damage = 1);

	bool IsBlink() const;
};