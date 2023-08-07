#include "stdafx.h"
#include "SceneMaptool.h"
#include "SpriteGo.h"
SceneMaptool::SceneMaptool() : Scene(SceneId::MapTool)
{
	resourceListPath = "script/SceneMapToolResourceList.csv";
}

void SceneMaptool::Init()
{
	Release();


	LoadFromMapObjectTypeFile("MapFile/MapPattern1.csv");
	LoadFromMapFile("MapFile/MapGraphicsInfo.csv");
	SettingRoom();

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneMaptool::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneMaptool::Enter()
{

	Scene::Enter();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	std::cout << "Enter The Map" << std::endl;
}

void SceneMaptool::Exit()
{
	Scene::Exit();
}

void SceneMaptool::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetMouseButton(sf::Mouse::Middle))
	{
		
		sf::Vector2f worldPose = ScreenToWorldPos(INPUT_MGR.GetMousePos());
		float moveSpeed = 0.01f;
		worldView.move(-worldPose.x * moveSpeed,-worldPose.y * moveSpeed);
	}
}

void SceneMaptool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
//  GetColumnCount
// GetRowCount
void SceneMaptool::LoadFromMapObjectTypeFile(std::string path)
{
	rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));
	//int maxSize = doc.GetColumnCount() * doc.GetRowCount();
	for (int i = 0;i < doc.GetRowCount();++i)
	{
		for (int k = 0; k < doc.GetColumnCount();++k)
		{
			auto type = doc.GetCell<int>(k, i); 
			mapObjectTypes.push_back(static_cast<MapObjectType>(type));
		}
	}
	maxRowCount = doc.GetColumnCount();
}

void SceneMaptool::LoadFromMapFile(std::string path)
{
	
	rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));
	// Header
	mapSpriteId = doc.GetCell<std::string>(0, 1);
	//Loof
	for (int i = 4;i < doc.GetRowCount();++i)
	{
		auto rows = doc.GetRow<int>(i);
		TextureInfo info;
		info.textureRect = { rows[0], rows[1], rows[2], rows[3] };
		info.sortLayer = rows[4];
		info.sortOrder = rows[5];
		textureInfo.push_back(info);
	}
	
}
/*
		std::vector<int> mapSortLayer;
	std::vector<int> mapSortOrder;
*/
void SceneMaptool::SettingRoom()
{
	int width = 0;
	int height = 0;
	float sizetest = 3.f;
	for (int i = 0;i < mapObjectTypes.size();++i)
	{
		SpriteGo* map = (SpriteGo*)AddGo(new SpriteGo(mapSpriteId));
		map->SetOrigin(Origins::MC);
		switch (mapObjectTypes[i])
		{
		case MapObjectType::Wall:
			map->sprite.setTextureRect(textureInfo[(int)MapObjectType::Wall].textureRect);
			map->sortLayer= textureInfo[(int)MapObjectType::Wall].sortLayer;
			map->sortOrder = textureInfo[(int)MapObjectType::Wall].sortOrder;
			break;
		case MapObjectType::Tile:
			map->sprite.setTextureRect(textureInfo[(int)MapObjectType::Tile].textureRect);
			map->sortLayer = textureInfo[(int)MapObjectType::Tile].sortLayer;
			map->sortOrder = textureInfo[(int)MapObjectType::Tile].sortOrder;
			break;
		case MapObjectType::wallObjectUp:
			map->sprite.setTextureRect(textureInfo[(int)MapObjectType::wallObjectUp].textureRect);
			map->sortLayer = textureInfo[(int)MapObjectType::wallObjectUp].sortLayer;
			map->sortOrder = textureInfo[(int)MapObjectType::wallObjectUp].sortOrder;
			break;
		case MapObjectType::WallObjectDown:
			map->sprite.setTextureRect(textureInfo[(int)MapObjectType::WallObjectDown].textureRect);
			map->sortLayer = textureInfo[(int)MapObjectType::WallObjectDown].sortLayer;
			map->sortOrder = textureInfo[(int)MapObjectType::WallObjectDown].sortOrder;
			break;
		}
		sf::IntRect intrect = textureInfo[0].textureRect;
		if (i!=0 && i % maxRowCount == 0)
		{
			width = 0;
			height++;
		}
		map->SetScale(sizetest, sizetest);
		map->SetPosition(0.f+(intrect.width* width++ * sizetest) ,0.f+(intrect.height * height * sizetest));
		
		mapInfo.push_back(map);
	}
}
