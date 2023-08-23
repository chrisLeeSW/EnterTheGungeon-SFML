#pragma once
#include "Weapon.h"
#include "AnimationController.h"

class Player;


class Pad : public Weapon

{
protected:

	Player* player = nullptr;

	Types weaponType;
	Bullet::Types bulletType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	int currentbulletcount;
	float reload;
	int santan;
	float tick;

	float reloadtick;

	bool isreload = false;
	bool flipX = false;

	AnimationController gun;
	AnimationController effect;

	float WeaponXpos = 9.f;

	sf::RectangleShape gunend;

	float commandtick = 0.5f;

	bool sKeyPressed = false;
	bool dKeyPressed = false;
	bool mouseClicked = false;

public:
	
	Item::Types itemtype = Item::Types::Pad;
	Item::WAP wap = Item::WAP::Weapon;

	sf::Sprite shooteffect;

	Pad(const std::string& textureId = "", const std::string& n = "");
	virtual ~Pad() override { Release(); }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetGunFlipx(bool flipX) override;

	virtual void SetType(Types t) override;
	virtual Types GetWeaponType() override { return weaponType; }
	virtual Bullet::Types GetBulletType() override { return bulletType; }

	virtual float GetReloadTime()override { return reload; }
	virtual float GetCurrentReloadTime()override { return reloadtick; }

	virtual void RequestReload() override { currentbulletcount = bulletcount; }

	virtual AnimationController* GetWeaponAnimation() override { return &gun; }

	virtual Item::Types GetItemType() { return itemtype; }
	virtual Item::WAP GetItemWAP() { return wap; }

};