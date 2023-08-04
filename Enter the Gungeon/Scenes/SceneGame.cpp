#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{

}

void SceneGame::Init()
{
	Release();

	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{

	for (auto go : gameObjects)
	{
		delete go;
	}

}

void SceneGame::Enter()
{

	
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);

}