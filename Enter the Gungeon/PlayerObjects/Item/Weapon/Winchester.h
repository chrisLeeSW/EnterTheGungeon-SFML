#pragma once
#include "Weapon.h"
#include "AnimationController.h"
#include "Bullet.h"

class Enemy;

class Winchester : public Weapon
{

protected:

	Player* player = nullptr;
	Enemy* enemy = nullptr;

	Types weaponType;
	Bullet::Types bulletType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	float reload;
	int santan;

	bool flipX = false;

	AnimationController gun;
	AnimationController shootEffect;

	float WeaponXpos = 9.f;

	sf::RectangleShape gunend;

public:

	Winchester(const std::string& textureId = "", const std::string& n = "");
	virtual ~Winchester() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flipX) override;

	virtual Types GetWeaponType() override { return weaponType; }
	virtual void SetType(Types type) override;
	virtual Bullet::Types GetBulletType() override { return bulletType; }

	virtual void SetEnemy(Enemy* enemy) override { this->enemy = enemy; }
};