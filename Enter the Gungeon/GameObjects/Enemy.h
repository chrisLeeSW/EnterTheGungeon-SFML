#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player;
//김혜준 추가
class ShotGun;
class Magnum;

class Enemy : public SpriteGo
{
public:
	enum class EnemyName
	{
		None = -1,

		// Normal Enemy
		BulletKin,
		KeyBulletKin,
		ShotgunKinRed,
		ShotgunKinBlue,

		// Unique Enemy

		// Boss
		GatlingGull,

		Count,
	};

	enum class State
	{
		Idle,
		Move,
		Attack,
		Hit,
		Die,
		Runaway,

		Count,
	};

protected:
	AnimationController animation;

	std::vector<sf::Vector2f> way;
	sf::Vector2f direction;
	float speed = 0.f;
	float maxHp = 0.f;
	float hp = 0.f;
	bool isHanded = false;
	bool flipX = false;
	float attackRange = 0.f;
	float attackInterval = 0.f;
	float attackTimer = 0.f;
	bool superarmor = false;

	int patternCount = 0;

	//Enemy Weapon - 김혜준 추가
	ShotGun* shotgun;
	Magnum* magnum;

	Player* player;
	sf::Sprite hand;
	sf::Sprite shadow;
	EnemyName type;
	Enemy::State state;

public:
	Enemy(EnemyName type, const std::string& textureId="", const std::string& n="");
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
	void SetEnemy();
	void LoadMuzzle(const std::string& path);

	// Bullet에게 맞았을 때
	std::function<void(float)> IfHit;
	// Player와 몸이 충돌했을 때
	std::function<void()> IfBump;
	// 사망 시
	std::function<void(sf::Vector2f dir)> IfDie;
	// 사격 시
	std::function<void(sf::Vector2f dir, float speed)> IfShoot;

	void OnDamage(const float& damage, sf::Vector2f dir = {0.f, 0.f}, const float& knockback = 0.f);
	void OnBump();
	void OnDie(const sf::Vector2f& look);

	// 단발사격
	void OneShot(sf::Vector2f dir, float speed, bool isBlink = false);
	// 각도를 조절한 단발사격
	void AngleShot(sf::Vector2f dir, float speed, float angle = 0.f, bool isBlink = false);
	// 부채꼴로 n개의 총알을 산개하여 발사
	void ShotgunShot(sf::Vector2f dir, float speed, int quantity, float angle);
	// 위치 벡터에 총알을 유지
	void Boom(sf::Vector2f pos, float range);
	// 근접공격
	void CloseAttack(float range);

	// 6방향으로 총알을 발사하며 사망
	void SixWayDie(sf::Vector2f dir, float speed, int chance);

	// 탄피 드랍
	void DropCasing();
	// 열쇠 드랍
	void DropKey();
};