#pragma once
#include"DataTable.h"
#include"Player.h"

struct PlayerInfo
{
	Player::Types playerType;
	int passive;
	int active;
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
