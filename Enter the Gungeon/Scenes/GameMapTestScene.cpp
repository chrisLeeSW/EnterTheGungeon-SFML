#include "stdafx.h"
#include "GameMapTestScene.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "AnimationController.h"
#include "InteractionObject.h"


GameMapTestScene::GameMapTestScene() :Scene(SceneId::GameMapTestScene)
{
	resourceListPath = "script/GameMapTestScene.csv";
}

void GameMapTestScene::Init()
{
	startTileRoom = { 0.f,0.f };
	tileWallSize = { 100,100};
	sf::Vector2f pos = { 0.f,0.f };

	tileRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	tileRoom1->SetOrigin(Origins::MC);
	tileRoom1->NoneFileLoad(tileWallSize.x , tileWallSize.y,true,false);
	tileRoom1->SetStartPos(pos);
	tileRoom1->Divide();

	for (int i = 0;i<tileRoom1->tiles.size();++i)
	{
		switch (static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes))
		{
		case MapObjectType::WallDown:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
			spr->sprite.setTextureRect({ 0,250,50,50 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x , tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y );
			spr->sortLayer = 2;
			objects.push_back(spr); // wall클래스 생성
		}
		break;
		case MapObjectType::LibraryDown:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
			spr->sprite.setTextureRect({ 0,650,50,50 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x , tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y );
			spr->sortLayer = 2;
			objects.push_back(spr); // wall클래스 생성
		}
		break;
		case MapObjectType::Pot:
		{
			InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 0,800,50,50 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x , tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y );
			spr->sortLayer = 0;
			interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes) ,spr });
		}
		break;
		case MapObjectType::Book1:
		{
			InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 0,850,50,50 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition( tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
			spr->sortLayer = 0;
			interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes) ,spr });
		}
		break;
		}
	}
	
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
	worldView.setSize(windowSize*0.5f);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);




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
		worldView.move(1.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(-1.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, -1.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, 1.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(1.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(0.5f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		tileRoom1->Divide();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F2))
	{
		tileRoom1->MakeRoom();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F3))
	{
		tileRoom1->ConnectRoom();
	}
}

void GameMapTestScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
}
