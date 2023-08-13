#pragma once
#include "Player.h"
#include "Singleton.h"
#include "AnimationController.h"

class SpriteGo;
class Player;

class PlayerMgr : public Singleton<PlayerMgr>
{
	friend Singleton<PlayerMgr>;

protected:

	PlayerMgr() = default;
	virtual ~PlayerMgr() override = default;

	std::vector<SpriteGo> currentchoise;
	std::vector<Player*> Players;

	Player* player = nullptr;

	AnimationController pilotchoise;
	AnimationController prisonerchoise;


public:

	void Init();
	void Release();

	void SetPlayer(Player* player) {this->player = player;}
	Player* GetPlayer() { return player; }

	void ChangeCurrentChoise(AnimationController choise);

};

#define PLAYER_MGR (PlayerMgr::Instance())
