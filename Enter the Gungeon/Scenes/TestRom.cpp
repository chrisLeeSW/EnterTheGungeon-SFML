#include "stdafx.h"
#include "TestRom.h"
#include "Room.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "InteractionObject.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Npc.h"
TestRom::TestRom() :Scene(SceneId::TestRoom)
{
	resourceListPath = "script/GameMapTestScene.csv";
}

void TestRom::Init()
{


	rooms = new Room();
	shape.setSize({ 25, 25 });
	ListFilesInDirectory("Room/TileMapFile/", fileList);
	ListFilesInDirectory("Room/TileMapFile/SponRoom/", sponRoomFileList); 
	ListFilesInDirectory("Room/TileMapFile/BossRoom/", bossRoomFileList);
	int count = 0;
	int rnadFileNumber = 0;
	int sponRoom = Utils::RandomRange(0, sponRoomFileList.size());
	int bossRoom = Utils::RandomRange(0, bossRoomFileList.size());
	// player에게  sort Layer 1을 주자
	bool boosRoomMake = false;
	bool storeRoomMake = false;

	int roomRandBoss = Utils::RandomRange(1, rooms->GetRoom().size());
	int RandStore;
	int eventRoom;
	while (true)
	{
		RandStore = Utils::RandomRange(1, rooms->GetRoom().size());
		if ( RandStore!= roomRandBoss) break;
	}
	while (true)
	{
		eventRoom = Utils::RandomRange(1, rooms->GetRoom().size());
		if (eventRoom != rooms->GetLastRoom() && eventRoom != RandStore) break;
	}
	while (count != rooms->GetRoom().size())
	{
		bool collied = false;
		rnadFileNumber = Utils::RandomRange(0, fileList.size());
		TileMap* map = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		// sf::Vector2f pos = { rooms->Center(rooms->GetRoomIndex(count)) };
		sf::Vector2f pos = { rooms->GetRoomIndex(count).x,rooms->GetRoomIndex(count).y };
		sf::Vector2f tileMapSize;
		map->SetStartPos(pos);
		if (count == 0)
		{
			tileMapSize = map->TileMapSize(sponRoomFileList[sponRoom]);
		}
		else if (count == rooms->GetLastRoom())
		{
			tileMapSize = map->TileMapSize(bossRoomFileList[bossRoom]);
		}
		else if (count == RandStore)
		{
			tileMapSize = map->TileMapSize("Room/TileMapFile/StoreRoom/StoreRoom1.csv");
		}
		else if (count == eventRoom)
		{
			tileMapSize = map->TileMapSize("Room/TileMapFile/EventRoom/EventRoom1.csv");
		}
		else
		{
			tileMapSize = map->TileMapSize(fileList[rnadFileNumber]);
		}
		
		sf::Vector2f objpos = pos;
		objpos -= tileMapSize * 0.5f;
		objpos += map->GetTileSize() * 0.5f;

		if (rooms->GetRoomIndex(count).width < tileMapSize.x ||
			rooms->GetRoomIndex(count).height < tileMapSize.y)
		{
			continue;
		}


		
		if (count == 0)
		{
			map->Load(sponRoomFileList[sponRoom]);
		}
		else if (count == rooms->GetLastRoom())
		{
			map->Load(bossRoomFileList[bossRoom]);
		}
		else if (count == RandStore)
		{
			map->Load("Room/TileMapFile/StoreRoom/StoreRoom1.csv");
		}
		else if (count == eventRoom)
		{
			map->Load("Room/TileMapFile/EventRoom/EventRoom1.csv");
		}
		else
		{
			map->Load(fileList[rnadFileNumber]);
		}
	
		map->SetOrigin(Origins::MC);
		map->sortLayer = -1;
		std::vector<SpriteGo*> objects;
		std::vector<RoomObjectsInfoTest1> interaction;
		std::vector<Enemy*> monsters;
		for (int i = 0; i < map->tiles.size(); ++i)
		{
			switch (static_cast<MapObjectType>(map->tiles[i].objectTypes))
			{

			case MapObjectType::NormalWallTop:
			case MapObjectType::NorMalWallRight:
			case MapObjectType::LightWallTop:
			case MapObjectType::LightWallLeft:
			case MapObjectType::LightWallRight:
			case MapObjectType::LibraryTop:
			case MapObjectType::LibraryLeft:
			case MapObjectType::LibraryRight:
			case MapObjectType::LibraryDown:
			case MapObjectType::StoreTop:
			case MapObjectType::StoreRight:
			case MapObjectType::StoreLeft:
			case MapObjectType::StoreTableDisplay1:
			case MapObjectType::StoreTableDisplay2:
			case MapObjectType::NormalWallLeft:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,(map->tiles[i].objectTypes * 50),50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::TreasureAlter:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,(map->tiles[i].objectTypes * 50),50,50 });
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::StoreTable1:
			case MapObjectType::StoreTable2:
			case MapObjectType::StoreTable3:
			case MapObjectType::StoreTable4:
			case MapObjectType::StoreTable5:
			case MapObjectType::StoreTable6:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,(map->tiles[i].objectTypes * 50),50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr);

				// 아이템 요기에 생성하게 해야함상점 진열 굿!
			}
			break;
			case MapObjectType::Armor:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 2,39,12,20 });
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::Chiar:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 2,63,14,21 });
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::Pot:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 7,148,13,16 });
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::MonsterKin:
			{
				Enemy* monster = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::BulletKin));
				monster->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				monsters.push_back(monster);
			}
			break;
			case MapObjectType::MonsterKinKey:
			{
				Enemy* monster = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::KeyBulletKin));
				monster->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				monsters.push_back(monster);
			}
			break;
			case MapObjectType::MonsterBlue:
			{
				Enemy* monster = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::ShotgunKinBlue));
				monster->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				monsters.push_back(monster);
			}
			break;
			case MapObjectType::MonsterRed:
			{
				Enemy* monster = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::ShotgunKinRed));
				monster->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				monsters.push_back(monster);
			}
			case MapObjectType::Boss:
			{
				Enemy* monster = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::GatlingGull));
				monster->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				monsters.push_back(monster);
			}
			break;
			case MapObjectType::StoreOner :
			{
				// 이하 동문
			}
			break;
			}
			// new switch
			switch (static_cast<MapObjectType>(map->tiles[i].monsterAndObject))
			{
			case MapObjectType::QueenPicture:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 0,4,31,32 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::Flag1:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 85,5,13,29 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::Flag2:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 108,6,13,29 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::Flag3:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 108,6,13,29 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::HeadObject:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 39,14,13,14 });
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::Stair:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 58,10,18,18 });
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::TreasureRoomFlag:
			{

				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 125,0,31,38 });
				spr->SetScale(0.5f, 0.75f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 3;
				objects.push_back(spr);
			}
			break;
			case MapObjectType::TreasureObject:
			{

				// 보물상자 클래스 생성 구역 
			}
			break;
			}
		}
		tileRoom.push_back({ map, objects, interaction,monsters });
		sf::RectangleShape shape;
		shape.setSize({ map->vertexArray.getBounds().width - map->GetTileSize().x * 1.75f, map->vertexArray.getBounds().height - map->GetTileSize().y * 1.75f });
		shape.setPosition({ map->vertexArray.getBounds().left + map->GetTileSize().x  ,map->vertexArray.getBounds().top + map->GetTileSize().y });
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color::Green);
		roomShape.push_back(shape);
		count++;
	}


	connected.resize(tileRoom.size(), false);
	connected[0] = true;
	int currentRoom = 0;
	int lineCount = 0;
	int prevRooom = 0;
	while (true)
	{
		int closestRoom = -1;
		float minDistance = std::numeric_limits<float>::max();
		for (size_t i = 1; i < tileRoom.size(); ++i)
		{
			if (!connected[i])
			{
				float dist = Utils::Distance(tileRoom[currentRoom].map->GetStartPos(), tileRoom[i].map->GetStartPos());
				if (dist < minDistance)
				{
					minDistance = dist;
					closestRoom = i;
				}
			}
		}
		if (closestRoom == -1)
		{
			lastRoom = currentRoom;
			break;
		}
		ConnectRooms(tileRoom[currentRoom].map, tileRoom[closestRoom].map);
		connected[closestRoom] = true;
		prevRooom = currentRoom;
		currentRoom = closestRoom;
	}

	for (int i = 0; i < tileRoom.size(); ++i)
	{
		std::vector<DoorInfo> door;
		for (int k = 0; k < passages.size(); ++k)
		{
			door.clear();
			isIntersecting(tileRoom[i].map->vertexArray.getBounds(), passages[k].from, passages[k].to, door);
			for (int i = 0; i < door.size(); ++i)
			{
				bool isNotPos = false;
				for (auto& pushPos : doorInfo)
				{
					if (pushPos.pos.x == door[i].pos.x && pushPos.pos.y == door[i].pos.y)
					{
						isNotPos = true;
						break;
					}
				}
				if (!isNotPos)
				{
					doorInfo.push_back(door[i]);
				}

			}
		}
	}



	for (int i = 0; i < doorInfo.size(); ++i)
	{
		Door* temp = (Door*)AddGo(new Door(static_cast<int>(doorInfo[i].dir), "graphics/DoorSprite.png"));
		temp->SetPosition(doorInfo[i].pos);
		temp->SetOrigin(Origins::MC);
		temp->SetScale(2.0f, 2.0f);
		temp->sortLayer = 3;
		doors.push_back(temp);

		sf::RectangleShape shape;
		shape.setSize({ 25.f,25.f });
		shape.setPosition(doorInfo[i].pos);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1);
		Utils::SetOrigin(shape, Origins::MC);
		doorShape2.push_back(shape);
	}

	for (int i = 0; i < passages.size(); ++i)
	{
		CreateTunnel(passages[i].from, passages[i].to);
	}


	player = (Player*)AddGo(new Player((Player::Types)1));
	player->sortLayer = 10;


	for (auto go : gameObjects)
	{
		go->Init();
	}

	for (int i = 0; i < tileRoom.size(); ++i)
	{
		for (int ii = 0; ii < tileRoom[i].spr.size(); ++ii)
		{
			for (int k = 0; k < doorShape2.size(); ++k)
			{
				if (tileRoom[i].spr[ii]->sprite.getGlobalBounds().intersects(doorShape2[k].getGlobalBounds()))
				{
					RemoveGo(tileRoom[i].spr[ii]);
				}
			}
		}
	}
	Exit();

	std::cout << "TestRoom의 끝방 :" << lastRoom << "\t" << "Room의 끝방 :" << rooms->GetLastRoom() << " 중간 지점 :" << rooms->GetMidRoom() << std::endl;
}

void TestRom::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	if (rooms != nullptr)
	{
		delete rooms;
		rooms = nullptr;
	}
}

void TestRom::Enter()
{
	Scene::Enter();
	shape.setPosition(tileRoom[0].map->GetStartPos());
	worldView.setSize(windowSize);
	worldView.setCenter(shape.getPosition());

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	player->SetPosition(tileRoom[0].map->GetStartPos());
	player->SetOrigin(Origins::MC);
}

void TestRom::Exit()
{
	Scene::Exit();
}

void TestRom::Update(float dt)
{
	Scene::Update(dt);
	accumulatedTime += dt;
	frameCount++;
	if (accumulatedTime >= 1.0f)
	{
		float fps = static_cast<float>(frameCount) / accumulatedTime;
		std::cout << "FPS: " << fps << std::endl;

		// 값 초기화
		frameCount = 0;
		accumulatedTime = 0.0f;
	}

	MoveWorldView();
	CoiledPlayerByMap();
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F6))
	{
		rooms->PrintSize();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Add))
	{
		length++;
		test = true;
	}

	/*for (auto& door : doors)
	{
		if (door->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			door->Open();
			colliedDoor = true;
		}
	}*/


	for (int i = 0; i < doorShape2.size(); ++i)
	{
		if (doorShape2[i].getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			doors[i]->Open();
			colliedDoor = true;
		}
	}

	for (int i = 0; i < tileRoom.size(); ++i)
	{
		for (int ii = 0; ii < tileRoom[i].roomobj.size(); ++ii)
		{
			if (tileRoom[i].roomobj[ii].interactionObj->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
			{
				tileRoom[i].roomobj[ii].interactionObj->PlayAnimation(tileRoom[i].roomobj[ii].type);
			}
		}
	}
	/*for (auto& t : tunnelSprite)
	{
		if (t->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			std::cout << "A" << std::endl;
		}
	}*/

}

void TestRom::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	//rooms->Draw(window);
	window.draw(shape);
	for (int i = 0; i < length; ++i)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = passages[i].from;
		line[1].position = passages[i].to;
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		window.draw(line);
	}


	for (auto& r : roomShape)
	{
		window.draw(r);
	}

	for (const auto& rect : tunnel)
	{
		window.draw(rect);
	}
	for (const auto& rect : doorShape)
	{
		window.draw(rect);
	}
	for (const auto& rect : doorShape2)
	{
		window.draw(rect);
	}
	for (const auto& cir : circle)
	{
		window.draw(cir);
	}
}

void TestRom::MoveWorldView()
{
	/*if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(1.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(-1.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, -1.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, 1.f);
	}*/


	prevPlayerPos = player->GetPosition();

	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		player->sprite.move(5.5f, 0.f);
		player->SetPosition(player->GetPosition() + sf::Vector2f{ 5.5f, 0.f });
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		player->sprite.move(-5.5f, 0.0f);
		player->SetPosition(player->GetPosition() + sf::Vector2f{ -5.5f, 0.f });
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		player->sprite.move(0.0f, -5.5f);
		player->SetPosition(player->GetPosition() + sf::Vector2f{ 0.0f, -5.5f });
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		player->sprite.move(0.0f, 5.5f);
		player->SetPosition(player->GetPosition() + sf::Vector2f{ 0.0f, 5.5f });
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(1.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(0.5f);
	}

	worldView.setCenter(player->GetPosition());

}

void TestRom::ListFilesInDirectory(const std::string& folderPath, std::vector<std::string>& fileList)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((folderPath + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cerr << "Error finding files in directory." << std::endl;
		return;
	}

	int fileCount = 0;

	do {
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			//std::cout << "파일 이름: " << findFileData.cFileName << std::endl;
			std::string filePath = folderPath + findFileData.cFileName;
			fileList.push_back(filePath);
			++fileCount;
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);
}

sf::Vector2f TestRom::Center(TileMap* room)
{
	return { room->vertexArray.getBounds().width / 2 , room->vertexArray.getBounds().height / 2 };
}

void TestRom::ConnectRooms(TileMap* r1, TileMap* r2)
{
	sf::Vector2f c1 = r1->GetStartPos();
	sf::Vector2f c2 = r2->GetStartPos();

	std::vector<DoorInfo> points;

	if (c1.x == c2.x || c1.y == c2.y) // 일자 모양의 통로
	{
		points.clear();
		isIntersecting(r1->vertexArray.getBounds(), c1, c2, points);
		if (points.size() == 1)
		{
			c1 = points[0].pos;
			//doorInfo.push_back(c1);
		}
		points.clear();
		isIntersecting(r2->vertexArray.getBounds(), c1, c2, points);
		if (points.size() == 1)
		{
			c2 = points[0].pos;
			//doorInfo.push_back(c2);

		}
		passages.push_back({ c1, c2 });
	}
	else
	{
		points.clear();
		isIntersecting(r1->vertexArray.getBounds(), c1, { c2.x, c1.y }, points);
		if (points.size() == 1)
		{
			c1 = points[0].pos;
			//doorInfo.push_back(c1);

		}
		points.clear();
		isIntersecting(r2->vertexArray.getBounds(), { c2.x, c1.y }, c2, points);
		if (points.size() == 1)
		{
			c2 = points[0].pos;
			//doorInfo.push_back(c2);

		}
		passages.push_back({ c1, {c2.x, c1.y} });
		passages.push_back({ {c2.x, c1.y}, c2 });
	}

}

void TestRom::CreateTunnel(sf::Vector2f start, sf::Vector2f end)
{

	//// 터널의 사이즈를 설정합니다.
	const sf::Vector2f tunnelSize(25.f, 25.f);
	const float tunnelSpacing = 3.0f; // 터널 사각형들 간의 간격입니다.
	sf::Vector2f midpoint(start.x, end.y);


	sf::Vector2f direction1 = (midpoint - start) / Utils::Distance(start, midpoint);
	float totalTunnelLength1 = Utils::Distance(start, midpoint);
	int tunnelCount1 = static_cast<int>(totalTunnelLength1 / (tunnelSize.x));
	for (int i = 0; i < tunnelCount1; ++i)
	{
		SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
		spr->SetPosition((start + sf::Vector2f{ direction1.x * i, direction1.y * i }*(tunnelSize.x)));
		spr->sortLayer = -2;
		spr->sprite.setTextureRect({ 13,13,25,25 });
		spr->SetOrigin(Origins::MC);

		SpriteGo* spr2 = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
		spr2->SetPosition(spr->GetPosition().x + tunnelSize.x, spr->GetPosition().y);
		spr2->sortLayer = -3;
		spr2->sprite.setTextureRect({ 13,43,25,25 });
		spr2->sprite.setRotation(90);
		spr2->SetOrigin(Origins::MC);


		SpriteGo* spr3 = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
		spr3->SetPosition(spr->GetPosition().x - tunnelSize.x, spr->GetPosition().y);
		spr3->sortLayer = -3;
		spr3->sprite.setTextureRect({ 13,43,25,25 });
		spr3->sprite.setRotation(90);
		spr3->SetOrigin(Origins::MC);

		for (auto& a : tunnelSprite)
		{
			if (a->sprite.getGlobalBounds().intersects(spr2->sprite.getGlobalBounds()))
			{
				RemoveGo(spr2);
			}
			if (a->sprite.getGlobalBounds().intersects(spr3->sprite.getGlobalBounds()))
			{
				RemoveGo(spr3);
			}
		}
		for (auto& a : tunnelWall)
		{

			if (a->sprite.getGlobalBounds().intersects(spr2->sprite.getGlobalBounds()))
			{
				RemoveGo(spr2);
			}
			if (a->sprite.getGlobalBounds().intersects(spr3->sprite.getGlobalBounds()))
			{
				RemoveGo(spr3);
			}
		}

		sf::RectangleShape tunnelShape;
		tunnelShape.setSize(tunnelSize);
		tunnelShape.setPosition((start + sf::Vector2f{ direction1.x * i, direction1.y * i }*(tunnelSize.x)));
		tunnelShape.setRotation(std::atan2(direction1.y, direction1.x) * 180.0f / 3.14159265f);
		tunnelShape.setFillColor(sf::Color::Transparent);
		tunnelShape.setOutlineThickness(2);
		tunnelShape.setOutlineColor(sf::Color::Red);
		Utils::SetOrigin(tunnelShape, Origins::MC);
		{
			tunnelSprite.push_back(spr);
			tunnelWall.push_back(spr2);
		}
	}
	sf::Vector2f direction2 = (end - midpoint) / Utils::Distance(midpoint, end);
	float totalTunnelLength2 = Utils::Distance(midpoint, end);
	int tunnelCount2 = static_cast<int>(totalTunnelLength2 / (tunnelSize.x));
	for (int i = 0; i < tunnelCount2; ++i)
	{
		SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
		spr->SetPosition(midpoint + sf::Vector2f{ direction2.x * i ,direction2.y * i } *(tunnelSize.x));
		spr->sortLayer = -2;
		spr->sprite.setTextureRect({ 13,13,25,25 });
		spr->SetOrigin(Origins::MC);

		SpriteGo* spr2 = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
		spr2->SetPosition(spr->GetPosition().x, spr->GetPosition().y + tunnelSize.y);
		spr2->sortLayer = -3;
		spr2->sprite.setTextureRect({ 13,43,25,25 });
		spr2->SetOrigin(Origins::MC);


		SpriteGo* spr3 = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
		spr3->SetPosition(spr->GetPosition().x, spr->GetPosition().y - tunnelSize.y);
		spr3->sortLayer = -3;
		spr3->sprite.setTextureRect({ 13,43,25,25 });
		spr3->SetOrigin(Origins::MC);

		for (auto& a : tunnelSprite)
		{
			if (a->sprite.getGlobalBounds().intersects(spr2->sprite.getGlobalBounds()))
			{
				RemoveGo(spr2);
			}
			if (a->sprite.getGlobalBounds().intersects(spr3->sprite.getGlobalBounds()))
			{
				RemoveGo(spr3);
			}
		}

		for (auto& a : tunnelWall)
		{

			if (a->sprite.getGlobalBounds().intersects(spr2->sprite.getGlobalBounds()))
			{
				RemoveGo(spr2);
			}
			if (a->sprite.getGlobalBounds().intersects(spr3->sprite.getGlobalBounds()))
			{
				RemoveGo(spr3);
			}
		}

		for (auto& a : tileRoom)
		{
			if (a.map->vertexArray.getBounds().contains(spr2->GetPosition()))
			{
				RemoveGo(spr2);
			}
			if (a.map->vertexArray.getBounds().contains(spr3->GetPosition()))
			{
				RemoveGo(spr3);
			}
		}
		sf::RectangleShape tunnelShape;
		tunnelShape.setSize(tunnelSize);
		tunnelShape.setPosition(midpoint + sf::Vector2f{ direction2.x * i ,direction2.y * i } *(tunnelSize.x));
		tunnelShape.setRotation(std::atan2(direction2.y, direction2.x) * 180.0f / 3.14159265f);
		tunnelShape.setFillColor(sf::Color::Transparent);
		tunnelShape.setOutlineThickness(2);
		tunnelShape.setOutlineColor(sf::Color::Green);
		Utils::SetOrigin(tunnelShape, Origins::MC);
		{
			tunnelSprite.push_back(spr);
			tunnelWall.push_back(spr2);
			tunnelWall.push_back(spr3);
		}
	}
	if (start.y < end.y)
	{
		for (int i = 0; i < 3; ++i)
		{
			float xpos = end.x - tunnelSize.x;
			SpriteGo* spr3 = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
			spr3->SetPosition(xpos + (tunnelSize.x * i), start.y - tunnelSize.y);
			spr3->sortLayer = -2;
			spr3->sprite.setTextureRect({ 13,43,25,25 });
			spr3->SetOrigin(Origins::MC);

			tunnelWall.push_back(spr3);
		}
	}
	if (start.y > end.y)
	{
		for (int i = 0; i < 3; i++)
		{
			float xpos = end.x - tunnelSize.x;
			SpriteGo* spr3 = (SpriteGo*)AddGo(new SpriteGo("graphics/tunnel.png"));
			spr3->SetPosition(xpos + (tunnelSize.x * i), start.y + tunnelSize.y);
			spr3->sortLayer = -2;
			spr3->sprite.setTextureRect({ 13,43,25,25 });
			spr3->SetOrigin(Origins::MC);

			tunnelWall.push_back(spr3);
		}
	}
	sf::RectangleShape startShape;

	sf::Vector2f shapeSize = { 37.5f,37.5f };
	sf::Vector2f startPos = { start.x, start.y };
	if (start.x > end.x)
	{
		shapeSize.x = end.x - start.x;
		shapeSize.y -= 19.75f;
		startPos.y -= 12.5f;
	}
	else if (start.x < end.x)
	{
		//shapeSize.x = start.x - end.x;
		shapeSize.x = end.x - start.x;
		shapeSize.y -= 19.75f;
		startPos.y -= 12.5f;

	}
	else if (start.y > end.y)
	{
		shapeSize.y = start.y - end.y;
		shapeSize.y = -shapeSize.y;
		shapeSize.x -= 25.f;
		startPos.x -= 7.25f;
	}
	else if (start.y < end.y)
	{
		shapeSize.y = end.y - start.y;
		shapeSize.x -= 25.f;
		startPos.x -= 7.25f;
	}
	startShape.setSize(shapeSize);
	startShape.setPosition(startPos);
	startShape.setFillColor(sf::Color::Transparent);
	startShape.setOutlineThickness(2);
	startShape.setOutlineColor(sf::Color::Yellow);

	tunnel.push_back(startShape);

	Exit();
}






bool TestRom::isIntersecting(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2)
{
	float d1 = (b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x);
	float d2 = (b2.x - b1.x) * (a2.y - b1.y) - (b2.y - b1.y) * (a2.x - b1.x);
	float d3 = (a2.x - a1.x) * (b1.y - a1.y) - (a2.y - a1.y) * (b1.x - a1.x);
	float d4 = (a2.x - a1.x) * (b2.y - a1.y) - (a2.y - a1.y) * (b2.x - a1.x);

	return (d1 * d2 < 0) && (d3 * d4 < 0);
}

sf::Vector2f TestRom::intersectionPoint(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2)
{
	float A1 = a2.y - a1.y;
	float B1 = a1.x - a2.x;
	float C1 = A1 * a1.x + B1 * a1.y;

	float A2 = b2.y - b1.y;
	float B2 = b1.x - b2.x;
	float C2 = A2 * b1.x + B2 * b1.y;

	float det = A1 * B2 - A2 * B1;

	if (det == 0)
		return sf::Vector2f(); // 선분이 평행한 경우

	float x = (B2 * C1 - B1 * C2) / det;
	float y = (A1 * C2 - A2 * C1) / det;

	return sf::Vector2f(x, y);
}

bool TestRom::isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, sf::Vector2f& intersection)
{
	sf::Vector2f b1(rect.left, rect.top);
	sf::Vector2f b2(rect.left + rect.width, rect.top);
	sf::Vector2f b3(rect.left, rect.top + rect.height);
	sf::Vector2f b4(rect.left + rect.width, rect.top + rect.height);

	if (isIntersecting(a1, a2, b1, b2))
	{
		intersection = intersectionPoint(a1, a2, b1, b2);
		return true;
	}
	if (isIntersecting(a1, a2, b1, b3))
	{
		intersection = intersectionPoint(a1, a2, b1, b3);
		return true;
	}
	if (isIntersecting(a1, a2, b2, b4))
	{
		intersection = intersectionPoint(a1, a2, b2, b4);
		return true;
	}
	if (isIntersecting(a1, a2, b3, b4))
	{
		intersection = intersectionPoint(a1, a2, b3, b4);
		return true;
	}

	return false;
}

std::vector<DoorInfo> TestRom::isIntersecting(const sf::FloatRect& rect, const sf::Vector2f& a1, const sf::Vector2f& a2, std::vector<DoorInfo>& room)
{
	sf::Vector2f b1(rect.left, rect.top);
	sf::Vector2f b2(rect.left + rect.width, rect.top);
	sf::Vector2f b3(rect.left, rect.top + rect.height);
	sf::Vector2f b4(rect.left + rect.width, rect.top + rect.height);

	sf::Vector2f center = { (rect.left + rect.width) * 0.5f,(rect.top + rect.height) * 0.5f };
	if (isIntersecting(a1, a2, b1, b2))
	{
		sf::Vector2f pos = intersectionPoint(a1, a2, b1, b2);
		pos.y += tileRoom[0].map->GetTileSize().y * 0.5f;
		room.push_back({ pos , DoorDirection::Up });
	}
	if (isIntersecting(a1, a2, b1, b3))
	{
		sf::Vector2f pos = intersectionPoint(a1, a2, b1, b3);
		pos.x += tileRoom[0].map->GetTileSize().x * 0.5f;
		room.push_back({ pos, DoorDirection::Left });

	}
	if (isIntersecting(a1, a2, b2, b4))
	{
		sf::Vector2f pos = intersectionPoint(a1, a2, b2, b4);
		pos.x -= tileRoom[0].map->GetTileSize().x * 0.5f;
		room.push_back({ pos, DoorDirection::Right });
	}
	if (isIntersecting(a1, a2, b3, b4))
	{
		sf::Vector2f pos = intersectionPoint(a1, a2, b3, b4);
		pos.y -= tileRoom[0].map->GetTileSize().y * 0.5f;
		room.push_back({ pos, DoorDirection::Down });
	}

	return room;
}

void TestRom::CoiledPlayerByMap()
{
	/*if(!colliedDoor)
	for (int i = 0;i < tileRoom.size();++i)
	{

	}*/
	if (tileRoom[currentRoom].map->vertexArray.getBounds().contains(player->GetPosition()) && !colliedDoor)
	{
		if (!roomShape[currentRoom].getGlobalBounds().contains(player->GetPosition()) )
			player->SetPosition(prevPlayerPos);
	}

	for (int i = 0; i < tileRoom.size(); ++i)
	{
		if (tileRoom[i].map->vertexArray.getBounds().contains(player->GetPosition()) && colliedDoor)
		{
			currentRoom = i;
			colliedDoor = false;
			break;
		}
	}
	for (int i = 0; i < tunnel.size(); ++i)
	{
		if (tunnel[i].getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			currentTunnel = i;
			break;
		}
	}
	bool test = false;
	bool test1 = false;
	if (!tunnel[currentTunnel].getGlobalBounds().contains(player->GetPosition()) && colliedDoor)
	{
		for (int i = 0; i < tunnel.size(); ++i)
		{
			if (tunnel[i].getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
			{
				test1 = true;
				currentTunnel = i;
			}
		}
		if (!test1) player->SetPosition(prevPlayerPos);
	}
	/*if (test)
	{
		for (int i = 0;i < tunnel.size();++i)
		{
			if (tunnel[i].getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
			{
				test1 = true;
				currentTunnel = i;
				break;
			}
		}
	}*/
	//if (test1)
	//{
	//	player->SetPosition(tunnel[currentTunnel].getPosition());
	//}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F11))
	{
		std::cout << "현재방 : " << currentRoom << "터널 :" << currentTunnel << std::endl;
	}
	/*for (auto& tu : tunnel)
	{
		if (colliedDoor)
		{
			if (!tu.getGlobalBounds().contains(player->GetPosition()))
			{
				std::cout << "OutTunnel" << std::endl;
			}
		}
	}*/
}
