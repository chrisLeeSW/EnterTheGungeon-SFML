#pragma once
#include "Weapon.h"
#include "AnimationController.h"
#include "Bullet.h"

class Enemy;

class EnemyShotGun : public Weapon
{

protected:



public:

	EnemyShotGun(const std::string& textureId = "", const std::string& n = "");
	virtual ~EnemyShotGun() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flipX) override;

	virtual Types GetWeaponType() override { return weaponType; }
	virtual Bullet::Types GetBulletType() override { return bulletType; }

	virtual void SetEnemy(Enemy* enemy) override { this->enemy = enemy; }
};