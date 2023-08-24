#include "stdafx.h"
#include "BulletTable.h"

const BulletInfo* BulletTable::Get(Bullet::Types id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "총알 못찾았음" << std::endl;
		return nullptr;
	}

	return &(find->second);
}

bool BulletTable::Load()
{
	std::string bulletfile = "tables/BulletTable.csv";

	rapidcsv::Document doc(bulletfile);
	std::vector<int> ids = doc.GetColumn<int>(0);
	std::vector<std::string> bulletids = doc.GetColumn<std::string>(1);
	std::vector<float> bulletSpeed = doc.GetColumn<float>(2);
	std::vector<float> bulletDamage = doc.GetColumn<float>(3);
	std::vector<float> bulletrange = doc.GetColumn<float>(4);
	std::vector<float> bulletkonckback = doc.GetColumn<float>(5);

	for (int i = 0; i < ids.size(); ++i)
	{
		BulletInfo bulletinfo;
		bulletinfo.bulletType = (Bullet::Types)ids[i];
		bulletinfo.bulletid = bulletids[i];
		bulletinfo.speed = bulletSpeed[i];
		bulletinfo.damage = bulletDamage[i];
		bulletinfo.range = bulletrange[i];
		bulletinfo.knockback = bulletkonckback[i];

		table.insert({ (Bullet::Types)ids[i] ,bulletinfo });
	}
	return true;
}

void BulletTable::Release()
{
	table.clear();
}