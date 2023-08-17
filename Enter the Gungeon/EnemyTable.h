#pragma once
#include "DataTable.h"
#include "Enemy.h"

struct EnemyInfo
{
	Enemy::EnemyName type;
	Weapon::Types weaponType;
	float maxHp;
	float speed;
	float attackRange;
	float attackInterval;
	bool superarmor;
};

class EnemyTable : public DataTable
{
protected:

	std::unordered_map<Enemy::EnemyName, EnemyInfo> table;

public:
	EnemyTable() : DataTable(DataTable::Ids::Enemy) {};
	virtual ~EnemyTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	const EnemyInfo* Get(Enemy::EnemyName id);
};