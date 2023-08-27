#pragma once
#include "Singleton.h"
#include "AnimationController.h"
#include "Item.h"
#include "Passive.h"
#include "Active.h"
#include "DropEquipItem.h"

class ItemMgr : public Singleton<ItemMgr>
{
	friend Singleton<ItemMgr>;


protected:

	ItemMgr() = default;
	virtual ~ItemMgr() override = default;

	std::unordered_map<Weapon::Types, Weapon*> mapWeapon;
	std::unordered_map<Passive::Types, Passive*> mapPassive;
	std::unordered_map<Active::Types, Active*> mapActive;

	float bulletTime = 0.2f;
	bool isbulletTime = false;

public:

	void Init();
	
	Passive* GetItem(Passive::Types type);
	Active* GetItem(Active::Types type);
	Weapon* GetItem(Weapon::Types type);

	DropEquipItem* GetDropItem();

	float BulletTime();
	void BulletTimeOn(bool bullettime);
	bool GetBulletTime();
};

#define ITEM_MGR (ItemMgr::Instance())