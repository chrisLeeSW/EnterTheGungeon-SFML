#pragma once
#include "Scene.h"
#include "AnimationController.h"

class Player;
class SpriteGo;
class TileMap;
class InteractionObject;
class SceneLobby : public Scene
{
	
public:

	enum class Types
	{
		None,
		Pilot,
		Prisoner,
		WeaponPilot,
		WeaponPrsioner,
	};


protected:
	TileMap* lobby;
	std::vector<SpriteGo*> objects;
	
	Player* pilot;
	Player* prisoner;
	Player* currentplayer;

	SpriteGo* elevator;


	Types playertype;

	sf::Vector2f pilotSetPosition;
	sf::Vector2f prisonerSetPosition;

	int choiseindex = 1;

	bool playerchoise = false;

	bool playerface = true;
	AnimationController animation;

	sf::Sprite sprite;
	sf::Sprite spritehegemonyCredit;
	sf::Text textHegemonyCredit;
	sf::RectangleShape doorCollisionBox;

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
	void MakeLobby();
	void PlayerCollied();
};

