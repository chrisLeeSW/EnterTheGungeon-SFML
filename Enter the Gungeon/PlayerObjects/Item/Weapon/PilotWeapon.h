#pragma once
#include "Weapon.h"
#include "AnimationController.h"

class Player;

class PilotWeapon : public Weapon
{
protected:


	

public:

	Item::Types itemtype = Item::Types::PilotWeapon;
	Item::WAP wap = Item::WAP::Weapon;


	PilotWeapon(const std::string& textureId = "", const std::string& n = "");
	virtual ~PilotWeapon() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetType(Types t) override;

	virtual Item::Types GetItemType() { return itemtype; }
	virtual Item::WAP GetItemWAP() { return wap; }


};

