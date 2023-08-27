#pragma once
#include "Enemy.h"
#include "AnimationController.h"

class Player;

class Boss : public Enemy
{
public:
	enum class PatternNum
	{
		None,

		P1,
		P2,
		P3,
		P4,
		P5,
		P6,
		P7,

		Count,
	};

protected:
	PatternNum pattern = PatternNum::None;

	float patternTimer = 0.f;
	float patternDuration = 0.f;

public:
	Boss(EnemyName type, const std::string& textureId = "", const std::string& n = "");
	virtual ~Boss() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void SetPlayer(Player* player) override;

	void SetBoss(float patternDuration = 0.f);
	void PlayPattern(const PatternNum& p);
	void EndPattern(bool idle = true);

	std::function<void(sf::Vector2f dir, float speed)> Pattern1;
	std::function<void(sf::Vector2f dir, float speed)> Pattern2;
	std::function<void(sf::Vector2f dir, float speed)> Pattern3;
	std::function<void(sf::Vector2f dir, float speed)> Pattern4;
	std::function<void(sf::Vector2f dir, float speed)> Pattern5;
	std::function<void(sf::Vector2f dir, float speed)> Pattern6;
	std::function<void(sf::Vector2f dir, float speed)> Pattern7;

	const Enemy::EnemyName& GetType() const;

	sf::Vector2f GatlingGullMuzzlePos();
};