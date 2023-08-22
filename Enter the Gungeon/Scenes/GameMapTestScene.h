#pragma once
#include "Scene.h"


class TileMap;
class SpriteGo;
class InteractionObject;
class BSPNode;
class Room1;
struct RoomObjectsInfoTest
{
	MapObjectType type;
	InteractionObject* interactionObj;
};

class GameMapTestScene :public Scene
{
protected:
	TileMap* tileRoom1;
	TileMap* rooms;
	BSPNode* root;
	Room1* room;
public:
	GameMapTestScene();
	virtual ~GameMapTestScene() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void GenerateTileMap(BSPNode* node);
};

