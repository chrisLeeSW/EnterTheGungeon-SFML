#pragma once
#include "GameObject.h"
#include "AnimationController.h"
#include "Weapon.h"

class Player;
class Weapon;
class Active;

class PlayerUI : public GameObject
{

protected:

	sf::Vector2f windowsize;

	Player* player = nullptr;

	AnimationController pilotweapon;

	AnimationController currentweapon;

	std::vector<sf::Sprite> playermaxhp;
	std::vector<sf::Sprite> playerhp;
	std::vector<sf::Sprite> blankbullets;

	//SpriteGo* playerhp;
	sf::Sprite spritehp;
	sf::Sprite weaponBox;
	sf::Sprite weapon;
	sf::Sprite money;
	sf::Sprite key;
	sf::Sprite activeBox;
	sf::Sprite active;
	sf::Sprite reload;
	sf::Sprite reloadBar;
	sf::Text currentmoney;
	sf::Text currentkey;
	sf::Text currentMagazine;
	sf::Text remainingAmmo;

		int bulletcount;
	int bulletmax;
	Weapon* playerweapon = nullptr;
	Active* currentActive = nullptr;



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

	void CurrentActive(Active* active);

	void UseBlankBullet();

	void AddBlankBullet();
	void AddHp();
	void AdjustMoney();
	void AdjustKey();
};

