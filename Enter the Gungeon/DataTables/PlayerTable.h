#pragma once
#include"DataTable.h"
#include"Player.h"
#include "Active.h"
#include "Passive.h"
#include "Weapon.h"

struct PlayerInfo
{
	Player::Types type;
	Active::Types activetype;
	Passive::Types passivetype;
	Weapon::Types weapontype;
	float speed;
	float rollspeed;
	int maxHp;
	int blankBulletCount;
	float hitDelay;
	bool isGame;
	bool isLobby;
};

class PlayerTable : public DataTable
{

protected:

	std::unordered_map<Player::Types, PlayerInfo> table;


public:
	PlayerTable() : DataTable(DataTable::Ids::Player) {};
	virtual ~PlayerTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	const PlayerInfo* Get(Player::Types id);

};
