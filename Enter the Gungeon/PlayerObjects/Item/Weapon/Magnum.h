#pragma once
#include "Weapon.h"
#include "AnimationController.h"

class Player;

class Magnum : public Weapon
{

protected:

	Player* player = nullptr;

	Types weaponType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	float reload;
	int santan;

	bool flipX = false;

	AnimationController gun;
	AnimationController shootEffect;

	float WeaponXpos = 9.f;

public:

	Magnum(const std::string& textureId = "", const std::string& n = "");
	virtual ~Magnum() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flipX) override;

	virtual Types GetWeaponType() override { return weaponType; }

	void Shoot();
};

