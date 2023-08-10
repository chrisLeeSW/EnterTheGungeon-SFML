#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Weapon.h"
#include "Scene.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "script/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();
	//Scene* scene = SCENE_MGR.GetCurrScene();
	//setplayer 써서 scene에 있는 player 할당해
	//SetPlayer(scene->currentPlayer);
	//player = (Player*)AddGo(new Player(Player::Types::Prisoner));
	//weapon = (Weapon*)AddGo(new Weapon());
	shadow = (SpriteGo*)/*scene->*/AddGo(new SpriteGo("graphics/Shadow.png"));
	shadow->SetOrigin(Origins::MC);
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

	//std::cout << "씬게임 릴리드";
}

void SceneGame::Enter()
{
	Scene::Enter();

	worldView.setSize(windowSize * 0.5f);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	//weapon->SetPlayer(player);

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

void SceneGame::SetPlayer(Player* player)
{
	this->player = player;
	this->player = (Player*)AddGo(new Player(player->GetType()));

	std::cout << "플레이어 넘김" << std::endl;
}
