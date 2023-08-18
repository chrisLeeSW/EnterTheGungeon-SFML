#include "stdafx.h"
#include "TestRom.h"
#include "Room.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "InteractionObject.h"

TestRom::TestRom() :Scene(SceneId::TestRoom)
{
	resourceListPath = "script/GameMapTestScene.csv";
}

void TestRom::Init()
{
	

	rooms = new Room();
	shape.setSize({ 50.f, 50.f });
	ListFilesInDirectory("Room/TileMapFile/");
	int count = 0;
	int rnadFileNumber = 0;
	while (count != rooms->GetRoom().size())
	{
		bool collied = false;
		rnadFileNumber = Utils::RandomRange(0, fileList.size() );
		TileMap* map = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		 sf::Vector2f pos = { rooms->Center(rooms->GetRoomIndex(count)) };
		// sf::Vector2f pos = { rooms->GetRoomIndex(count).x , rooms->GetRoomIndex(count).y};
		map->SetStartPos(pos);

		sf::Vector2f tileMapSize = map->TileMapSize(fileList[rnadFileNumber]);
		sf::Vector2f objpos = pos;
		objpos -= tileMapSize * 0.5f;
		objpos += map->GetTileSize() * 0.5f;



		if (rooms->GetRoomIndex(count).width < tileMapSize.x ||
			rooms->GetRoomIndex(count).height < tileMapSize.y)
		{
			continue;
		}
		map->Load(fileList[rnadFileNumber]);
		map->SetOrigin(Origins::MC);
		std::vector<SpriteGo*> objects;
		std::vector<RoomObjectsInfoTest1> interaction;
		for (int i = 0; i < map->tiles.size(); ++i)
		{
			//	objects
			switch (static_cast<MapObjectType>(map->tiles[i].objectTypes))
			{
			case MapObjectType::WallDown:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,250,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr); // wall클래스 생성
			}
			break;
			case MapObjectType::LibraryDown:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,650,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr); // wall클래스 생성
			}
			break;
			case MapObjectType::Pot:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 0,800,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::Book1:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(map->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 0,850,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + map->tiles[i].x * map->GetTileSize().x, objpos.y + map->tiles[i].y * map->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(map->tiles[i].objectTypes), spr });
			}
			break;

			}
		}
		tileRoom.push_back({ map, objects, interaction });
		count++;
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}
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
	shape.setPosition({ (tileRoom[0].map->vertexArray.getBounds().left + tileRoom[0].map->vertexArray.getBounds().width) / 2 ,
	(tileRoom[0].map->vertexArray.getBounds().top + tileRoom[0].map->vertexArray.getBounds().height) / 2 });
	worldView.setSize(windowSize);
	worldView.setCenter(shape.getPosition());

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


}

void TestRom::Exit()
{
	Scene::Exit();
}

void TestRom::Update(float dt)
{
	Scene::Update(dt);
	MoveWorldView();
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		shape.move(5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		shape.move(-5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		shape.move(0.0f, -5.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		shape.move(0.0f, 5.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Add))
	{
		rooms->length++;
		if (rooms->length > rooms->LineSize())
			rooms->length = rooms->LineSize();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Dash))
	{
		rooms->length--;
		if (rooms->length <0)
			rooms->length = 0;
	}
}

void TestRom::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	rooms->Draw(window);
	window.draw(shape);
}

void TestRom::MoveWorldView()
{
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(-5.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, -5.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, 5.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(1.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(0.5f);
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Home))
	{
		rooms->PrintSize();
	}
}

void TestRom::ListFilesInDirectory(const std::string& folderPath)
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
			// 디렉토리 스킵
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
