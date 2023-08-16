#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	resourceListPath = "script/SceneTitleResourceList.csv";
}

void SceneTitle::Init() 
{
	Release();

	worldView.setSize(windowSize * 0.7f);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	SpriteGo* bg = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png"));
	bg->SetOrigin(Origins::MC);
	bg->sortLayer = -1;

	SpriteGo* logo = (SpriteGo*)AddGo(new SpriteGo("graphics/titletext.png"));
	logo->SetOrigin(Origins::MC);
	logo->SetPosition(0, -200.f);
	logo->sortLayer = 0;

	for (auto go : gameObjects)	
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	
}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneId::Lobby);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.ChangeScene(SceneId::BulletEditor);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		SCENE_MGR.ChangeScene(SceneId::MapTool);
	}
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}*/
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
	{
		SCENE_MGR.ChangeScene(SceneId::GameMapTestScene);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

