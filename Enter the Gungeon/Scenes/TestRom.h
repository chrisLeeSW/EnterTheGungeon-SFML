#pragma once
#include "Scene.h"


class Room;
class TileMap;
class InteractionObject;
class SpriteGo;
class Door;
class Player;
class Enemy;
enum class DoorDirection
{
	None =-1,
	Up,
	Down,
	Left,
	Right
};
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
	std::vector<WallTypeInfo> roomtype;
	std::vector< Enemy*> monster;
	// 몬스터 리스트 추가 
};
struct Passage {
	sf::Vector2f from, to;
};
struct DoorInfo
{
	sf::Vector2f pos;
	DoorDirection dir;
};
class TestRom : public Scene
{
protected:
	Room* rooms;
	sf::RectangleShape shape;
	std::vector<std::string> fileList;
	std::vector<RandomMapInfo> tileRoom;
	std::vector<Passage> passages;
	std::vector<bool> connected;
	std::vector<sf::RectangleShape> tunnel;
	std::vector<DoorInfo> doorInfo;
//	std::vector<sf::Vector2f> position2;
	std::vector<sf::RectangleShape> doorShape;
	std::vector<sf::CircleShape> circle;
	int length = 0;

	std::vector<Door*> doors;
	Player* player = nullptr;
	bool test = false;
	std::vector<SpriteGo*> tunnelSprite;
	std::list<SpriteGo*> tunnelWall;

	int currentRoom = 0;
	int currentTunnel = 0;
	bool colliedDoor = false;
	std::vector<sf::RectangleShape> roomShape;
	std::vector<sf::RectangleShape> doorShape2;

	sf::Vector2f prevPlayerPos;
	int lastRoom = 0;
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
	sf::Vector2f Center( TileMap* room);
	void ConnectRooms(TileMap* r1 , TileMap* r2);
	void CreateTunnel(sf::Vector2f start, sf::Vector2f end);
	bool isIntersecting(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2);
	sf::Vector2f intersectionPoint(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2);
	bool isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, sf::Vector2f& intersection);
	std::vector<DoorInfo> isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, std::vector<DoorInfo>& room);

	void CoiledPlayerByMap();
};


