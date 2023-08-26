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
	sf::Vector2f startTileRoom;
	sf::Vector2i tileWallSize;
	TileMap* tileRoom1;
	std::vector<SpriteGo*> objects;
	std::vector<RoomObjectsInfoTest> interaction;
	
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

