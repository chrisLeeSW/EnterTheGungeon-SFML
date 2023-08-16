#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	
}

void SceneTitle::Init() 
{
	Release();

	TextGo* sceneName = (TextGo*)AddGo(new TextGo("", "Scene Name"));
	sceneName->sortLayer = 100;
	sceneName->text.setCharacterSize(25);
	sceneName->text.setFillColor(sf::Color::White);
	sceneName->text.setString(L"¾À Å¸ÀÌÆ²");

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

