#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

enum class BulletType
{
	None = -1,
	EnemyBullet,

	Count,
};

class Bullet : public SpriteGo
{
protected:
	AnimationController animation;

	sf::Vector2f direction;
	float speed = 0.0f;
	int damage = 0;
	BulletType type;

	bool isBlink = false;

public:
	Bullet(BulletType type, std::string textureId = "", std::string name = "");
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetBullet(bool isBlink = false);
	void Shoot(sf::Vector2f dir, float speed, int damage = 1);
};