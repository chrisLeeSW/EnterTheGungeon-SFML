#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player;

enum class EnemyTypes
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
	float speed = 0.f;
	float maxHp = 0.f;
	float hp = 0.f;
	bool isHanded = false;
	bool flipX = false;
	bool isAlive = true;

	Player* player;
	sf::Sprite hand;
	EnemyTypes type;

public:
	Enemy(EnemyTypes type, const std::string& textureId="", const std::string& n="");
	virtual ~Enemy() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;

	void SetFlipX(bool flip);

	void SetPlayer(Player* player);
	void SetEnemy(float speed = 0.f, float maxHp = 0.f);

	std::function<void(float)> IfHit; // Bullet���� �¾��� ��
	std::function<void()> IfBump; // Player�� ���� �浹���� ��
	std::function<void()> IfDie; // ��� ��

	void OnDamage(float damage);
	void OnBump();
	void OnDie();

	// ����� ��� �Լ������͸� ����Ͽ� Enemy�� �ִ� ���� ��� �Լ��� �� �ϳ��� ȣ���ϴ� ������� �����ϸ� ���?
};