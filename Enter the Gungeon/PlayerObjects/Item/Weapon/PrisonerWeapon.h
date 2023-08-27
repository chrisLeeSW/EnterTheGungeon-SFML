#pragma once
#include "Weapon.h"

class Player;



class PrisonerWeapon : public Weapon
{
protected:


public:

	Item::Types itemtype = Item::Types::PrisonerWeapon;
	Item::WAP wap = Item::WAP::Weapon;

	PrisonerWeapon(const std::string& textureId = "", const std::string& n = "");
	virtual ~PrisonerWeapon() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


	virtual Item::Types GetItemType() { return itemtype; }
	virtual Item::WAP GetItemWAP() { return wap; }
};

