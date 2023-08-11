#pragma once
#include "Weapon.h"

class Player;

class Ak47 : public Weapon
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

public:

	Ak47(const std::string& textureId = "", const std::string& n = "");
	virtual ~Ak47() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flip) override;

	virtual void SetPlayer();
	virtual void SetType(Types t);
};

