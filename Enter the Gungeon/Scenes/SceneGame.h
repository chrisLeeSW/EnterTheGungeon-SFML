#pragma once
#include "Scene.h"

class Player;
class Weapon;
class SpriteGo;
class TileMap;
class Equipment;
class Enemy;
class InteractionObject;
class PlayerUI;

struct RoomObjectsInfo
{
	MapObjectType type;
	InteractionObject* interactionObj;
};

class SceneGame : public Scene
{
protected:

	Player* player = nullptr;
	Weapon* weapon;
	SpriteGo* shadow;
	PlayerUI* playerui;


	Enemy* testenm1;
	Enemy* testenm2;
	Enemy* testenm3;

	std::vector<TileMap*> tileRoom;
	std::vector<SpriteGo*> objects;
	std::vector<RoomObjectsInfo> interaction;

	sf::RectangleShape shape;
	sf::RectangleShape shape2;

	std::vector<WallTypeInfo>colliedShape;

	int playertype;

	Equipment* equipment;

	std::list<Enemy*> enemylist;

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

	void MakeTestRoom(int size);
	void ColliedTest();
};

