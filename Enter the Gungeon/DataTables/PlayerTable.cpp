#include "stdafx.h"
#include "PlayerTable.h"
#include "Weapon.h"
#include "Passive.h"
#include "Active.h"
#include "Player.h"


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
	std::vector<int> actives = doc.GetColumn<int>(1);
	std::vector<int> passives = doc.GetColumn<int>(2);
	std::vector<int> weapons = doc.GetColumn<int>(3);
	std::vector<float> speeds = doc.GetColumn<float>(4);
	std::vector<float> rollspeeds = doc.GetColumn<float>(5);
	std::vector<int> maxHps = doc.GetColumn<int>(6);
	std::vector<int> isGames = doc.GetColumn<int>(7);
	std::vector<int> isLobbys = doc.GetColumn<int>(8);
	std::vector<int> blankbullets = doc.GetColumn<int>(9);
	std::vector<float> hitDelays = doc.GetColumn<float>(10);

	for (int i = 0; i < ids.size(); ++i)
	{
		PlayerInfo playerinfo;
		playerinfo.type = (Player::Types)ids[i];
		playerinfo.activetype = (Active::Types)actives[i];
		playerinfo.passivetype = (Passive::Types)passives[i];
		playerinfo.weapontype = (Weapon::Types)weapons[i];
		playerinfo.speed = speeds[i];
		playerinfo.rollspeed = rollspeeds[i];
		playerinfo.maxHp = maxHps[i];
		playerinfo.isGame = (bool)isGames[i];
		playerinfo.isLobby = (bool)isLobbys[i];
		playerinfo.blankBulletCount = blankbullets[i];
		playerinfo.hitDelay = hitDelays[i];

		//table.insert({ bulletinfo.bulletType ,bulletinfo });
		table.insert({ (Player::Types)ids[i] ,playerinfo });
	}
	return true;
}

void PlayerTable::Release()
{
	table.clear();
}