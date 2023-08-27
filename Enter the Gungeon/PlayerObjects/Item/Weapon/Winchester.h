#pragma once
#include "Weapon.h"
#include "AnimationController.h"
#include "Bullet.h"

class Enemy;

class Winchester : public Weapon
{

protected:




public:

	Winchester(const std::string& textureId = "", const std::string& n = "");
	virtual ~Winchester() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flipX) override;


};