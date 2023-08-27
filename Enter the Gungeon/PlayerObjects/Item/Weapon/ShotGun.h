#pragma once
#include "Weapon.h"


class ShotGun : public Weapon
{

protected:


public:

	Item::Types itemtype = Item::Types::ShotGun;
	Item::WAP wap = Item::WAP::Weapon;

	ShotGun(const std::string& textureId = "", const std::string& n = "");
	virtual ~ShotGun() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


	virtual Item::Types GetItemType() { return itemtype; }
	virtual Item::WAP GetItemWAP() { return wap; }

};