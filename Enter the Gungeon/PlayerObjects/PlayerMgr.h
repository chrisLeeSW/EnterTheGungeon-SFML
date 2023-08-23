#pragma once
#include "Player.h"
#include "Singleton.h"
#include "AnimationController.h"
#include "Book.h"

class SpriteGo;
class Player;
class Book;

class PlayerMgr : public Singleton<PlayerMgr>
{
	friend Singleton<PlayerMgr>;

protected:

	PlayerMgr() = default;
	virtual ~PlayerMgr() override = default;

	std::vector<SpriteGo> currentchoise;
	std::vector<Player*> Players;

	bool isPause = false;

	AnimationController pilotchoise;
	AnimationController prisonerchoise;


public:
	Player* player = nullptr;
	Book* book = nullptr;
	void Init();
	void Release();

	void SetPlayer(Player* player) {this->player = player;}
	Player* GetPlayer() { return player; }

	void SetBook(Book* book) { this->book = book; }
	Book* GetBook() { return book; }


	void ChangeCurrentChoise(AnimationController choise);

	bool IsPause() { return isPause; }
	void SetPause(bool pause) { isPause = pause; }
};

#define PLAYER_MGR (PlayerMgr::Instance())
