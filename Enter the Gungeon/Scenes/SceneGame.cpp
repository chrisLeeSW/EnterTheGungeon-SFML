#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Weapon.h"


SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "script/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();

	player = (Player*)AddGo(new Player());
	weapon = (Weapon*)AddGo(new Weapon());
	shadow = (SpriteGo*)AddGo(new SpriteGo("graphics/Shadow.png"));
	shadow->SetOrigin(Origins::MC);
	shadow->SetScale(3.5, 3.5);
	shadow->sortLayer = -1;
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

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	weapon->SetPlayer(player);
	player->SetPosition(0.f, 0.f);

}

void SceneGame::Exit()
{
	Scene::Exit();
	player->Reset();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	shadow->SetPosition(player->GetPosition());
}


void SceneGame::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);

}