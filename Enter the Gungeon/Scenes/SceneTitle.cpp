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
		SCENE_MGR.ChangeScene(SceneId::Game);
	}

	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.ChangeScene(SceneId::BulletEditor);
	} -> 테스트 코드 진행 으로 주석 처리함
		
	*/ 

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		SCENE_MGR.ChangeScene(SceneId::MapTool);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

