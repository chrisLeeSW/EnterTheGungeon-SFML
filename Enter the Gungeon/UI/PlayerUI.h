#pragma once
#include "GameObject.h"
#include "AnimationController.h"
#include "Weapon.h"

class Player;
class Weapon;

class PlayerUI : public GameObject
{

protected:

	sf::Vector2f windowsize;

	Player* player = nullptr;

	AnimationController pilotweapon;

	AnimationController currentweapon;

	std::vector<sf::Sprite> playermaxhp;
	std::vector<sf::Sprite> playerhp;

	//SpriteGo* playerhp;
	sf::Sprite spritehp;
	sf::Sprite weaponBox;

	Weapon* playerweapon = nullptr;

	sf::Sprite weapon;

	bool isone = true;

public:

	PlayerUI(Player* player, const std::string& textureId = "", const std::string& n = "");
	virtual ~PlayerUI() override { Release(); }


	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void IsHited();
	sf::Sprite CreateSprite(sf::Texture* texture, float x, float y);

	sf::Sprite CreateSprite2(sf::Texture* texture, float x, float y);

	//void WeaponUI(Weapon::Types type);

	void CurrentWeapon(Weapon* weapon);

};

