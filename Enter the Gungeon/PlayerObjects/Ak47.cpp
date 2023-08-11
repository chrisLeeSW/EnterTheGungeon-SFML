#include "stdafx.h"
#include "Ak47.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "WeaponMgr.h"

Ak47::Ak47(const std::string& textureId, const std::string& n)
{
}

void Ak47::Init()
{
}

void Ak47::Release()
{
}

void Ak47::Reset()
{
}

void Ak47::Update(float dt)
{

}

void Ak47::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Ak47::SetGunFlipx(bool flipX)
{
}

void Ak47::SetPlayer()
{
	this->player = WEAPON_MGR.GetPlayer();
}

void Ak47::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}
