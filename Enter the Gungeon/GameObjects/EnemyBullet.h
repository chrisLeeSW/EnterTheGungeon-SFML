#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

enum class BulletType
{
	None = -1,
	EnemyBullet,

	Count,
};

class EnemyBullet : public SpriteGo
{
protected:
	AnimationController animation;

	sf::Vector2f direction;
	float speed = 0.0f;
	int damage = 0;
	float range = 1000.0f;
	BulletType type;

	bool isBlink = false;

public:
	EnemyBullet(BulletType type, std::string textureId = "", std::string name = "");
	virtual ~EnemyBullet() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetBullet(bool isBlink = false);
	void Shoot(sf::Vector2f dir, float speed, float range = 1000.0f, int damage = 1);

	bool IsBlink() const;
};