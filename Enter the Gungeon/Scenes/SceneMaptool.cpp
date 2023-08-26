#include "stdafx.h"
#include "SceneMaptool.h"
#include "SpriteGo.h"
#include "TileMap.h"
#include "UiButton.h"
#include "TextGo.h"
#include "TextBox.h"

#include <windows.h>
#include <tchar.h>
SceneMaptool::SceneMaptool() : Scene(SceneId::MapTool), view(1.0f), wallWidthCount(5), wallHeightCount(3), doubleBySclaeX(2.f), doubleBySclaeY(2.f), minWallWidthCount(5),
minWallHeightCount(3), currentCplliedShapeType(-1)
{
	resourceListPath = "script/SceneMapToolResourceList.csv";
}

void SceneMaptool::Init()
{
	Release();


	SettingUiSprite();
	SettingUiText();
	SettingTileSprite("Room/TileSpriteInfo.csv");




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

	wallWidthCount = 5;
	wallHeightCount = 3;

	worldView.setSize(windowSize*0.5f);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);



	view = 1.0f;
}

void SceneMaptool::Exit()
{
	Scene::Exit();
}



void SceneMaptool::Update(float dt)
{
	Scene::Update(dt);

	std::stringstream wallWidthSize;
	wallWidthSize << "Width : " << wallWidthCount;
	wallWidthCountText->text.setString(wallWidthSize.str());
	wallWidthCountText->SetOrigin(Origins::BC);

	std::stringstream wallHeightSize;
	wallHeightSize << "Height : " << wallHeightCount;
	wallHeightCountText->text.setString(wallHeightSize.str());
	wallHeightCountText->SetOrigin(Origins::BC);


	MakeLine();
	if (IncreaseOrDecrease)
	{

		TileMap* temp1 = gridTile;
		TileMap* temp2 = objectSprite;
		TileMap* temp3 = thirdSprite;

		gridTile = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		/*gridTile->tiles.resize(temp1->tiles.size());
		for (int i = 0;i < temp1->tiles.size();++i)
		{
			gridTile->tiles[i] = temp1->tiles[i];
		}*/
		gridTile->NoneFileLoad(wallWidthCount, wallHeightCount,false);
		
	
		objectSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		
		//objectSprite->tiles.resize(temp2->tiles.size());
		/*for (int i = 0;i < temp1->tiles.size();++i)
		{
			objectSprite->tiles[i] = temp2->tiles[i];
		}*/
		objectSprite->NoneFileLoad(wallWidthCount, wallHeightCount, false);
		

		thirdSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		thirdSprite->NoneFileLoad(wallWidthCount, wallHeightCount, false);

		RemoveGo(temp1);
		temp1 = nullptr;

		RemoveGo(temp2);
		temp2 = nullptr;


		RemoveGo(temp3);
		temp3 = nullptr;
		IncreaseOrDecrease = false;
	}


	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(-1.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(1.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, 1.5f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, -1.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(1.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(0.5f);
	}


	for (auto& tile : tiles)
	{
		
		if (tile.spr->GetActive()&&tile.spr->sprite.getGlobalBounds().contains(INPUT_MGR.GetMousePos()) && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			currentTileSprite->sprite.setTextureRect(tile.spr->sprite.getTextureRect());
		}
	}
	//
	if (INPUT_MGR.GetKey(sf::Keyboard::Delete))
	{
		deleteWall = true;
	}
	for (auto it = colliedShape.begin(); it != colliedShape.end();) {
		if (INPUT_MGR.GetKey(sf::Keyboard::Delete) && it->shape.getGlobalBounds().contains(ScreenToWorldPos(INPUT_MGR.GetMousePos()))) {
			it = colliedShape.erase(it);
		}
		else {
			++it;
		}
	}
	// 함수만들기


	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
	{
		if (!drawGridAllowed) return;
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 25;
		int count = -1;
		for (int i = 0; i < tiles.size(); ++i)
		{
			if (currentTileSprite->sprite.getTextureRect() == tiles[i].spr->sprite.getTextureRect())
			{
				count = i;
				break;
			}
		}
		if (count < 0) return;
		if (count == (int)MapObjectType::NormalWallTop || count == (int)MapObjectType::NorMalWallRight || count == (int)MapObjectType::NormalWallLeft||count == (int)MapObjectType::LightWallTop || 	count==(int)MapObjectType::LibraryTop ||
			count == (int)MapObjectType::LightWallLeft || count == (int)MapObjectType::LightWallRight || count == (int)MapObjectType::LibraryLeft || count == (int)MapObjectType::LibraryRight ||
			count == (int)MapObjectType::LibraryDown|| count == (int)MapObjectType::StoreTop || count == (int)MapObjectType::StoreRight || count == (int)MapObjectType::StoreLeft ||
			count == (int)MapObjectType:: Grass|| count == count == (int)MapObjectType::StoreTable1 || count == (int)MapObjectType::StoreTable2 || count == (int)MapObjectType::StoreTable3 ||
			count == (int)MapObjectType::StoreTable4 || count == (int)MapObjectType::StoreTable5 || count == (int)MapObjectType::StoreTable6 || count == (int)MapObjectType::StoreTableDisplay1 ||
			count == (int)MapObjectType::StoreTableDisplay2 || count == (int)MapObjectType::Armor|| count == (int)MapObjectType::Chiar||
			count == (int)MapObjectType::Pot|| count == (int)MapObjectType::MonsterKin|| count == (int)MapObjectType::TreasureAlter ||
			count == (int)MapObjectType::MonsterKinKey|| count == (int)MapObjectType::MonsterBlue|| count == (int)MapObjectType::MonsterRed || count == (int)MapObjectType::Boss || 
			count == (int)MapObjectType::StoreOner)
		{
			objectSprite->ChangeTile(gridIndex.x, gridIndex.y, count, currentTileSprite->sprite.getTextureRect());
			//thirdSprite
		}
		else if(count == (int)MapObjectType::QueenPicture ||
			count == (int)MapObjectType::HeadObject || count == (int)MapObjectType::Stair || count == (int)MapObjectType::Flag1 || count == (int)MapObjectType::Flag2 || count == (int)MapObjectType::TreasureRoomFlag ||
			count == (int)MapObjectType::Flag3 || count == (int)MapObjectType::TreasureObject)
		{
			thirdSprite->ChangeTile(gridIndex.x, gridIndex.y, count, currentTileSprite->sprite.getTextureRect());
		}
		else
		{
			gridTile->ChangeTile(gridIndex.x, gridIndex.y, count, currentTileSprite->sprite.getTextureRect());
		}
	}

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Right) && INPUT_MGR.GetKey(sf::Keyboard::LControl))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 25;
		if (gridIndex.x < 0 || gridIndex.y < 0) return;
		gridTile->ChangeTile(gridIndex.x, gridIndex.y, static_cast<int>(MapObjectType::None), sf::IntRect{ 50,0,50,50 });
	}
	if (INPUT_MGR.GetMouseButton(sf::Mouse::Right) && INPUT_MGR.GetKey(sf::Keyboard::LShift))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 25;
		if (gridIndex.x < 0 || gridIndex.y < 0) return;
		objectSprite->ChangeTile(gridIndex.x, gridIndex.y, static_cast<int>(MapObjectType::None), sf::IntRect{ 50,0,50,50 });
	}
	if (INPUT_MGR.GetMouseButton(sf::Mouse::Right) && INPUT_MGR.GetKey(sf::Keyboard::LAlt))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 25;
		if (gridIndex.x < 0 || gridIndex.y < 0) return;
		thirdSprite->ChangeTile(gridIndex.x, gridIndex.y, static_cast<int>(MapObjectType::None), sf::IntRect{ 50,0,50,50 });
	}
	WallMakeCollied();

	
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0))
	{
		setWall = !setWall;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneId::GameMapTestScene);
	}
}

void SceneMaptool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	if (drawGridAllowed)
	{
		for (auto& arry : linesMap)
		{
			window.draw(arry);
		}
	}
	for (auto& arry : colliedShape)
	{
		window.draw(arry.shape);
	}
}

void SceneMaptool::SettingUiSprite()
{
	saveUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "SaveUi"));
	saveUi->sprite.setTextureRect({ 10,27,50,20 });
	saveUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	saveUi->SetPosition(windowSize.x * 0.05f, windowSize.y * 0.35f);
	saveUi->SetOrigin(Origins::MC);
	saveUi->OnEnter = [this]()
	{
		saveUi->sprite.setTextureRect({ 11,55,50,20 });
		saveUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	saveUi->OnExit = [this]()
	{
		saveUi->sprite.setTextureRect({ 10,27,50,20 });
		saveUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	saveUi->OnClick = [this]()
	{
		std::string route = "Room/TileMapFile/";
		std::string  file = fileNameTexBox->text.getString();
		std::string csv = ".csv";

		std::string path = route + file + csv;
		SaveRoom(path, route, file + csv);
		WallResetCollied();
	};
	saveUi->sortLayer = 100;



	loadUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "LoadUi"));
	loadUi->sprite.setTextureRect({ 10,27,50,20 });
	loadUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	loadUi->SetPosition(windowSize.x * 0.11f, windowSize.y * 0.35f);
	loadUi->SetOrigin(Origins::MC);
	loadUi->OnEnter = [this]()
	{
		loadUi->sprite.setTextureRect({ 11,55,50,20 });
		loadUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	loadUi->OnExit = [this]()
	{
		loadUi->sprite.setTextureRect({ 10,27,50,20 });
		loadUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	loadUi->OnClick = [this]()
	{
		std::string route = "Room/TileMapFile/";
		std::string  file = fileNameTexBox->text.getString();
		std::string csv = ".csv";
		std::string path = route + file + csv;

		LoadGridAndObjectSpriteFile(path, route, file + csv);

	};
	loadUi->sortLayer = 100;


	wallWidthSprite = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "MapXSizeSprite"));
	wallWidthSprite->sprite.setTextureRect({ 12,84,71,30 });
	wallWidthSprite->SetOrigin(Origins::MC);
	wallWidthSprite->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallWidthSprite->SetPosition(windowSize.x * 0.06f, windowSize.y * 0.1f);
	wallWidthSprite->sortLayer = 100;

	wallHeightSprite = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "MapYSizeSprite"));
	wallHeightSprite->sprite.setTextureRect({ 12,84,71,30 });
	wallHeightSprite->SetOrigin(Origins::MC);
	wallHeightSprite->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallHeightSprite->SetPosition(wallWidthSprite->GetPosition().x, wallWidthSprite->GetPosition().y + wallHeightSprite->sprite.getGlobalBounds().height * 1.3f);
	wallHeightSprite->sortLayer = 100;

	wallWidthCountIncrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallWidthSizeIncrease"));
	wallWidthCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
	wallWidthCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallWidthCountIncrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.09f);
	wallWidthCountIncrease->SetOrigin(Origins::MC);

	wallWidthCountIncrease->OnEnter = [this]()
	{
		wallWidthCountIncrease->sprite.setTextureRect({ 11,55,50,20 });
	};
	wallWidthCountIncrease->OnExit = [this]()
	{
		wallWidthCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
		wallWidthCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallWidthCountIncrease->OnClick = [this]()
	{
		wallWidthCount++;
		if (makeGridCheck)
		{
			IncreaseOrDecrease = true;
			increaseWidth = true;
		}
	};
	wallWidthCountIncrease->sortLayer = 100;


	wallHeightCountIncrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallHeightSizeIncrease"));
	wallHeightCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
	wallHeightCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallHeightCountIncrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.16f);
	wallHeightCountIncrease->SetOrigin(Origins::MC);
	wallHeightCountIncrease->OnEnter = [this]()
	{
		wallHeightCountIncrease->sprite.setTextureRect({ 11,55,50,20 });
	};
	wallHeightCountIncrease->OnExit = [this]()
	{
		wallHeightCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
		wallHeightCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallHeightCountIncrease->OnClick = [this]()
	{
		wallHeightCount++;
		if (makeGridCheck) 
		{ 
			IncreaseOrDecrease = true; 
			increaseHeight = true;
		}

	};
	wallHeightCountIncrease->sortLayer = 100;


	wallWidthCountDecrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallWidthSizeDecrease"));
	wallWidthCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
	wallWidthCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallWidthCountDecrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.12f);
	wallWidthCountDecrease->SetOrigin(Origins::MC);

	wallWidthCountDecrease->OnEnter = [this]()
	{
		wallWidthCountDecrease->sprite.setTextureRect({ 11,55,50,20 });
		wallWidthCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallWidthCountDecrease->OnExit = [this]()
	{
		wallWidthCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
		wallWidthCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallWidthCountDecrease->OnClick = [this]()
	{
		if (makeGridCheck)
		{
			IncreaseOrDecrease = true;
			decreaseWidth = true;
		}
		wallWidthCount--;
		if (wallWidthCount < minWallWidthCount)	wallWidthCount = minWallWidthCount;
	};
	wallWidthCountDecrease->sortLayer = 100;

	wallHeightCountDecrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallHeightSizeDecrease"));
	wallHeightCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
	wallHeightCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallHeightCountDecrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.19f);
	wallHeightCountDecrease->SetOrigin(Origins::MC);

	wallHeightCountDecrease->OnEnter = [this]()
	{
		wallHeightCountDecrease->sprite.setTextureRect({ 11,55,50,20 });
		wallHeightCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallHeightCountDecrease->OnExit = [this]()
	{
		wallHeightCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
		wallHeightCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallHeightCountDecrease->OnClick = [this]()
	{
		if (makeGridCheck)
		{
			IncreaseOrDecrease = true;
			decreaseHeight = true;
		}
		wallHeightCount--;
		if (wallHeightCount < minWallHeightCount)	wallHeightCount = minWallHeightCount;
	};
	wallHeightCountDecrease->sortLayer = 100;

	makeUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "MakeUi"));
	makeUi->sprite.setTextureRect({ 10,27,50,20 });
	makeUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeUi->SetPosition(windowSize.x * 0.05f, windowSize.y * 0.25f);
	makeUi->SetOrigin(Origins::MC);
	makeUi->OnEnter = [this]()
	{
		makeUi->sprite.setTextureRect({ 11,55,50,20 });
		makeUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeUi->OnExit = [this]()
	{
		makeUi->sprite.setTextureRect({ 10,27,50,20 });
		makeUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeUi->OnClick = [this]()
	{
		if (!drawGridAllowed)
		{
			drawGridAllowed = true;
			MakeGrid();
		}
	};
	makeUi->sortLayer = 100;

	restUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "RestUi"));
	restUi->sprite.setTextureRect({ 10,27,50,20 });
	restUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	restUi->SetPosition(windowSize.x * 0.1f, windowSize.y * 0.25f);
	restUi->SetOrigin(Origins::MC);
	restUi->OnEnter = [this]()
	{
		restUi->sprite.setTextureRect({ 11,55,50,20 });
		restUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	restUi->OnExit = [this]()
	{
		restUi->sprite.setTextureRect({ 10,27,50,20 });
		restUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	restUi->OnClick = [this]()
	{
		drawGridAllowed = false;
		ResetGrid();
		RestLine();
		WallResetCollied();
		setWall = false;
		currentCplliedShapeType = -1;
		AllWallTyepeTextReset();
	};
	restUi->sortLayer = 100;



	currentTileSpriteBackGround = (SpriteGo*)AddGo(new SpriteGo("graphics/MapMakerMenu.png", "CurrentTileBackGround"));
	currentTileSpriteBackGround->sprite.setTextureRect({ 12,120,100,100 });
	currentTileSpriteBackGround->SetPosition(windowSize.x * 0.225f, windowSize.y * 0.125f);
	currentTileSpriteBackGround->SetScale(doubleBySclaeX, doubleBySclaeY);
	currentTileSpriteBackGround->SetOrigin(Origins::MC);
	currentTileSpriteBackGround->sortLayer = 100;


	wallButton = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallButton"));
	wallButton->sprite.setTextureRect({ 10,27,50,20 });
	wallButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallButton->SetPosition(windowSize.x * 0.2f, windowSize.y * 0.25f);
	wallButton->SetOrigin(Origins::MC);
	wallButton->OnEnter = [this]()
	{
		wallButton->sprite.setTextureRect({ 11,55,50,20 });
		wallButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallButton->OnExit = [this]()
	{
		wallButton->sprite.setTextureRect({ 10,27,50,20 });
		wallButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallButton->OnClick = [this]()
	{
		if(!setWall)
			currentCplliedShapeType = 0;
		setWall = true;
	};
	wallButton->sortLayer = 100;

	wallBlockerButton = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallButton"));
	wallBlockerButton->sprite.setTextureRect({ 10,27,50,20 });
	wallBlockerButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	wallBlockerButton->SetPosition(windowSize.x * 0.25f, windowSize.y * 0.25f);
	wallBlockerButton->SetOrigin(Origins::MC);
	wallBlockerButton->OnEnter = [this]()
	{
		wallBlockerButton->sprite.setTextureRect({ 11,55,50,20 });
		wallBlockerButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallBlockerButton->OnExit = [this]()
	{
		wallBlockerButton->sprite.setTextureRect({ 10,27,50,20 });
		wallBlockerButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	wallBlockerButton->OnClick = [this]()
	{
		if (!setWall)
			currentCplliedShapeType = 1;
		setWall = true;
	};
	wallBlockerButton->sortLayer = 100;

	fallingZoneButton = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "fallingZoneButton"));
	fallingZoneButton->sprite.setTextureRect({ 10,27,50,20 });
	fallingZoneButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	fallingZoneButton->SetPosition(windowSize.x * 0.2f, windowSize.y * 0.275f);
	fallingZoneButton->SetOrigin(Origins::MC);
	fallingZoneButton->OnEnter = [this]()
	{
		fallingZoneButton->sprite.setTextureRect({ 11,55,50,20 });
		fallingZoneButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	fallingZoneButton->OnExit = [this]()
	{
		fallingZoneButton->sprite.setTextureRect({ 10,27,50,20 });
		fallingZoneButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	fallingZoneButton->OnClick = [this]()
	{
		if (!setWall)
			currentCplliedShapeType = 2;
		setWall = true;
	};
	fallingZoneButton->sortLayer = 100;

	teleportZoneButton = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "teleportZoneButton"));
	teleportZoneButton->sprite.setTextureRect({ 10,27,50,20 });
	teleportZoneButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	teleportZoneButton->SetPosition(windowSize.x * 0.25f, windowSize.y * 0.275f);
	teleportZoneButton->SetOrigin(Origins::MC);
	teleportZoneButton->OnEnter = [this]()
	{
		teleportZoneButton->sprite.setTextureRect({ 11,55,50,20 });
		teleportZoneButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	teleportZoneButton->OnExit = [this]()
	{
		teleportZoneButton->sprite.setTextureRect({ 10,27,50,20 });
		teleportZoneButton->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	teleportZoneButton->OnClick = [this]()
	{
		if (!setWall)
			currentCplliedShapeType = 3;
		setWall = true;
	};
	teleportZoneButton->sortLayer = 100;
}

void SceneMaptool::SettingUiText()
{
	saveUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "SaveText"));
	saveUiText->text.setCharacterSize(20);
	saveUiText->SetOrigin(Origins::BC);
	saveUiText->text.setString("Save");
	saveUiText->sortLayer = 100;
	saveUiText->SetPosition(saveUi->GetPosition() - sf::Vector2f{ 0.f, saveUiText->text.getCharacterSize() * 0.25f });

	loadUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "SaveText"));
	loadUiText->text.setCharacterSize(20);
	loadUiText->SetOrigin(Origins::BC);
	loadUiText->text.setString("Load");
	loadUiText->sortLayer = 100;
	loadUiText->SetPosition(loadUi->GetPosition() - sf::Vector2f{ 0.f, saveUiText->text.getCharacterSize() * 0.25f });

	wallWidthCountText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeText"));
	wallWidthCountText->text.setCharacterSize(20);
	wallWidthCountText->sortLayer = 100;
	wallWidthCountText->SetPosition(wallWidthSprite->GetPosition());

	wallHeightCountText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeText"));
	wallHeightCountText->text.setCharacterSize(20);
	wallHeightCountText->sortLayer = 100;
	wallHeightCountText->SetPosition(wallHeightSprite->GetPosition());

	wallWidthCountIncreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeIncreaseText"));
	wallWidthCountIncreaseText->text.setCharacterSize(20);
	wallWidthCountIncreaseText->SetOrigin(Origins::BC);
	wallWidthCountIncreaseText->text.setString("+");
	wallWidthCountIncreaseText->sortLayer = 100;
	wallWidthCountIncreaseText->SetPosition(wallWidthCountIncrease->GetPosition() - sf::Vector2f{ 0.f, wallWidthCountIncrease->text.getCharacterSize() * 0.25f });

	wallWidthCountDecreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeDecreaseText"));
	wallWidthCountDecreaseText->text.setCharacterSize(20);
	wallWidthCountDecreaseText->SetOrigin(Origins::BC);
	wallWidthCountDecreaseText->text.setString("-");
	wallWidthCountDecreaseText->sortLayer = 100;
	wallWidthCountDecreaseText->SetPosition(wallWidthCountDecrease->GetPosition() - sf::Vector2f{ 0.f, wallWidthCountDecrease->text.getCharacterSize() * 0.5f });

	wallHeightCountIncreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallHeightSizeIncreaseText"));
	wallHeightCountIncreaseText->text.setCharacterSize(20);
	wallHeightCountIncreaseText->SetOrigin(Origins::BC);
	wallHeightCountIncreaseText->text.setString("+");
	wallHeightCountIncreaseText->sortLayer = 100;
	wallHeightCountIncreaseText->SetPosition(wallHeightCountIncrease->GetPosition() - sf::Vector2f{ 0.f, wallHeightCountIncrease->text.getCharacterSize() * 0.25f });

	wallHeightCountDecreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallHeightSizeDEcreaseText"));
	wallHeightCountDecreaseText->text.setCharacterSize(20);
	wallHeightCountDecreaseText->SetOrigin(Origins::BC);
	wallHeightCountDecreaseText->text.setString("-");
	wallHeightCountDecreaseText->sortLayer = 100;
	wallHeightCountDecreaseText->SetPosition(wallHeightCountDecrease->GetPosition() - sf::Vector2f{ 0.f, wallHeightCountDecrease->text.getCharacterSize() * 0.6f });

	makeUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "makeUiText"));
	makeUiText->text.setCharacterSize(20);
	makeUiText->SetOrigin(Origins::BC);
	makeUiText->text.setString("make");
	makeUiText->sortLayer = 100;
	makeUiText->SetPosition(makeUi->GetPosition() - sf::Vector2f{ 0.f, makeUi->text.getCharacterSize() * 0.125f });


	restUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "RestUiText"));
	restUiText->text.setCharacterSize(20);
	restUiText->SetOrigin(Origins::BC);
	restUiText->text.setString("Reset");
	restUiText->sortLayer = 100;
	restUiText->SetPosition(restUi->GetPosition() - sf::Vector2f{ 0.f, restUi->text.getCharacterSize() * 0.125f });

	fileNameTexBox = (TextBox*)AddGo(new TextBox("fonts/OpenSans-Semibold.ttf", "Map"));
	fileNameTexBox->box.setSize({ 200, 50 });
	fileNameTexBox->text.setCharacterSize(10);
	fileNameTexBox->SetOrigin(Origins::MC);
	fileNameTexBox->SetPosition(windowSize.x * 0.08f, windowSize.y * 0.3f);
	fileNameTexBox->sortLayer = 100;

	wallButtonText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "wallButtonText"));
	wallButtonText->text.setCharacterSize(20);
	wallButtonText->SetOrigin(Origins::BC);
	wallButtonText->text.setString("Wall");
	wallButtonText->SetPosition(wallButton->GetPosition() - sf::Vector2f{ 0.f, wallButton->text.getCharacterSize() * 0.125f });
	wallButtonText->sortLayer = 100;

	wallBlockerButtonText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "wallBlockerButtonText"));
	wallBlockerButtonText->text.setCharacterSize(10);
	wallBlockerButtonText->SetOrigin(Origins::BC);
	wallBlockerButtonText->text.setString("WallBlocker");
	wallBlockerButtonText->SetPosition(wallBlockerButton->GetPosition() - sf::Vector2f{ 0.f, wallBlockerButton->text.getCharacterSize() * 0.125f });
	wallBlockerButtonText->sortLayer = 100;

	fallingZoneButtonText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "wallBlockerButtonText"));
	fallingZoneButtonText->text.setCharacterSize(10);
	fallingZoneButtonText->SetOrigin(Origins::BC);
	fallingZoneButtonText->text.setString("FalingZone");
	fallingZoneButtonText->SetPosition(fallingZoneButton->GetPosition() - sf::Vector2f{ 0.f, fallingZoneButton->text.getCharacterSize() * 0.125f });
	fallingZoneButtonText->sortLayer = 100;

	teleportZoneButtonText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "teleportZoneButtonText"));
	teleportZoneButtonText->text.setCharacterSize(10);
	teleportZoneButtonText->SetOrigin(Origins::BC);
	teleportZoneButtonText->text.setString("TeleportZone");
	teleportZoneButtonText->SetPosition(teleportZoneButton->GetPosition() - sf::Vector2f{ 0.f, teleportZoneButton->text.getCharacterSize() * 0.125f });
	teleportZoneButtonText->sortLayer = 100;

}

void SceneMaptool::SettingTileSprite(const std::string& path)
{
	rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));

	std::string textureId = doc.GetCell<std::string>(1, 0);
	int count = 0;
	sf::Vector2i size = { 0,0 };
	sf::Vector2f curPos = { 60.f,60.f };
	for (int i = 4;i < doc.GetRowCount();++i)
	{
		auto rows = doc.GetRow<int>(i);
		SpriteGo* spriteTexture = (SpriteGo*)AddGo(new SpriteGo(textureId));
		spriteTexture->SetOrigin(Origins::MC);
		spriteTexture->sortLayer = 101;
		spriteTexture->SetPosition(windowSize.x * 0.025f + (size.x++ * curPos.x), windowSize.y * 0.4f + (size.y * curPos.y));
		spriteTexture->sprite.setTextureRect({ rows[0],rows[1] ,rows[2] ,rows[3] });
		if (size.x == 10)
		{
			size.x = 0;
			size.y++;
		}
		tiles.push_back({ spriteTexture,static_cast<MapObjectType>(count++) });
	}
	currentTileSprite = (SpriteGo*)AddGo(new SpriteGo(textureId));
	currentTileSprite->sprite.setTextureRect({ 0,0,50,50 });
	currentTileSprite->SetOrigin(Origins::MC);
	currentTileSprite->SetPosition(currentTileSpriteBackGround->GetPosition());
	currentTileSprite->sortLayer = 101;
	currentTileSprite->SetScale(doubleBySclaeX, doubleBySclaeY);

}

void SceneMaptool::MakeLine()
{

	if (drawGridAllowed)
	{
		linesMap.clear();
		sf::VertexArray grid(sf::Lines);
		sf::Vector2f mapTileSize = { 25.f,25.f };
		sf::Vector2f startPos = { 0.f,0.f };

		for (int i = 0; i < wallHeightCount + 1; ++i)
		{
			grid.append(sf::Vertex(sf::Vector2f(startPos.x, startPos.y + (mapTileSize.y * i)), sf::Color::Red));
			grid.append(sf::Vertex(sf::Vector2f(mapTileSize.x * (wallWidthCount), startPos.y + (mapTileSize.y * i)), sf::Color::Red));
			linesMap.push_back(grid);
		}

		for (int i = 0; i < wallWidthCount + 1; ++i)
		{
			grid.append(sf::Vertex(sf::Vector2f(startPos.x + (mapTileSize.x * i), startPos.y), sf::Color::White));
			grid.append(sf::Vertex(sf::Vector2f(startPos.x + (mapTileSize.x * i), mapTileSize.y * (wallHeightCount)), sf::Color::White));
			linesMap.push_back(grid);
		}
	}
}

void SceneMaptool::RestLine()
{
	if (!linesMap.empty())
		linesMap.clear();
	else
		return;
}

void SceneMaptool::MakeGrid()
{
	makeGridCheck = true;
	gridTile = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	gridTile->NoneFileLoad(wallWidthCount, wallHeightCount, false);

	objectSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	objectSprite->NoneFileLoad(wallWidthCount, wallHeightCount, false);

	thirdSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	thirdSprite->NoneFileLoad(wallWidthCount, wallHeightCount, false);
}


void SceneMaptool::ResetGrid()
{
	if (gridTile != nullptr)
	{
		RemoveGo(gridTile);
		delete gridTile;
		gridTile = nullptr;
	}
	if (objectSprite != nullptr)
	{
		RemoveGo(objectSprite);
		delete objectSprite;
		objectSprite = nullptr;
	}
	if (thirdSprite != nullptr)
	{
		RemoveGo(thirdSprite);
		delete thirdSprite;
		thirdSprite = nullptr;
	}
}

void SceneMaptool::WallMakeCollied()
{
	if (setWall && drawGridAllowed)
	{
		sf::RectangleShape temp1;
		temp1.setOutlineThickness(2);
		WallType type = WallType::None;
		switch (currentCplliedShapeType)
		{
		case 0:
			wallButtonText->text.setFillColor(sf::Color::Red);
			temp1.setOutlineColor(sf::Color::Red);
			type = WallType::Wall;
			break;
		case 1:
			wallBlockerButtonText->text.setFillColor(sf::Color::Green);
			temp1.setOutlineColor(sf::Color::Green);
			type = WallType::WalloBlocker;
			break;
		case 2:
			fallingZoneButtonText->text.setFillColor(sf::Color::Yellow);
			temp1.setOutlineColor(sf::Color::Yellow);
			type = WallType::FallingZone;
			break;
		case 3:
			teleportZoneButtonText->text.setFillColor(sf::Color::Blue);
			temp1.setOutlineColor(sf::Color::Blue);
			type = WallType::TeleportZone;
			break;
		}
		sf::Vector2f isNowPos;
		sf::Vector2f shapeSize;
		if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Middle))
		{
			isPrevPos = ScreenToWorldPos(INPUT_MGR.GetMousePos());
		}
		if (INPUT_MGR.GetMouseButtonUp(sf::Mouse::Middle))
		{
			
			isNowPos = ScreenToWorldPos(INPUT_MGR.GetMousePos());
			shapeSize = isNowPos - isPrevPos;

			temp1.setSize({ shapeSize.x - 2.f, shapeSize.y - 2.f });
			temp1.setFillColor(sf::Color::Transparent);
			temp1.setPosition(isPrevPos);
			colliedShape.push_back({ type,temp1 });
			setWall = false;
			AllWallTyepeTextReset();
		}
	}
	
}

void SceneMaptool::WallResetCollied()
{
	colliedShape.clear();
}

void SceneMaptool::AllWallTyepeTextReset()
{
	wallButtonText->text.setFillColor(sf::Color::White);
	wallBlockerButtonText->text.setFillColor(sf::Color::White);
	fallingZoneButtonText->text.setFillColor(sf::Color::White);
	teleportZoneButtonText->text.setFillColor(sf::Color::White);
}

void SceneMaptool::SaveRoom(std::string& fileName, std::string route, std::string saveFileNameCsv)
{
	ListFilesInDirectory(route);
	bool makeFile = false;

	for (int i = 0;i < fileList.size();++i)
	{
		if (fileList[i] != saveFileNameCsv)
		{
			makeFile = true;
		}
	}
	if (makeFile || fileList.size() <= 0) { std::ofstream ouptFile(fileName); }
	IncreaseOrDecrease = false;
	rapidcsv::Document doc(fileName, rapidcsv::LabelParams(-1, -1));
	doc.Clear();

	doc.SetCell<std::string>(0, 0, "WallSizeWidth");
	doc.SetCell<std::string>(1, 0, "WallSizeHeight");
	doc.SetCell<std::string>(2, 0, "SortLayer");

	doc.SetCell<int>(0, 1, wallWidthCount);
	doc.SetCell<int>(1, 1, wallHeightCount);	
	doc.SetCell<int>(2, 1, -1);

	int count = 0;
	for (int i = 4;i < wallHeightCount+4;++i)
	{
		for (int j = 0;j < wallWidthCount;++j)
		{
			std::string tileInfo = std::to_string(gridTile->tiles[count].texIndex);
			tileInfo += "," + std::to_string(objectSprite->tiles[count].texIndex);
			tileInfo += "," + std::to_string(thirdSprite->tiles[count].texIndex);
			// thirdSprite +한번더 
			doc.SetCell<std::string>(j, i, tileInfo);
			count++;
		}
	}
	int newHeight = wallHeightCount + 4 + 2;
	doc.SetCell<std::string>(0, newHeight-1, "ShapeSize");
	doc.SetCell<int>(1, newHeight-1, colliedShape.size());
	doc.SetCell<std::string>(0,newHeight, "WallType");
	doc.SetCell<std::string>(1,newHeight, "WallPosition.x");
	doc.SetCell<std::string>(2,	newHeight, "WallPosition.y");
	doc.SetCell<std::string>(3,	newHeight, "WallSize.x");
	doc.SetCell<std::string>(4,newHeight, "WallSize.y");
	
	int indexCount = 0;
	for (int i = newHeight+1; i < newHeight + colliedShape.size()+1; ++i)
	{
		doc.SetCell<int>(0,i, static_cast<int>(colliedShape[indexCount].type));
		doc.SetCell<float>(1, i, colliedShape[indexCount].shape.getPosition().x  );
		doc.SetCell<float>(2, i, colliedShape[indexCount].shape.getPosition().y);
		doc.SetCell<float>(3, i, colliedShape[indexCount].shape.getSize().x);
		doc.SetCell<float>(4, i, colliedShape[indexCount].shape.getSize().y);

		indexCount++;
	}

	doc.Save();
	std::cout << "Save File Complete" << std::endl;

	drawGridAllowed = false;
	ResetGrid();
	RestLine();
}

void SceneMaptool::LoadGridAndObjectSpriteFile(std::string& fileName, std::string& route, std::string saveFileNameCsv)
{
	ListFilesInDirectory(route);
	bool makeFile = false;

	for (int i = 0;i < fileList.size();++i)
	{
		if (fileList[i] == saveFileNameCsv)
		{
			makeFile = true;
			break;
		}
	}
	if (!makeFile)
	{
		std::cout << "Not Find File" << std::endl;
		return;
	}

	rapidcsv::Document doc(fileName, rapidcsv::LabelParams(-1, -1));
	RestLine();
	ResetGrid();
	WallResetCollied();
	wallWidthCount = doc.GetCell<int>(0, 1);
	wallHeightCount = doc.GetCell<int>(1, 1);



	gridTile = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	gridTile->Load(fileName, false);

	objectSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	objectSprite->LoadObject(fileName, false,0);

	thirdSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	thirdSprite->LoadObject(fileName, false,1);

	wallWidthCount = gridTile->GetWallSize().x;
	wallHeightCount = gridTile->GetWallSize().y;
	if (!drawGridAllowed)
	{
		drawGridAllowed = true;
	}
	MakeLine();
	makeGridCheck = true;
	
	int newHeight = wallHeightCount + 4 + 2+1;
	int size = doc.GetCell<int>(1, newHeight-2);
	for (int i = 0; i < size; ++i)
	{
		WallType type = static_cast<WallType>(doc.GetCell<int>(0, newHeight));
		sf::RectangleShape shape;
		shape.setPosition({ doc.GetCell<float>(1, newHeight) ,doc.GetCell<float>(2, newHeight) });
		shape.setSize({ doc.GetCell<float>(3, newHeight) ,doc.GetCell<float>(4, newHeight) });
		shape.setOutlineThickness(2);
		switch (static_cast<int>(type))
		{
		case 0:
			shape.setOutlineColor(sf::Color::Red);
			break;
		case 1:
			shape.setOutlineColor(sf::Color::Green);
			break;
		case 2:
			shape.setOutlineColor(sf::Color::Yellow);
			break;
		case 3:
			shape.setOutlineColor(sf::Color::Blue);
			break;
		}
		shape.setFillColor(sf::Color::Transparent);
		colliedShape.push_back({ type,shape });

		newHeight++;
	}
}


void SceneMaptool::ListFilesInDirectory(const std::string& folderPath)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((folderPath + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cerr << "Error finding files in directory." << std::endl;
		return;
	}

	fileCount = 0;

	do {
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			// 디렉토리 스킵
		}
		else {
			//std::cout << "파일 이름: " << findFileData.cFileName << std::endl;
			fileList.push_back(findFileData.cFileName);
			++fileCount;
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);

	//std::cout << "폴더 안의 파일 개수: " << fileCount << std::endl;
}


