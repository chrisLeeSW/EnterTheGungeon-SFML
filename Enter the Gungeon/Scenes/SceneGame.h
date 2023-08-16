#pragma once
#include "Scene.h"

class Player;
class Weapon;
class SpriteGo;
class TileMap;
class Equipment;
class Enemy;

class SceneGame : public Scene
{
protected:

	Player* player = nullptr;
	Weapon* weapon;
	SpriteGo* shadow;

	Enemy* testenm1;

	TileMap* gameDevMap;

	int playertype;

	Equipment* equipment;

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPlayer(int a);

};

