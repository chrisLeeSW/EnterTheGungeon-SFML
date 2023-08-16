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
	tileRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	sf::Vector2f pos = { -300.f,-300.f }; // 랜덤 설정
	tileRoom1->SetStartPos(pos);
	tileRoom1->Load("Room/TileMapFile/direction.csv");
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
		case MapObjectType::Pot:
		{
			InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes),"graphics/InteractionGameObjects.png"));
			spr->SetPosition(pos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x, pos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y);
			spr->sortLayer = 0;
			interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), spr });
		}
		break;
		case MapObjectType::Book1:
		{
			InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
			spr->SetPosition(pos.x + tileRoom1->tiles[i].x * tileRoom1->GetTileSize().x , pos.y + tileRoom1->tiles[i].y * tileRoom1->GetTileSize().y );
			spr->sortLayer = 0;
			interaction.push_back({ static_cast<MapObjectType>(tileRoom1->tiles[i].objectTypes), spr });
		}
		break;
		}
	}
	tileRoom1->MakeWall("Room/TileMapFile/direction.csv");
	for (int i = 0; i < tileRoom1->colliedShape.size(); ++i)
	{
		tileRoom1->colliedShape[i].shape.setPosition(tileRoom1->colliedShape[i].shape.getPosition() + pos);
		colliedShape.push_back(tileRoom1->colliedShape[i]);
	}
	tileRoom1->colliedShape;
	colliedShape;






	//tileRoom2 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	//sf::Vector2f pos1 = { pos.x,pos.y + (tileRoom1->vertexArray.getBounds().top + tileRoom1->vertexArray.getBounds().height)*7.f}; // 랜덤 설정
	//tileRoom2->SetStartPos(pos1);
	//tileRoom2->Load("Room/TileMapFile/Room3.csv", false);
	//for (int i = 0; i < tileRoom2->tiles.size(); ++i)
	//{
	//	//	objects
	//	switch (static_cast<MapObjectType>(tileRoom2->tiles[i].objectTypes))
	//	{
	//	case MapObjectType::WallDown:
	//	{
	//		SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
	//		spr->sprite.setTextureRect({ 0,250,50,50 });
	//		spr->SetPosition(pos1.x + tileRoom2->tiles[i].x * tileRoom2->GetTileSize().x, pos1.y + tileRoom2->tiles[i].y * tileRoom2->GetTileSize().y);
	//		spr->sortLayer = 2;
	//		objects.push_back(spr); // wall클래스 생성
	//	}
	//	break;
	//	case MapObjectType::Pot:
	//	{
	//		InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom2->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
	//		spr->SetPosition(pos1.x + tileRoom2->tiles[i].x * tileRoom2->GetTileSize().x, pos1.y + tileRoom2->tiles[i].y * tileRoom2->GetTileSize().y);
	//		spr->sortLayer = 0;
	//		interaction.push_back({ static_cast<MapObjectType>(tileRoom2->tiles[i].objectTypes), spr });
	//	}
	//	break;
	//	case MapObjectType::Book1:
	//	{
	//		InteractionObject* spr = (InteractionObject*)AddGo(new InteractionObject(static_cast<MapObjectType>(tileRoom2->tiles[i].objectTypes), "graphics/InteractionGameObjects.png"));
	//		spr->SetPosition(pos1.x + tileRoom2->tiles[i].x * tileRoom2->GetTileSize().x, pos1.y + tileRoom2->tiles[i].y * tileRoom2->GetTileSize().y);
	//		spr->sortLayer = 0;
	//		interaction.push_back({ static_cast<MapObjectType>(tileRoom2->tiles[i].objectTypes), spr });
	//	}
	//	break;
	//	}
	//}
	shape.setSize({ 5.f,5.f });
	shape.setPosition(tileRoom1->vertexArray.getBounds().left + tileRoom1->vertexArray.getBounds().width * 0.5f, tileRoom1->vertexArray.getBounds().top + tileRoom1->vertexArray.getBounds().height * 0.5f);

	/*std::cout << tileRoom1->vertexArray.getBounds().top + tileRoom1->vertexArray.getBounds().height << " " << pos1.y << std::endl;
	shape2.setSize({ 400.f,pos1.y - (tileRoom1->vertexArray.getBounds().top + tileRoom1->vertexArray.getBounds().height)  });
	shape2.setPosition({ tileRoom1->vertexArray.getBounds().left + tileRoom1->vertexArray.getBounds().width*0.5f -shape2.getSize().x*0.5f  ,(tileRoom1->vertexArray.getBounds().top + tileRoom1->vertexArray.getBounds().height)});
	shape2.setFillColor(sf::Color::Red);*/
	
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
	worldView.setSize(windowSize);
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
		worldView.move(-3.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(3.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, -3.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, 3.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneId::MapTool);
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::W))
	{
		shape.move(0.f, -2.5f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::S))
	{
		shape.move(0.f, 2.5f);
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		shape.move(-2.5f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::D))
	{
		shape.move(2.5f, 0.f);
	}

	if (!tileRoom1->vertexArray.getBounds().contains(shape.getPosition()))
	{
		std::cout << "???" << std::endl;
	}
	for (auto& arry : colliedShape)
	{
		if (arry.shape.getGlobalBounds().intersects(shape.getGlobalBounds()))
		{
			switch (arry.type)
			{
			case WallType::Wall:
				std::cout << "Wall Collied" << std::endl;
				break;
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

void GameMapTestScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	//window.draw(shape2);
	window.draw(shape);
	for (auto& arry : colliedShape)
	{
		window.draw(arry.shape);
	}
}
