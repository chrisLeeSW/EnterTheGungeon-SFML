#pragma once
#include "Scene.h"


class Room;
class TileMap;
class InteractionObject;
class SpriteGo;

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

	bool test = false;
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
	std::vector<sf::Vector2f> isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, std::vector<sf::Vector2f>& room);
};


