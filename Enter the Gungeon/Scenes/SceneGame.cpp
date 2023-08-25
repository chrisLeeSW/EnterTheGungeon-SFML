#include "stdafx.h"
#include "SceneGame.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Weapon.h"
#include "TileMap.h"
#include "WeaponMgr.h"
#include "Book.h"
#include "Enemy.h"
#include "InteractionObject.h"
#include "PlayerUI.h"
#include "DropItem.h"
#include "DisplayItem.h"

#include "Boss.h"
#include "EnemyBullet.h"

#include "BossUI.h"

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

	windowSize *= 0.3f;

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	//player = (Player*)AddGo(new Player());
	//weapon = (Weapon*)AddGo(new Weapon());

	

	book = (Book*)AddGo(new Book());

	testenm1 = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::KeyBulletKin)); //test
	testenm1->SetOrigin(Origins::BC); //test
	testenm1->SetPosition(200, 200); //test
	testenm1->sortLayer = 0;

	testenm2 = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::BulletKin)); //test
	testenm2->SetOrigin(Origins::BC); //test
	testenm2->SetPosition(300, 300); //test
	testenm2->sortLayer = 0;

	testenm3 = (Enemy*)AddGo(new Enemy(Enemy::EnemyName::ShotgunKinBlue)); //test
	testenm3->SetOrigin(Origins::BC); //test
	testenm3->SetPosition(400, 400); //test
	testenm3->sortLayer = 0;

	enemylist.push_back(testenm1);
	enemylist.push_back(testenm2);
	enemylist.push_back(testenm3);

	test2 = (Boss*)AddGo(new Boss(Enemy::EnemyName::GatlingGull)); //test
	test2->SetOrigin(Origins::BC); //test
	test2->SetPosition(400.f, 0.f); //test
	enemylist.push_back(test2); //test

	bossui = (BossUI*)AddGo(new BossUI()); //test
	bossui->SetBoss(test2);
	bossui->SetOrigin(Origins::MC);
	bossui->SetPosition(windowSize.x * 0.5f, windowSize.y - 50.f);
	bossui->sortLayer = 100;

	DisplayItem* distest = (DisplayItem*)AddGo(new DisplayItem(DisplayItem::Names::Heart)); //test
	distest->SetOrigin(Origins::MC);
	distest->SetPosition(-50, 0);

	enemyBullets.OnCreate = [this](EnemyBullet* bullet)
	{
		bullet->pool = &enemyBullets;
	};
	enemyBullets.Init();

	dropitemPool.OnCreate = [this](DropItem* dropitem)
	{
		dropitem->pool = &dropitemPool;
	};
	dropitemPool.Init();

	MakeTestRoom(3);
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	enemyBullets.Release();
	dropitemPool.Release();

	for (auto go : gameObjects)
	{
		delete go;
	}
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
	testenm2->SetPlayer(player); //test
	testenm3->SetPlayer(player); //test

	test2->SetPlayer(player); //test

	DropItem* droptest = dropitemPool.Get(); //test
	droptest->SetType(DropItem::Types::Ammo);
	droptest->SetPosition(-200, 0);
	droptest->Init();
	AddGo(droptest);

	player->SetPosition(0.f,0.f);

	playerui = (PlayerUI*)AddGo(new PlayerUI(player));
	playerui->Init();
	playerui->Reset();
	Scene::Enter();

}

void SceneGame::Exit()
{
	Scene::Exit();
	player->Reset();

	ClearPool(enemyBullets);
	ClearPool(dropitemPool);
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	shadow->SetPosition(player->GetPosition());

	// 대각선 충돌이 문제가 있음 테스트 코드로 사용

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
		

		sf::Vector2f tileMapSize;
		sf::Vector2f objpos;
		objpos -= tileMapSize * 0.5f;
		if (i == 0)
		{
			pos = sf::Vector2f{ -300.f,-300.f };
			tileRoom1->SetStartPos(pos);
			tileRoom1->Load("Room/TileMapFile/direction1.csv");
			tileMapSize =tileRoom1->TileMapSize("Room/TileMapFile/direction1.csv");
			objpos = pos;
			objpos += tileRoom1->GetTileSize() * 0.5f;
		}
		else if (i == 1)
		{
			pos = sf::Vector2f{ 200.f,200.f };
			tileRoom1->SetStartPos(pos);
			tileRoom1->Load("Room/TileMapFile/Room02.csv");
			tileMapSize = tileRoom1->TileMapSize("Room/TileMapFile/Room02.csv");
			objpos = pos;
			objpos += tileRoom1->GetTileSize() * 0.5f;
		}
		else if (i == 2)
		{
			pos = sf::Vector2f{	-300.f,150.f };
			tileRoom1->SetStartPos(pos);
			tileRoom1->Load("Room/TileMapFile/Room03.csv");
			tileMapSize = tileRoom1->TileMapSize("Room/TileMapFile/Room03.csv");
			objpos = pos;
			objpos += tileRoom1->GetTileSize() * 0.5f;
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
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, objpos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
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
				spr->SetPosition(objpos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, objpos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
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
				spr->SetPosition(objpos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, objpos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
				spr->sortLayer = 0;
				interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), spr });
			}
			break;
			case MapObjectType::Book1:
			{
				InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
				spr->sprite.setTextureRect({ 0,850,50,50 });
				spr->SetScale(0.5f, 0.5f);
				spr->SetOrigin(Origins::MC);
				spr->SetPosition(objpos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, objpos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
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
		/*tileRoom1->Init();
		tileRoom1->Reset();*/
		tileRoom.push_back(tileRoom1);
		
	}
}

void SceneGame::ColliedTest()
{
	for (auto& arry : colliedShape)
	{
		if (arry.type == WallType::Wall&& arry.shape.getGlobalBounds().contains(player->GetPosition()))
		{
			//std::cout << "Wall Collied" << std::endl;
		}
		else if (arry.shape.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			switch (arry.type)
			{
			case WallType::WalloBlocker:
				//std::cout << "Wall WalloBlocker" << std::endl;
				break;
			case WallType::FallingZone:
				//std::cout << "Wall FallingZone" << std::endl;
				break;
			case WallType::TeleportZone:
				//std::cout << "Wall TeleportZone" << std::endl;
				break;
			}
		}
	}
}

void SceneGame::RenewBossUI()
{
	bossui->Renew();
}

ObjectPool<EnemyBullet>& SceneGame::GetPoolEnemyBullet()
{
	return enemyBullets;
}

ObjectPool<DropItem>& SceneGame::GetPoolDropItem()
{
	return dropitemPool;
}
