#include "stdafx.h"
#include "WeaponTable.h"

const WeaponInfo* WeaponTable::Get(Weapon::Types id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "총알 못찾았음" << std::endl;
		return nullptr;
	}

	return &(find->second);
}

bool WeaponTable::Load()
{
	std::string weaponfile = "tables/WeaponTable.csv";

	rapidcsv::Document doc(weaponfile);
	std::vector<int> ids = doc.GetColumn<int>(0);
	std::vector<float> weaponRate = doc.GetColumn<float>(1);
	std::vector<int> weaponbulletCount = doc.GetColumn<int>(2);
	std::vector<int> weaponbulletMax = doc.GetColumn<int>(3);
	std::vector<float> weaponReload = doc.GetColumn<float>(4);
	std::vector<int> weaponSantan = doc.GetColumn<int>(4);


	for (int i = 0; i < ids.size(); ++i)
	{
		WeaponInfo weaponinfo; 
		weaponinfo.weaponType = (Weapon::Types)ids[i];
		weaponinfo.attackrate = weaponRate[i];
		weaponinfo.bulletcount = weaponbulletCount[i];
		weaponinfo.bulletmax = weaponbulletMax[i];
		weaponinfo.reload = weaponReload[i];
		weaponinfo.santan = weaponSantan[i];
		//table.insert({ bulletinfo.bulletType ,bulletinfo });
		table.insert({ (Weapon::Types)ids[i] ,weaponinfo });
	}
	return true;
}

void WeaponTable::Release()
{
	table.clear();
}