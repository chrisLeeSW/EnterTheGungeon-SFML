#pragma once
#include "Scene.h"

class TileMap;
class GameMapTestScene :public Scene
{
protected:
	TileMap* tileRoom1;
	TileMap* objectRoom1;

	TileMap* tileRoom2;
	TileMap* objectRoom2;
public:
	GameMapTestScene();
	virtual ~GameMapTestScene() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

