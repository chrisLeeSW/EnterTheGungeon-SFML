#pragma once
#include "DataTable.h"
#include "Bullet.h"

struct BulletInfo
{
	Bullet::Types bulletType;
	int speed;
	int damage;
	int range;
	int knockback;
};

class BulletTable :
    public DataTable
{

protected:

	std::unordered_map<Bullet::Types, BulletInfo> table;


public:
	BulletTable() : DataTable(DataTable::Ids::Bullet) {};
	virtual ~BulletTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	const BulletInfo* Get(Bullet::Types id);

};

