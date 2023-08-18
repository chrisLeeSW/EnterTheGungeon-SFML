#pragma once
#include "Scene.h"
class Room;
class TileMap;
class InteractionObject;
class SpriteGo;

struct RoomObjectsInfoTest1
{
	MapObjectType type;
	InteractionObject* interactionObj;
};
struct RandomMapInfo
{
	TileMap* map;
	std::vector<SpriteGo*> spr;
	std::vector<RoomObjectsInfoTest1> roomobj;

	// 몬스터 리스트 추가 
};

class TestRom : public Scene
{
protected:
	Room* rooms;
	sf::RectangleShape shape;
	std::vector<std::string> fileList;
	std::vector<RandomMapInfo> tileRoom;
public :
	TestRom();
	virtual ~TestRom() override = default;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;


	void MoveWorldView();
	void ListFilesInDirectory(const std::string& folderPath);
};

