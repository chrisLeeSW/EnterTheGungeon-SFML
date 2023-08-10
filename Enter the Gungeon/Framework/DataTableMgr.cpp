#include "stdafx.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "BulletTable.h"
#include "WeaponTable.h"
#include "PlayerTable.h"

void DataTableMgr::LoadAll()
{
	//tables.insert({ DataTable::Ids::String, new StringTable() });

	tables.insert({ DataTable::Ids::Bullet, new BulletTable() });
	tables.insert({ DataTable::Ids::Weapon, new WeaponTable() });
	tables.insert({ DataTable::Ids::Player, new PlayerTable() });

	for (auto pair : tables)
	{
		if (!pair.second->Load())
		{
			std::cout << "ERR: DATA TABLE LOAD FAIL" << std::endl;
			exit(-1);
		}
	}
}

void DataTableMgr::ReleaseAll()
{
	for (auto pair : tables)
	{
		//pair.second->Release();
		delete pair.second;
	}
	tables.clear();
}
