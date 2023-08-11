#include "stdafx.h"
#include "GameMapTestScene.h"
#include "TileMap.h"
GameMapTestScene::GameMapTestScene():Scene(SceneId::GameMapTestScene)
{
	resourceListPath = "script/GameMapTestScene.csv";
}

void GameMapTestScene::Init()
{



	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void GameMapTestScene::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void GameMapTestScene::Enter()
{
	Scene::Enter();
	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);



	tileRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	tileRoom1->SetStartPos(-300.f, -100.f);
	tileRoom1->Load("Room/TileMapFile/Room1.csv",false);

	objectRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	objectRoom1->SetStartPos(-300.f, -100.f);
	objectRoom1->LoadObject("Room/TileMapFile/Room1.csv", false);


	tileRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	tileRoom1->Load("Room/TileMapFile/Room2.csv", false);

	objectRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	objectRoom1->LoadObject("Room/TileMapFile/Room2.csv", false);
}

void GameMapTestScene::Exit()
{
	
	Scene::Exit();
}

void GameMapTestScene::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(-1.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(1.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, 1.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, -1.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneId::MapTool);
	}
}

void GameMapTestScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
