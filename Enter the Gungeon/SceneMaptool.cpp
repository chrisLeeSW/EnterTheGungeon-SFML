#include "stdafx.h"
#include "SceneMaptool.h"
#include "SpriteGo.h"
#include "TileMap.h"
#include "UiButton.h"
#include "TextGo.h"

SceneMaptool::SceneMaptool() : Scene(SceneId::MapTool), tileMap(nullptr), view(1.0f), wallWidthCount(5), wallHeightCount(3), doubleBySclaeX(2.f), doubleBySclaeY(2.f), minWallWidthCount(5), 
	minWallHeightCount(3),setTile(false)
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

	wallWidthCount=5;
	wallHeightCount=3;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	

	view = 1.0f;
}

void SceneMaptool::Exit()
{
	Release();
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
			if (!setTile) setTile = true;
			currentTileSprite->SetActive(setTile);
		}
	}
	
	if (drawGridAllowed && setTile) 
	{
		
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0))
	{
		sf::Vector2i gridIndex = (sf::Vector2i)ScreenToWorldPos(INPUT_MGR.GetMousePos())/50;
		std::cout << "X : " << gridIndex.x <<'t';
		std::cout << "y : " << gridIndex.y << std::endl;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad7))
	{
		drawGridAllowed = false;
		linesMap.clear();
	} // Ui로 만들예정


	//
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad8))
	{
		int currentIndex;
		for (int i = 0;i < tiles.size();++i)
		{
			
			if (currentTileSprite->sprite.getTextureRect() == tiles[i].spr->sprite.getTextureRect())
			{
				currentIndex = i;
				std::cout << currentIndex << std::endl;
				break;
			}
		}
	}
	//

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
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
		std::cout << "Clock" << std::endl;
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
		std::cout << "Clock" << std::endl;
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
		std::cout << "Creating and drawing rectangles" << std::endl;
		if (!drawGridAllowed)
		{
			drawGridAllowed = true;
		}
		else return;
		if (drawGridAllowed)
		{
			//linesMap.clear();

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

	};
	makeUi->sortLayer = 100;

	currentTileSpriteBackGround=(SpriteGo*)AddGo(new SpriteGo("graphics/MapMakerMenu.png", "CurrentTileBackGround"));
	currentTileSpriteBackGround->sprite.setTextureRect({ 12,120,100,100 });
	currentTileSpriteBackGround->SetPosition(windowSize.x * 0.225f, windowSize.y * 0.125f); //0.125 0.19
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
	currentTileSprite->SetActive(setTile);
	currentTileSprite->SetOrigin(Origins::MC);
	currentTileSprite->SetPosition(currentTileSpriteBackGround->GetPosition());
	currentTileSprite->sortLayer = 101;
	currentTileSprite->SetScale(doubleBySclaeX, doubleBySclaeY);

}

