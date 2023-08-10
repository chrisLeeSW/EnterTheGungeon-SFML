#include "stdafx.h"
#include "PlayerTable.h"

const PlayerInfo* PlayerTable::Get(Player::Types id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "플레이어 못찾았음" << std::endl;
		return nullptr;
	}

	return &(find->second);
}

bool PlayerTable::Load()
{
	std::string playerfile = "tables/PlayerTable.csv";

	rapidcsv::Document doc(playerfile);
	std::vector<int> ids = doc.GetColumn<int>(0);
	std::vector<int> passive = doc.GetColumn<int>(1);
	std::vector<int> active = doc.GetColumn<int>(2);

	for (int i = 0; i < ids.size(); ++i)
	{
		PlayerInfo playerinfo;
		playerinfo.playerType = (Player::Types)ids[i];
		playerinfo.passive = passive[i];
		playerinfo.active = active[i];
		//table.insert({ bulletinfo.bulletType ,bulletinfo });
		table.insert({ (Player::Types)ids[i] ,playerinfo });
	}
	return true;
}

void PlayerTable::Release()
{
	table.clear();
}