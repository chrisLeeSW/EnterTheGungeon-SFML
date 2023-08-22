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

	std::unordered_map<ItemButton*, std::string> mapString;

	std::unordered_map<Weapon::Types, ItemButton*> mapWeapon;
	std::unordered_map<Passive::Types, ItemButton*> mapPassive;
	std::unordered_map<Active::Types, ItemButton*> mapActvie;



	std::vector<ItemButton*> weaponsUI;

	ItemButton* but1;

	sf::Sprite equWeapon;
	sf::Sprite equActive;
	sf::Sprite equPassive;

	sf::RectangleShape test1;
	sf::RectangleShape test2;
	sf::RectangleShape test3;

	sf::RectangleShape black;

	std::vector<ItemButton> weaponbuttons;
	std::vector<ItemButton> passivebuttons;
	std::vector<ItemButton> activebuttons;

	sf::Vector2f weaponline;
	sf::Vector2f passiveline;
	sf::Vector2f activeline;

	ItemButton& it;


	bool bookOn = false;
	bool isSprite = false;

	bool draw;

public:

	Book(const std::string& textureId = "", const std::string& n = "");
	virtual ~Book() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void Insert();
	void GetItem(Item::Types t, Item::WAP w);
};