#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player;

enum class EnemyTypes
{
	None = -1,

	BulletKin,
	KeyBulletKin, //Escape�Լ� ���� �ʿ�
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
	float speed = 0.f;
	float maxHp = 0.f;
	float hp = 0.f;
	bool isHanded = false;
	bool flipX = false;
	bool isAlive = true;
	float attackRange = 0.f;
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
	void SetEnemy(float speed = 0.f, float maxHp = 0.f, float attackRange = 0.f, bool superarmor = false);

	std::function<void(float)> IfHit; // Bullet���� �¾��� ��
	std::function<void()> IfBump; // Player�� ���� �浹���� ��
	std::function<void()> IfDie; // ��� ��

	void OnDamage(const float& damage, const sf::Vector2f& dir = {0.f, 0.f}, const float& knockback = 0.f);
	void OnBump();
	void OnDie(const sf::Vector2f& dir);

	// ����� ��� �Լ������͸� ����Ͽ� Enemy�� �ִ� ���� ��� �Լ��� �� �ϳ��� ȣ���ϴ� ������� �����ϸ� ���?
};