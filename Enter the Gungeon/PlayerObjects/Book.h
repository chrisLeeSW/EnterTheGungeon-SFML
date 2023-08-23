#pragma once
#include "SpriteGo.h"
#include "ItemButton.h"
#include "Weapon.h"
#include "AnimationController.h"

class TextGo;
class ItemButton;
class Player;

class Book : public SpriteGo
{

protected:
	Player* player;

	AnimationController animation;

	sf::Vector2f windowsize;


	ItemButton* currentClickButton = nullptr;


	sf::RectangleShape black;

	std::vector<ItemButton*> weaponbuttons;
	std::vector<ItemButton*> passivebuttons;
	std::vector<ItemButton*> activebuttons;

	sf::Vector2f weaponline;
	sf::Vector2f passiveline;
	sf::Vector2f activeline;




	bool bookOn = false;
	bool isSprite = false;
	bool isBookOpen = false;

	bool draw;

public:

	Book(const std::string& textureId = "", const std::string& n = "");
	virtual ~Book() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetCurrentClickButton(ItemButton* button) { currentClickButton = button; }

	void GetItem(Item::Types t, Item::WAP w);
};