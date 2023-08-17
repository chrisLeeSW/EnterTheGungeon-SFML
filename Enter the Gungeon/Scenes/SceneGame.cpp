#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Weapon.h"
#include "TileMap.h"
#include "WeaponMgr.h"
#include "Equipment.h"
#include "Enemy.h"
#include "InteractionObject.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "script/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();


	shadow = (SpriteGo*)/*scene->*/AddGo(new SpriteGo("graphics/Shadow.png"));
	shadow->SetOrigin(Origins::MC);
	shadow->sortLayer = -1;

	worldView.setSize(windowSize * 0.5f);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	//player = (Player*)AddGo(new Player());
	//weapon = (Weapon*)AddGo(new Weapon());

	

	equipment = (Equipment*)AddGo(new Equipment());

	testenm1 = (Enemy*)AddGo(new Enemy(EnemyName::BulletKin)); //test
	testenm1->SetOrigin(Origins::BC); //test
	testenm1->SetEnemy(100.f, 50.f, 50.f, 1.f); //test
	testenm1->SetPosition(200, 200); //test
	testenm1->sortLayer = 0;
	enemylist.push_back(testenm1);

	MakeTestRoom(3);
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
	if (player != nullptr)
	{
		delete player;
	}

	player = (Player*)AddGo(new Player((Player::Types)playertype));
	player->sortLayer = 0;
	player->Init();
	player->SetEnemyList(enemylist);
	testenm1->SetPlayer(player); //test


	player->SetPosition(0.f,0.f);



	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
	player->Reset();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	//WEAPON_MGR.Update(dt);
	shadow->SetPosition(player->GetPosition());

	//sf::Vector2i playerTile = (sf::Vector2i)(player->GetPosition()/ 50.f);
	//for (int i = 0;i < gameDevMap->tiles.size();++i)
	//{
	//	if (gameDevMap->tiles[i].x == playerTile.x && gameDevMap->tiles[i].y == playerTile.y)
	//	{
	//		if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallTop))
	//		{
	//			player->SetPosition(player->GetPosition().x, 50.f);
	//		}
	//		if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallRight))
	//		{
	//			player->SetPosition(50.f,player->GetPosition().y);
	//		}
	//		if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallLeft))
	//		{
	//			player->SetPosition((gameDevMap->vertexArray.getBounds().left + gameDevMap->vertexArray.getBounds().width)-50.f,player->GetPosition().y);
	//		}
	//		if (gameDevMap->tiles[i].texIndex == static_cast<int>(MapObjectType::WallDown))
	//		{
	//			//player->SetPosition(player->GetPosition().x, (gameDevMap->vertexArray.getBounds().top + gameDevMap->vertexArray.getBounds().height)-50.f);
	//		}
	//	}
	//}


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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}

	worldView.setCenter(player->GetPosition());
	ColliedTest();
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	for (auto& arry : colliedShape)
	{
		window.draw(arry.shape);
	}
}

void SceneGame::SetPlayer(int a)
{
	playertype =  a;
}

void SceneGame::MakeTestRoom(int size)
{
	for (int i = 0;i < size;++i)
	{
		TileMap* tileRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
		sf::Vector2f pos; //= { -300.f+(i * 500.f),-300.f + (i * 500.f) }; // 랜덤 설정
		
		if (i == 0)
		{
			pos = sf::Vector2f{ -300.f,-300.f };
			tileRoom1->SetStartPos(pos);
			tileRoom1->Load("Room/TileMapFile/Room01.csv");
		}
		else if (i == 1)
		{
			pos = sf::Vector2f{ 200.f,200.f };
			tileRoom1->SetStartPos(pos);
			tileRoom1->Load("Room/TileMapFile/Room02.csv");
		}
		else if (i == 2)
		{
			pos = sf::Vector2f{	-300.f,150.f };
			tileRoom1->SetStartPos(pos);
			tileRoom1->Load("Room/TileMapFile/Room03.csv");
		}
		
		tileRoom1->sortLayer = -1;
		for (int i = 0; i < tileRoom1->tiles.size(); ++i)
		{
			//	objects
			switch (static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes))
			{
			case MapObjectType::WallDown:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,250,50,50 });
				spr->SetPosition(pos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, pos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr); // wall클래스 생성
			}
			break;
			case MapObjectType::LibraryDown:
			{
				SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
				spr->sprite.setTextureRect({ 0,650,50,50 });
				spr->SetPosition(pos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, pos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
				spr->sortLayer = 2;
				objects.push_back(spr); // wall클래스 생성
			}
			break;
			case MapObjectType::Pot:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->SetPosition(pos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, pos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::Book1:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->SetPosition(pos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, pos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), spr });
			}
			break;
			
			}
		}
		tileRoom1->MakeWall("Room/TileMapFile/Room01.csv");
		for (int i = 0; i < tileRoom1->colliedShape.size(); ++i)
		{
			tileRoom1->colliedShape[i].shape.setPosition(tileRoom1->colliedShape[i].shape.getPosition() + pos);
			colliedShape.push_back(tileRoom1->colliedShape[i]);
		}
		tileRoom.push_back(tileRoom1);
	}
}

void SceneGame::ColliedTest()
{
	for (auto& arry : colliedShape)
	{
		if (arry.type == WallType::Wall&& arry.shape.getGlobalBounds().contains(player->GetPosition()))
		{
			std::cout << "Wall Collied" << std::endl;
		}
		else if (arry.shape.getGlobalBounds().intersects(shape.getGlobalBounds()))
		{
			switch (arry.type)
			{
			case WallType::WalloBlocker:
				std::cout << "Wall WalloBlocker" << std::endl;
				break;
			case WallType::FallingZone:
				std::cout << "Wall FallingZone" << std::endl;
				break;
			case WallType::TeleportZone:
				std::cout << "Wall TeleportZone" << std::endl;
				break;
			}
		}
	}
}
