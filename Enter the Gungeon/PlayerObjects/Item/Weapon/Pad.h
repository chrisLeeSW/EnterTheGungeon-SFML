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
	virtual void GetAmmunition() override { currentbulletmax = bulletmax; }

	virtual float GetReloadTime()override { return reload; }
	virtual float GetCurrentReloadTime()override { return reloadtick; }
	virtual int GetCurrentBulleCount() override { return currentbulletcount; }
	virtual int GetRemainingAmmo() override { return bulletmax; }

	virtual void RequestReload() override { currentbulletcount = bulletcount; }

	virtual AnimationController* GetWeaponAnimation() override { return &gun; }

	virtual Item::Types GetItemType() { return itemtype; }
	virtual Item::WAP GetItemWAP() { return wap; }

};