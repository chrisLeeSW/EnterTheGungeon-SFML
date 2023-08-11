#pragma once
#include "DataTable.h"
#include "Weapon.h"

struct WeaponInfo
{
	Weapon::Types weaponType;
	float attackrate;
	int bulletcount;
	int bulletmax;
	float reload;
	int santan;
};

class WeaponTable : public DataTable
{

protected:

	std::unordered_map<Weapon::Types, WeaponInfo> table;


public:
	WeaponTable() : DataTable(DataTable::Ids::Weapon) {};
	virtual ~WeaponTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	const WeaponInfo* Get(Weapon::Types id);

};


