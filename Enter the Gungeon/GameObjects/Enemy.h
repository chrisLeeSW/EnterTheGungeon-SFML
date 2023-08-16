#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player;

enum class EnemyTypes
{
	None = -1,

	BulletKin,
	KeyBulletKin,
	ShotgunKinRed,
	ShotgunKinBlue,

	Count,
};

class Enemy : public SpriteGo
{
protected:
	AnimationController animation;

	std::vector<sf::Vector2f> way;
	sf::Vector2f direction;
	sf::Vector2f prevDir;
	float speed = 0.f;
	float maxHp = 0.f;
	float hp = 0.f;
	bool isHanded = false;
	bool flipX = false;
	bool isAlive = true;
	float attackRange = 0.f;
	float attackInterval = 0.f;
	float attackTimer = 0.f;
	bool superarmor = false;

	Player* player;
	sf::Sprite hand;
	EnemyTypes type;

public:
	Enemy(EnemyTypes type, const std::string& textureId="", const std::string& n="");
	virtual ~Enemy() override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;

	void SetFlipX(bool flip);
	sf::Vector2f WhereWay(sf::Vector2f dir);

	void SetPlayer(Player* player);
	void SetEnemy(float speed = 0.f, float maxHp = 0.f, float attackRange = 0.f, float attackInterval = 0.f, bool superarmor = false);

	std::function<void(float)> IfHit; // Bullet에게 맞았을 때
	std::function<void()> IfBump; // Player와 몸이 충돌했을 때
	std::function<void(sf::Vector2f dir)> IfDie; // 사망 시
	std::function<void(sf::Vector2f dir, float speed)> IfShoot;

	void OnDamage(const float& damage, sf::Vector2f dir = {0.f, 0.f}, const float& knockback = 0.f);
	void OnBump();
	void OnDie(const sf::Vector2f& look);

	// 단발사격
	void OneShot(sf::Vector2f dir, float speed, bool isBlink = false);
	// 전방으로 5개의 총알을 산개하여 발사
	void FiveWayShot(sf::Vector2f dir, float speed);

	// 6방향으로 총알을 발사하며 사망
	void SixWayDie(sf::Vector2f dir, float speed, int chance);
};