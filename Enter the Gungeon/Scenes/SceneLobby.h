#pragma once
#include "Scene.h"

class Player;
class SpriteGo;
class Enemy; //test

class SceneLobby : public Scene
{
	
public:

	enum class Types
	{
		Pilot,
		Prisoner,
	};


protected:

	Player* pilot;
	Player* prisoner;
	Player* currentplayer;

	SpriteGo* elevator;


	Types playertype;

	sf::Vector2f pilotSetPosition;
	sf::Vector2f prisonerSetPosition;

	int choiseindex = 0;

	bool playerchoise = false;

	std::vector<SpriteGo*> currentchoise;

	SpriteGo* playerui;

	Enemy* test; //test

public:
	SceneLobby();
	virtual ~SceneLobby() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void PlayerChoise();

};

