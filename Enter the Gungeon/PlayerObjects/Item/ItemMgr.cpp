#include "stdafx.h"
#include "ItemMgr.h"
#include "Active.h"
#include "Passive.h"
#include "PilotActive.h"
#include "PrisonerActive.h"
#include "PrisonerPassive.h"
#include "PilotPassive.h"
#include "Item.h"
#include "PilotWeapon.h"
#include "PrisonerWeapon.h"
#include "Magnum.h"
#include "WeaponMgr.h"
#include "aBulletTime.h"
#include "ShotGun.h"
//#include "Pad.h"

void ItemMgr::Init()
{
	PilotActive* pilotActive = new PilotActive();
	PilotPassive* pilotPassive = new PilotPassive();
	PrisonerActive* prisonerActive = new PrisonerActive();
	PrisonerPassive* prisonerPassive = new PrisonerPassive();
	PilotWeapon* pilotWeapon = new PilotWeapon();
	PrisonerWeapon* prisonerWeapon = new PrisonerWeapon();
	Magnum* magnum = new Magnum();
	aBulletTime* abulletTime = new aBulletTime();
	ShotGun* shotgun = new ShotGun();
	//Pad* pad = new Pad();

	mapWeapon.insert({ Weapon::Types::Magnum,magnum });
	mapWeapon.insert({ Weapon::Types::PilotWeapon,pilotWeapon });
	mapWeapon.insert({ Weapon::Types::PrisonerWeapon,prisonerWeapon });
	mapWeapon.insert({ Weapon::Types::ShotGun, shotgun });
	//mapWeapon.insert({ Weapon::Types::Pad, pad });

	mapPassive.insert({ Passive::Types::PilotPassive,pilotPassive });
	mapPassive.insert({ Passive::Types::PrisonerPassive,prisonerPassive });

	mapActive.insert({ Active::Types::PilotActive,pilotActive });
	mapActive.insert({ Active::Types::PrisonerActive,prisonerActive });
	mapActive.insert({ Active::Types::BulletTime, abulletTime });

	WEAPON_MGR.Init();
}


Passive* ItemMgr::GetItem(Passive::Types id)
{
	auto find = mapPassive.find(id);
	return find->second;
}

Active* ItemMgr::GetItem(Active::Types id)
{
	auto find = mapActive.find(id);
	return find->second;
}

Weapon* ItemMgr::GetItem(Weapon::Types id)
{
	auto find = mapWeapon.find(id);
	return find->second;
}

float ItemMgr::BulletTime()
{
	return bulletTime;
}

void ItemMgr::BulletTimeOn(bool bullettime)
{
	isbulletTime = bullettime;
}

bool ItemMgr::GetBulletTime()
{
	return isbulletTime;
}