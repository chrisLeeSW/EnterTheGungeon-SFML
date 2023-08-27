#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Player;
class Weapon;
class SpriteGo;

class Book;
class Enemy;
class DropItem;
class Npc;
class Chest;
class SpriteEffect;

class PlayerUI;

class Boss;
class BossUI;
class EnemyBullet;

/// 
class Room;
class TileMap;
class InteractionObject;
class Door;
//
class SceneGame : public Scene
{
public :
	//
	enum class DoorDirection
	{
		None = -1,
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
		std::vector< Enemy*> monster;

	};
	struct Passage {
		sf::Vector2f from, to;
	};
	struct DoorInfo
	{
		sf::Vector2f pos;
		DoorDirection dir;
	};
	//
protected:

	Player* player = nullptr;
	Weapon* weapon;
	SpriteGo* shadow;
	PlayerUI* playerui;

	ObjectPool<EnemyBullet> enemyBullets;
	ObjectPool<DropItem> dropitemPool;
	ObjectPool<SpriteEffect> effectPool;

	BossUI* bossui;
	Npc* shopowner;
	Chest* chestTest;

	int playertype;
	Book* book;
//
	Room* rooms;
	std::vector<std::string> fileList;
	std::vector<std::string> sponRoomFileList;
	std::vector<std::string> bossRoomFileList;
	std::vector<RandomMapInfo> tileRoom;
	std::vector<sf::RectangleShape> roomShape;
	std::vector<Passage> passages;
	std::vector<bool> connected;
	std::vector<DoorInfo> doorInfo;
	std::vector<sf::RectangleShape> doorShape;

	std::vector<sf::RectangleShape> tunnel;
	Npc* npc;
	Chest* chest;
	Boss* boss;
	std::vector<Door*> doors;
	std::vector<SpriteGo*> tunnelSprite;
	std::list<SpriteGo*> tunnelWall;


	int bossRoom;
	int currentTunnel=0;
	int currentRoom=0;
	bool colliedDoor=false;

	bool colliedDraw = false;
//
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

	void MakeRoom();

	void SetBossUI(Boss* boss);
	void RenewBossUI();

	ObjectPool<EnemyBullet>& GetPoolEnemyBullet();
	ObjectPool<DropItem>& GetPoolDropItem();
	ObjectPool<SpriteEffect>& GetPoolSpriteEffect();

	void OverwriteCSV(const std::string& filepath);

	bool ValidFilePath(const std::string& filepath);

	template <typename T>
	void ClearPool(ObjectPool<T>& pool);



	///
	void ListFilesInDirectory(const std::string& folderPath, std::vector<std::string>& fileList);
	void NearRoomConnectRoom();
	void ConnectRooms(TileMap* r1, TileMap* r2);
	bool isIntersecting(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2);
	sf::Vector2f intersectionPoint(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2);
	bool isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, sf::Vector2f& intersection);
	std::vector<DoorInfo> isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, std::vector<DoorInfo>& room);
	void SettingDoorPosition();
	void MakeDoor();
	void CreateTunnel(sf::Vector2f start, sf::Vector2f end);
	void RemoveWall();
	void FindBossRoom();
	void CoiledPlayerByMap();
	void SetMonsterByPlayer();
	//
};

template<typename T>
inline void SceneGame::ClearPool(ObjectPool<T>& pool)
{
	for (auto it : pool.GetUseList())
	{
		RemoveGo(it);
	}
	pool.Clear();
}