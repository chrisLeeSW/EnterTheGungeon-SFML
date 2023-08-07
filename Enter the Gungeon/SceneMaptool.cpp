#include "stdafx.h"
#include "SceneMaptool.h"
#include "SpriteGo.h"
#include "TileMap.h"
SceneMaptool::SceneMaptool() : Scene(SceneId::MapTool), tileMap(nullptr), view(1.0f)
{
	resourceListPath = "script/SceneMapToolResourceList.csv";
}

void SceneMaptool::Init()
{
	Release();

	tileMap = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png","TileMap"));
	testPlayerCollied = (SpriteGo*)AddGo(new SpriteGo("graphics/testPlayer.png", "test"));
	testPlayerCollied->SetOrigin(Origins::MC);
	testPlayerCollied->SetPosition(0.f,-250.f);
	for (auto go : gameObjects)
	{
		go->Init();
	}

	tileMap->Load("MapFile/map1.csv");
	tileMap->SetOrigin(Origins::BC); // BC로 충돌검사 확인 
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



	view = 1.0f;
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
}

void SceneMaptool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
