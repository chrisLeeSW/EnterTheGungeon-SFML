#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Weapon.h"
#include "TileMap.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "script/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	player = (Player*)AddGo(new Player());
	weapon = (Weapon*)AddGo(new Weapon());

	gameDevMap = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	gameDevMap->Load("MapFile/map1.csv");
	gameDevMap->sortLayer = -1;

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

	

	weapon->SetPlayer(player);
	//player->SetPosition(0.f, 0.f);
	// 
	//
	player->SetPosition((gameDevMap->vertexArray.getBounds().left + gameDevMap->vertexArray.getBounds().width)/2, (gameDevMap->vertexArray.getBounds().top + gameDevMap->vertexArray.getBounds().height) / 2);
	//
}

void SceneGame::Exit()
{
	Scene::Exit();
	player->Reset();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	std::cout << "this:" << player->GetPosition().x << "," << player->GetPosition().y << std::endl;

	//
	sf::Vector2i playerTile = (sf::Vector2i)(player->GetPosition()/ 50.f);
	for (int i = 0;i < gameDevMap->tiles.size();++i)
	{
		if (gameDevMap->tiles[i].x == playerTile.x && gameDevMap->tiles[i].y == playerTile.y)
		{
			if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallTop))
			{
				player->SetPosition(player->GetPosition().x, 50.f);
			}
			if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallRight))
			{
				player->SetPosition(50.f,player->GetPosition().y);
			}
			if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallLeft))
			{
				player->SetPosition((gameDevMap->vertexArray.getBounds().left + gameDevMap->vertexArray.getBounds().width)-50.f,player->GetPosition().y);
			}
			if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallDown))
			{
				//player->SetPosition(player->GetPosition().x, (gameDevMap->vertexArray.getBounds().top + gameDevMap->vertexArray.getBounds().height)-50.f);
			}

		}
	}

	// 대각선 충돌이 문제가 있음 테스트 코드로 사용
	
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad6))
	{
		worldView.move(-0.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad4))
	{
		worldView.move(0.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad8))
	{
		worldView.move(0.0f, 0.5f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Numpad5))
	{
		worldView.move(0.0f, -0.5f);
	}

	worldView.setCenter(player->GetPosition());

}

void SceneGame::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);

}