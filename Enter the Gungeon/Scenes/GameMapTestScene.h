#pragma once
#include "Scene.h"

class TileMap;
class SpriteGo;
class InteractionObject;

struct RoomObjectsInfoTest
{
	MapObjectType type;
	InteractionObject* interactionObj;
};

class GameMapTestScene :public Scene
{
protected:
	TileMap* tileRoom1;
	TileMap* tileRoom2;
	std::vector<SpriteGo*> objects;
	std::vector<RoomObjectsInfoTest> interaction;

	sf::RectangleShape shape;
	sf::RectangleShape shape2;

	std::vector<WallTypeInfo>colliedShape;
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

