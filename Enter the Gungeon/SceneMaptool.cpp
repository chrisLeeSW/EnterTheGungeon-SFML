#include "stdafx.h"
#include "SceneMaptool.h"
#include "SpriteGo.h"
#include "TileMap.h"
#include "UiButton.h"
#include "TextGo.h"
SceneMaptool::SceneMaptool() : Scene(SceneId::MapTool), tileMap(nullptr), view(1.0f), makeWallWidthCount(5), makeWallHeightCount(3), doubleBySclaeX(2.f), doubleBySclaeY(2.f), minWallWidthCount(5),
	minWallHeightCount(3)
{
	resourceListPath = "script/SceneMapToolResourceList.csv";
}

void SceneMaptool::Init()
{
	Release();
	
	SettingUiSprite();
	SettingUiText();


	for (auto go : gameObjects)
	{
		go->Init();
	}
	/*tileMap = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png","TileMap"));

	testPlayerCollied = (SpriteGo*)AddGo(new SpriteGo("graphics/testPlayer.png", "test"));
	testPlayerCollied->SetOrigin(Origins::MC);
	testPlayerCollied->SetPosition(0.f,-250.f);
	for (auto go : gameObjects)
	{
		go->Init();
	
	//tileMap->Load("MapFile/map1.csv");
	//tileMap->SetOrigin(Origins::BC); // BC로 충돌검사 확인
	//shape.setSize(sf::Vector2f{ (-(tileMap->vertexArray.getBounds().left) + tileMap->vertexArray.getBounds().width), (-(tileMap->vertexArray.getBounds().top) + tileMap->vertexArray.getBounds().height) });
	*/

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

	makeWallWidthCount=5;
	makeWallHeightCount=3;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	

	view = 1.0f;
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


	makeWallWidthSprite = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "MapXSizeSprite"));
	makeWallWidthSprite->sprite.setTextureRect({ 12,84,71,30 });
	makeWallWidthSprite->SetOrigin(Origins::MC);
	makeWallWidthSprite->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeWallWidthSprite->SetPosition(windowSize.x * 0.06f, windowSize.y * 0.1f);
	makeWallWidthSprite->sortLayer = 100;

	makeWallHeightSprite = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "MapYSizeSprite"));
	makeWallHeightSprite->sprite.setTextureRect({ 12,84,71,30 });
	makeWallHeightSprite->SetOrigin(Origins::MC);
	makeWallHeightSprite->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeWallHeightSprite->SetPosition(makeWallWidthSprite->GetPosition().x, makeWallWidthSprite->GetPosition().y + makeWallHeightSprite->sprite.getGlobalBounds().height * 1.3f);
	makeWallHeightSprite->sortLayer = 100;

	makeWallWidthCountIncrease= (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallWidthSizeIncrease"));
	makeWallWidthCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
	makeWallWidthCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeWallWidthCountIncrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.09f);
	makeWallWidthCountIncrease->SetOrigin(Origins::MC);

	makeWallWidthCountIncrease->OnEnter = [this]()
	{
		makeWallWidthCountIncrease->sprite.setTextureRect({ 11,55,50,20 });
	};
	makeWallWidthCountIncrease->OnExit = [this]()
	{
		makeWallWidthCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
		makeWallWidthCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeWallWidthCountIncrease->OnClick = [this]()
	{
		makeWallWidthCount++;
	};
	makeWallWidthCountIncrease->sortLayer = 100;


	makeWallHeightCountIncrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallHeightSizeIncrease"));
	makeWallHeightCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
	makeWallHeightCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeWallHeightCountIncrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.16f);
	makeWallHeightCountIncrease->SetOrigin(Origins::MC);
	makeWallHeightCountIncrease->OnEnter = [this]()
	{
		makeWallHeightCountIncrease->sprite.setTextureRect({ 11,55,50,20 });
	};
	makeWallHeightCountIncrease->OnExit = [this]()
	{
		makeWallHeightCountIncrease->sprite.setTextureRect({ 10,27,50,20 });
		makeWallHeightCountIncrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeWallHeightCountIncrease->OnClick = [this]()
	{
		makeWallHeightCount++;
	};
	makeWallHeightCountIncrease->sortLayer = 100;




	makeWallWidthCountDecrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallWidthSizeDecrease"));
	makeWallWidthCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
	makeWallWidthCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeWallWidthCountDecrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.12f);
	makeWallWidthCountDecrease->SetOrigin(Origins::MC);

	makeWallWidthCountDecrease->OnEnter = [this]()
	{
		makeWallWidthCountDecrease->sprite.setTextureRect({ 11,55,50,20 });
		makeWallWidthCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeWallWidthCountDecrease->OnExit = [this]()
	{
		makeWallWidthCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
		makeWallWidthCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeWallWidthCountDecrease->OnClick = [this]()
	{
		makeWallWidthCount--;
		if (makeWallWidthCount < minWallWidthCount)	makeWallWidthCount = minWallWidthCount;
	};
	makeWallWidthCountDecrease->sortLayer = 100;
	



	makeWallHeightCountDecrease = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "WallHeightSizeDecrease"));
	makeWallHeightCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
	makeWallHeightCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	makeWallHeightCountDecrease->SetPosition(windowSize.x * 0.125f, windowSize.y * 0.19f);
	makeWallHeightCountDecrease->SetOrigin(Origins::MC);

	makeWallHeightCountDecrease->OnEnter = [this]()
	{
		makeWallHeightCountDecrease->sprite.setTextureRect({ 11,55,50,20 });
		makeWallHeightCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeWallHeightCountDecrease->OnExit = [this]()
	{
		makeWallHeightCountDecrease->sprite.setTextureRect({ 10,27,50,20 });
		makeWallHeightCountDecrease->SetScale(doubleBySclaeX, doubleBySclaeY);
	};
	makeWallHeightCountDecrease->OnClick = [this]()
	{
		makeWallHeightCount--;
		if (makeWallHeightCount < minWallHeightCount)	makeWallHeightCount = minWallHeightCount;
	};
	makeWallHeightCountDecrease->sortLayer = 100;

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
		if (!drawShape)
		{
			drawShape = true;
		}
		else return;
	};
	makeUi->sortLayer = 100;
}
void SceneMaptool::Exit()
{
	Scene::Exit();
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

	makerWallWidthCountText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeText"));
	makerWallWidthCountText->text.setCharacterSize(20);
	makerWallWidthCountText->sortLayer = 100;
	makerWallWidthCountText->SetPosition(makeWallWidthSprite->GetPosition());

	makerWallHeightCountText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeText"));
	makerWallHeightCountText->text.setCharacterSize(20);
	makerWallHeightCountText->sortLayer = 100;
	makerWallHeightCountText->SetPosition(makeWallHeightSprite->GetPosition());

	makeWallWidthCountIncreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeIncreaseText"));
	makeWallWidthCountIncreaseText->text.setCharacterSize(20);
	makeWallWidthCountIncreaseText->SetOrigin(Origins::BC);
	makeWallWidthCountIncreaseText->text.setString("+");
	makeWallWidthCountIncreaseText->sortLayer = 100;
	makeWallWidthCountIncreaseText->SetPosition(makeWallWidthCountIncrease->GetPosition() - sf::Vector2f{ 0.f, makeWallWidthCountIncrease->text.getCharacterSize() * 0.25f });

	makeWallWidthCountDecreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallWidthSizeDecreaseText"));
	makeWallWidthCountDecreaseText->text.setCharacterSize(20);
	makeWallWidthCountDecreaseText->SetOrigin(Origins::BC);
	makeWallWidthCountDecreaseText->text.setString("-");
	makeWallWidthCountDecreaseText->sortLayer = 100;
	makeWallWidthCountDecreaseText->SetPosition(makeWallWidthCountDecrease->GetPosition() - sf::Vector2f{ 0.f, makeWallWidthCountDecrease->text.getCharacterSize() * 0.5f });

	makeWallHeightCountIncreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallHeightSizeIncreaseText"));
	makeWallHeightCountIncreaseText->text.setCharacterSize(20);
	makeWallHeightCountIncreaseText->SetOrigin(Origins::BC);
	makeWallHeightCountIncreaseText->text.setString("+");
	makeWallHeightCountIncreaseText->sortLayer = 100;
	makeWallHeightCountIncreaseText->SetPosition(makeWallHeightCountIncrease->GetPosition() - sf::Vector2f{ 0.f, makeWallHeightCountIncrease->text.getCharacterSize() * 0.25f });

	makeWallHeightCountDecreaseText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "WallHeightSizeDEcreaseText"));
	makeWallHeightCountDecreaseText->text.setCharacterSize(20);
	makeWallHeightCountDecreaseText->SetOrigin(Origins::BC);
	makeWallHeightCountDecreaseText->text.setString("-");
	makeWallHeightCountDecreaseText->sortLayer = 100;
	makeWallHeightCountDecreaseText->SetPosition(makeWallHeightCountDecrease->GetPosition() - sf::Vector2f{ 0.f, makeWallHeightCountDecrease->text.getCharacterSize() * 0.6f });

	makeUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "makeUiText"));
	makeUiText->text.setCharacterSize(20);
	makeUiText->SetOrigin(Origins::BC);
	makeUiText->text.setString("make");
	makeUiText->sortLayer = 100;
	makeUiText->SetPosition(makeUi->GetPosition() - sf::Vector2f{ 0.f, makeUi->text.getCharacterSize() * 0.125f });

}

void SceneMaptool::Update(float dt)
{
	Scene::Update(dt);

	std::stringstream wallWidthSize;
	wallWidthSize << "Width : " << makeWallWidthCount;
	makerWallWidthCountText->text.setString(wallWidthSize.str());
	makerWallWidthCountText->SetOrigin(Origins::BC);

	std::stringstream wallHeightSize;
	wallHeightSize << "Height : " << makeWallHeightCount;
	makerWallHeightCountText->text.setString(wallHeightSize.str());
	makerWallHeightCountText->SetOrigin(Origins::BC);

	if (drawShape)
	{
		shape.clear();
		sf::Vector2f shapeSize = { 50.f,50.f };
		sf::Vector2f startPos = { 0, 0 };
		sf::Vector2f currPos = startPos;

		for (int i = 0;i < makeWallHeightCount;++i)
		{
			for (int k = 0;k < makeWallWidthCount;++k)
			{
				sf::RectangleShape roopShape;
				roopShape.setSize(shapeSize);
				Utils::SetOrigin(roopShape, Origins::MC);
				float x = shapeSize.x;
				roopShape.setPosition(currPos.x + (x * k), currPos.y);
				roopShape.setOutlineColor(sf::Color::Red);
				roopShape.setOutlineThickness(1.0f);
				roopShape.setFillColor(sf::Color(0, 0, 0, 0));
				shape.push_back(roopShape);
			}
			currPos.y += shapeSize.y;
		}
	}

	/*playerPos = testPlayerCollied->GetPosition();
	playerDir.x=INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	playerDir.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
	playerPos +=  playerDir * 100.f * dt;
	testPlayerCollied->SetPosition(playerPos);

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Middle))
	{
		sf::Vector2f worldPose = ScreenToWorldPos(INPUT_MGR.GetMousePos());
		float moveSpeed = 0.01f;
		worldView.move(-worldPose.x * moveSpeed,-worldPose.y * moveSpeed);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		view += 0.05f;
		tileMap->SetVewScale(view);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		view -= 0.05f;
		tileMap->SetVewScale(view);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::End))
	{
		view = 1.0f;
		tileMap->SetVewScale(view);
	}
	////csv 파일로 해서 그리는거 확인 완료 */
	
}

void SceneMaptool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.setView(worldView);
	if (drawShape)
	{
		for (auto& grid : shape)
		{
			window.draw(grid);
		}
	}
}
