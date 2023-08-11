#include "stdafx.h"
#include "PrisonerWeapon.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"


PrisonerWeapon::PrisonerWeapon(const std::string& textureId, const std::string& n)
{
}

void PrisonerWeapon::Init()
{
}

void PrisonerWeapon::Release()
{
}

void PrisonerWeapon::Reset()
{
}

void PrisonerWeapon::Update(float dt)
{

}

void PrisonerWeapon::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PrisonerWeapon::SetGunFlipx(bool flip)
{
	this->flipX = flip;
	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void PrisonerWeapon::SetPlayer(Player* player)
{
	this->player = player;
}

void PrisonerWeapon::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}
