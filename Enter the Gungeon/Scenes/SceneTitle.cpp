#include "stdafx.h"
#include "SceneTitle.h"
#include "Framework/Framework.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"

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
	
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

