#pragma once
#include "Weapon.h"
#include "AnimationController.h"

class Player;


class Pad : public Weapon
{
protected:


	float commandtick = 0.5f;

	bool sKeyPressed = false;
	bool dKeyPressed = false;
	bool mouseClicked = false;

public:
	
	Item::Types itemtype = Item::Types::Pad;
	Item::WAP wap = Item::WAP::Weapon;


	Pad(const std::string& textureId = "", const std::string& n = "");
	virtual ~Pad() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual Item::Types GetItemType() { return itemtype; }
	virtual Item::WAP GetItemWAP() { return wap; }

};