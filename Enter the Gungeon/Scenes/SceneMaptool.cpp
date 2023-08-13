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
minWallHeightCount(3)
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

	worldView.setSize(windowSize);
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
	//MakeGrid();
	if (IncreaseOrDecrease)
	{

		TileMap* temp1 = gridTile;
		TileMap* temp2 = objectSprite;

		gridTile = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		gridTile->tiles.resize(temp1->tiles.size());
		for (int i = 0;i < temp1->tiles.size();++i)
		{
			gridTile->tiles[i] = temp1->tiles[i];
		}
		gridTile->NoneFileLoad(wallWidthCount, wallHeightCount);
		
	
		objectSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		
		objectSprite->tiles.resize(temp2->tiles.size());
		for (int i = 0;i < temp1->tiles.size();++i)
		{
			objectSprite->tiles[i] = temp2->tiles[i];
		}
		objectSprite->NoneFileLoad(wallWidthCount, wallHeightCount);
		
		RemoveGo(temp1);
		temp1 = nullptr;

		RemoveGo(temp2);
		temp2 = nullptr;
		IncreaseOrDecrease = false;
		// 후반작업
	}


	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(-0.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(0.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, 0.5f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, -0.5f);
	}

	for (auto& tile : tiles)
	{
		if (tile.spr->sprite.getGlobalBounds().contains(INPUT_MGR.GetMousePos()) && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			currentTileSprite->sprite.setTextureRect(tile.spr->sprite.getTextureRect());
		}
	}

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 50;
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
		if (count == (int)MapObjectType::Pot || count == (int)MapObjectType::WallDown || count == (int)MapObjectType::LibraryDown || count == (int)MapObjectType::Book1)
		{
			objectSprite->ChangeTile(gridIndex.x, gridIndex.y, count, currentTileSprite->sprite.getTextureRect());
		}
		else
		{
			gridTile->ChangeTile(gridIndex.x, gridIndex.y, count, currentTileSprite->sprite.getTextureRect());
		}
	}

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Right) && INPUT_MGR.GetKey(sf::Keyboard::LControl))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 50;
		gridTile->ChangeTile(gridIndex.x, gridIndex.y, static_cast<int>(MapObjectType::None), sf::IntRect{ 50,0,50,50 });
	}
	if (INPUT_MGR.GetMouseButton(sf::Mouse::Right) && INPUT_MGR.GetKey(sf::Keyboard::LShift))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 50;
		objectSprite->ChangeTile(gridIndex.x, gridIndex.y, static_cast<int>(MapObjectType::None), sf::IntRect{ 50,0,50,50 });
	}




	// ?? 왜있는지 기억안남 ;;
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad8))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos()) / 50;
		int count = gridIndex.x * wallWidthCount + gridIndex.y;

		if (count > objectSprite->tiles.size()) return;
		std::cout << tiles[count].spr->sprite.getPosition().x << std::endl;
		std::cout << tiles[count].spr->sprite.getPosition().y << std::endl;

		std::cout << objectSprite->tiles[count].x * 50.f << "            " << objectSprite->tiles[count].y * 50.f;
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
}

void SceneMaptool::SettingUiSprite()
{
	saveUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "SaveUi"));
	saveUi->sprite.setTextureRect({ 10,27,50,20 });
	saveUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	saveUi->SetPosition(windowSize.x * 0.05f, windowSize.y * 0.5f);
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
	};
	saveUi->sortLayer = 100;



	loadUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "LoadUi"));
	loadUi->sprite.setTextureRect({ 10,27,50,20 });
	loadUi->SetScale(doubleBySclaeX, doubleBySclaeY);
	loadUi->SetPosition(windowSize.x * 0.11f, windowSize.y * 0.5f);
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
	};
	restUi->sortLayer = 100;



	currentTileSpriteBackGround = (SpriteGo*)AddGo(new SpriteGo("graphics/MapMakerMenu.png", "CurrentTileBackGround"));
	currentTileSpriteBackGround->sprite.setTextureRect({ 12,120,100,100 });
	currentTileSpriteBackGround->SetPosition(windowSize.x * 0.225f, windowSize.y * 0.125f);
	currentTileSpriteBackGround->SetScale(doubleBySclaeX, doubleBySclaeY);
	currentTileSpriteBackGround->SetOrigin(Origins::MC);
	currentTileSpriteBackGround->sortLayer = 100;


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

	fileNameTexBox = (TextBox*)AddGo(new TextBox("fonts/OpenSans-Semibold.ttf", "direction"));
	fileNameTexBox->box.setSize({ 200, 50 });
	fileNameTexBox->text.setCharacterSize(10);
	fileNameTexBox->SetOrigin(Origins::MC);
	fileNameTexBox->SetPosition(windowSize.x * 0.08f, windowSize.y * 0.3f);
	fileNameTexBox->sortLayer = 100;

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
		spriteTexture->SetPosition(windowSize.x * 0.025f + (size.x++ * curPos.x), windowSize.y * 0.6f + (size.y * curPos.y));
		spriteTexture->sprite.setTextureRect({ rows[0],rows[1] ,rows[2] ,rows[3] });
		if (size.x == 5)
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
		sf::Vector2f mapTileSize = { 50.f,50.f };
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
	gridTile->NoneFileLoad(wallWidthCount, wallHeightCount);

	objectSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	objectSprite->NoneFileLoad(wallWidthCount, wallHeightCount);

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

			doc.SetCell<std::string>(j, i, tileInfo);
			count++;
		}
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

	wallWidthCount = doc.GetCell<int>(0, 1);
	wallHeightCount = doc.GetCell<int>(1, 1);



	gridTile = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	gridTile->Load(fileName, false);

	objectSprite = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	objectSprite->LoadObject(fileName, false);

	wallWidthCount = gridTile->GetWallSize().x;
	wallHeightCount = gridTile->GetWallSize().y;
	if (!drawGridAllowed)
	{
		drawGridAllowed = true;
	}
	MakeLine();
	makeGridCheck = true;
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


