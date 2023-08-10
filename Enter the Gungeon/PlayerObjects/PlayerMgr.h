#pragma once
#include "Player.h"
#include "Singleton.h"
#include "AnimationController.h"

class SpriteGo;

class PlayerMgr : public Singleton<PlayerMgr>
{
	friend Singleton<PlayerMgr>;

protected:

	PlayerMgr() = default;
	virtual ~PlayerMgr() override = default;

	std::vector<SpriteGo> currentchoise;
	std::vector<Player*> Players;

	AnimationController pilotchoise;
	AnimationController prisonerchoise;


public:

	void Init();
	void Release();

	void ChangeCurrentChoise(AnimationController choise);

};

#define PLAYER_MGR (PlayerMgr::Instance())
