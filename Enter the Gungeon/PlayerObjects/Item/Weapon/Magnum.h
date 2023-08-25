#pragma once
#include "Weapon.h"
#include "AnimationController.h"
#include "Bullet.h"

class Player;
class Enemy;



class Magnum : public Weapon
{

protected:



public:

	Magnum(const std::string& textureId = "", const std::string& n = "");
	virtual ~Magnum() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flipX) override;



};

