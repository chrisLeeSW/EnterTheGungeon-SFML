#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player;

enum class MonsterTypes
{
	None = -1,
	BulletKin,

	Count,
};

class Enemy : public SpriteGo
{
protected:
	AnimationController animation;

	sf::Vector2f direction;
	sf::Vector2f look;
	float speed = 0.f;
	float maxHp = 0.f;
	float hp = 0.f;
	bool isHanded = false;

	Player* player;
	sf::Sprite hand;
	MonsterTypes type;

public:
	Enemy(MonsterTypes type, const std::string& textureId="", const std::string& n="");
	virtual ~Enemy() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};