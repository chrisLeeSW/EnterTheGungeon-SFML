#pragma once
#include "SpriteGo.h"
#include "UiButton.h"
#include "Weapon.h"
#include "AnimationController.h"

class TextGo;
class UIButton;

class Equipment : public SpriteGo
{

protected:

	AnimationController animation;

	sf::Vector2f windowsize;
	std::unordered_map<UiButton*, std::string> mapweapons;

	std::unordered_map<Item::Types, UiButton*> mapbuttons;

	std::vector<UiButton*> weaponsUI;

	UiButton* but1;

	sf::Sprite equWeapon;
	sf::Sprite equActive;
	sf::Sprite equPassive;

	sf::RectangleShape test1;
	sf::RectangleShape test2;
	sf::RectangleShape test3;

	sf::RectangleShape black;

	std::vector<UiButton*> weaponbuttons;
	std::vector<UiButton*> passivebuttons;
	std::vector<UiButton*> activeweaponbuttons;

	sf::Vector2f weaponline;
	sf::Vector2f passiveline;
	sf::Vector2f activeline;


	UiButton* pilotweapon;
	UiButton prisonerweapon;
	UiButton pad;
	UiButton prisonerPassive;
	UiButton pilotPassive;
	UiButton bulletTime;
	UiButton prisonerActive;


	bool bookOn = false;
	bool isSprite = false;

	bool draw;

public:

	Equipment(const std::string& textureId = "", const std::string& n = "");
	virtual ~Equipment() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void Insert();
	void GetItem(Weapon::Types type);
	void GetItem(Passive::Types type);
	void GetItem(Active::Types type);
};