#include "stdafx.h"
#include "EnemyTable.h"

bool EnemyTable::Load()
{
	std::string enemyfile = "tables/EnemyTable.csv";

	rapidcsv::Document doc(enemyfile);
	std::vector<int> enemyType = doc.GetColumn<int>(0);
	std::vector<int> enemyWeapon = doc.GetColumn<int>(1);
	std::vector<float> enemyHp = doc.GetColumn<float>(2);
	std::vector<float> enemySpeed = doc.GetColumn<float>(3);
	std::vector<float> enemyAttackRange = doc.GetColumn<float>(4);
	std::vector<float> enemyAttackInterval = doc.GetColumn<float>(5);
	std::vector<int> enemySuperarmor = doc.GetColumn<int>(6);


	for (int i = 0; i < enemyType.size(); i++)
	{
		EnemyInfo info;
		info.type = (Enemy::EnemyName)enemyType[i];
		info.weaponType = (Weapon::Types)enemyWeapon[i];
		info.maxHp = enemyHp[i];
		info.speed = enemySpeed[i];
		info.attackRange = enemyAttackRange[i];
		info.attackInterval = enemyAttackInterval[i];
		info.superarmor = (bool)enemySuperarmor[i];

		table.insert({ (Enemy::EnemyName)enemyType[i], info });
	}
	return true;
}

void EnemyTable::Release()
{
    table.clear();
}

const EnemyInfo* EnemyTable::Get(Enemy::EnemyName id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "WARNING: Not Exist EnemyName (EnemyTable Get(Enemy::EnemyName id))" << std::endl;
		return nullptr;
	}

	return &(find->second);
}
