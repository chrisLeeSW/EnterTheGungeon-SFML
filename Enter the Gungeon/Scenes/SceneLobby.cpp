#include "stdafx.h"
#include "SceneLobby.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "InteractionObject.h"

SceneLobby::SceneLobby() : Scene(SceneId::Lobby)
{
	resourceListPath = "script/SceneLobbyResourceList.csv";
	prisonerSetPosition = { 100.f,100.f };
	pilotSetPosition = { 0.f,0.f };
}

void SceneLobby::Init()
{
	Release();
	
	worldView.setSize(windowSize * 0.5f);
	worldView.setCenter(0.f, 0.f);

	windowSize *= 0.3f;

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	MakeLobby();
	pilot = (Player*)AddGo(new Player(Player::Types::Pilot));
	prisoner = (Player*)AddGo(new Player(Player::Types::Prisoner));

	pilot->SetOrigin(Origins::BC);
	prisoner->SetOrigin(Origins::BC);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PilotFace.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PilotFaceIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PrisonerFace.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PrisonerFaceIdle.csv"));

	animation.SetTarget(&sprite);

	sprite.setScale(0.5f,0.5f);

	elevator = (SpriteGo*)AddGo(new SpriteGo("graphics/elevator.png", ""));
	elevator->SetPosition(0.f,-250);
	elevator->SetOrigin(Origins::MC);
	elevator->sortLayer = -1;
	elevator->SetScale(0.3f,0.3f);

	currentplayer = pilot;

	doorCollisionBox.setSize({ 25,25 });
	doorCollisionBox.setFillColor(sf::Color::Transparent);
	doorCollisionBox.setOutlineThickness(3);
	doorCollisionBox.setOutlineColor(sf::Color::White);
	doorCollisionBox.setPosition(elevator->sprite.getGlobalBounds().left + elevator->sprite.getGlobalBounds().width * 0.5f, elevator->sprite.getGlobalBounds().top + sprite.getGlobalBounds().height+ elevator->sprite.getGlobalBounds().height);
	doorCollisionBox.setPosition(elevator->sprite.getGlobalBounds().left + elevator->sprite.getGlobalBounds().width * 0.5f, elevator->sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);

	sf::Texture* tex;
	tex = RESOURCE_MGR.GetTexture("graphics/ui_HegemonyCredit.png");
	sf::Font* font = RESOURCE_MGR.GetFont("fonts/PF.ttf");

	spritehegemonyCredit.setTexture(*tex);
	spritehegemonyCredit.setPosition(windowSize.x *0.95f, 10.f);

	textHegemonyCredit.setFont(*font);
	textHegemonyCredit.setFillColor(sf::Color::White);
	textHegemonyCredit.setCharacterSize(45);
	textHegemonyCredit.setPosition(spritehegemonyCredit.getGlobalBounds().left + spritehegemonyCredit.getGlobalBounds().width, spritehegemonyCredit.getGlobalBounds().top);

	textHegemonyCredit.setScale(0.3f,0.3f);


	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneLobby::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneLobby::Enter()
{
	pilot->SetPosition(pilotSetPosition);
	prisoner->SetPosition(prisonerSetPosition);
	currentplayer = pilot;

	Scene::Enter();

	sprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.4f);

	textHegemonyCredit.setString(std::to_string(Scene::hegemonyCredit));

}

void SceneLobby::Exit()
{
	//pilot->SetPosition(pilotSetPosition);
	//prisoner->SetPosition(prisonerSetPosition);


	Scene::Exit();	
}

void SceneLobby::Update(float dt)
{

	Scene::Update(dt);
	PlayerChoise();
	PlayerCollied();
	animation.Update(dt);

	if (currentplayer->sprite.getGlobalBounds().intersects(doorCollisionBox.getGlobalBounds()))
	{
		//여기 스위치로


		currentplayer->isChangeScene = true;

		switch (playertype)
		{
		case Types::Pilot:
			playertype = Types::WeaponPilot;
			break;
		case Types::Prisoner:
			playertype = Types::WeaponPrsioner;
			break;
		}
	}

	if (currentplayer->isChangeScene == true && currentplayer->isChangeSceneGame == true)
	{

		Scene* scene = SCENE_MGR.GetGameScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		sceneGame->SetPlayer((int)playertype);
		SCENE_MGR.ChangeScene(SceneId::Game);
		currentplayer->isChangeScene = false;
		currentplayer->isChangeSceneGame == false;
		playerchoise = false;
		playerface = true;
		currentplayer->ChangePlayer(pilotSetPosition, false);

	}
}


void SceneLobby::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(spritehegemonyCredit);
	window.draw(textHegemonyCredit);

	if(playerface)
	window.draw(sprite);

	window.setView(worldView);
	window.draw(doorCollisionBox);

	
}

void SceneLobby::PlayerChoise()
{
	if (choiseindex == 1)
	{
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.44f);
		if(animation.GetCurrentClipId() != "PilotFace" && animation.GetCurrentClipId() != "PilotFaceIdle")
			animation.Play("PilotFace");

		if (animation.AnimationEnd())
			if (animation.GetCurrentClipId() != "PilotFaceIdle")
				animation.Play("PilotFaceIdle");
	}
	else if(choiseindex == 2)
	{
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(windowSize.x * 0.604f, windowSize.y * 0.625f);
		if (animation.GetCurrentClipId() != "PrisonerFace" && animation.GetCurrentClipId() != "PrisonerFaceIdle")
			animation.Play("PrisonerFace");

		if (animation.AnimationEnd())
			if (animation.GetCurrentClipId() != "PrisonerFaceIdle")
				animation.Play("PrisonerFaceIdle");
	}

	if (!playerchoise)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
		{
			choiseindex--;
			if (choiseindex < 1)
			{
				choiseindex = 2;
			}
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::D))
		{
			choiseindex++;
			if (choiseindex == 3)
			{
				choiseindex = 1;
			}
		}

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
		{
			switch ((Types)choiseindex)
			{
			case Types::Pilot:
				pilot->ChangePlayer(pilotSetPosition, true);
				playertype = Types::Pilot;
				currentplayer = pilot;
				break;

			case Types::Prisoner:
				prisoner->ChangePlayer(prisonerSetPosition, true);
				playertype = Types::Prisoner;
				currentplayer = prisoner;
				break;
			}
			playerchoise = true;
			playerface = false;
		}
	}
	else
	{
		switch (playertype)
		{
		case Types::Pilot:
			if (Utils::Distance(pilot->GetPosition(), prisoner->GetPosition()) <= 30.f)
			{
				playerface = true;
				sprite.setPosition(windowSize.x * 0.604f, windowSize.y * 0.625f);

				choiseindex = 2;
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
				{
					playerface = false;
					prisoner->ChangePlayer(prisonerSetPosition, true);
					pilot->ChangePlayer(pilotSetPosition, false);
					playertype = Types::Prisoner;
					currentplayer = prisoner;
				}
			}
			else
				playerface = false;
				break;

		case Types::Prisoner:
			if (Utils::Distance(prisoner->GetPosition(), pilot->GetPosition()) <= 30.f)
			{
				playerface = true;

				sprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.44f);

				choiseindex = 1;
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
				{
					playerface = false;
					pilot->ChangePlayer(pilotSetPosition, true);
					prisoner->ChangePlayer(prisonerSetPosition, false);
					playertype = Types::Pilot;
					currentplayer = pilot;
				}
			}
			else
				playerface = false;
				break;
		}
	}
}

void SceneLobby::MakeLobby()
{
	lobby = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	lobby->Load("Room/TileMapFile/LobyRoom/LobyRoom.csv");
	lobby->SetStartPos(0.f,0.f);
	lobby->SetOrigin(Origins::MC);
	lobby->sortLayer = -1;
	sf::Vector2f objpos = lobby->GetStartPos();
	sf::Vector2f tileMapSize= lobby->TileMapSize("Room/TileMapFile/LobyRoom/LobyRoom.csv");
	objpos -= tileMapSize * 0.5f;
	objpos += lobby->GetTileSize() * 0.5f;
	for (int i = 0; i < lobby->tiles.size(); ++i)
	{
		switch (static_cast<MapObjectType>(lobby->tiles[i].objectTypes))
		{

		case MapObjectType::NormalWallTop:
		case MapObjectType::NorMalWallRight:
		case MapObjectType::LightWallTop:
		case MapObjectType::LightWallLeft:
		case MapObjectType::LightWallRight:
		case MapObjectType::LibraryTop:
		case MapObjectType::LibraryLeft:
		case MapObjectType::LibraryRight:
		case MapObjectType::LibraryDown:
		case MapObjectType::StoreTop:
		case MapObjectType::StoreRight:
		case MapObjectType::StoreLeft:
		case MapObjectType::StoreTableDisplay1:
		case MapObjectType::StoreTableDisplay2:
		case MapObjectType::NormalWallLeft:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
			spr->sprite.setTextureRect({ 0,(lobby->tiles[i].objectTypes * 50),50,50 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 2;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::TreasureAlter:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 3,87,50,50 });
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 2;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::StoreTable1:
		case MapObjectType::StoreTable2:
		case MapObjectType::StoreTable3:
		case MapObjectType::StoreTable4:
		case MapObjectType::StoreTable5:
		case MapObjectType::StoreTable6:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/WallSprtie.png"));
			spr->sprite.setTextureRect({ 0,(lobby->tiles[i].objectTypes * 50),50,50 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 2;
			objects.push_back(spr);
		}
		break;
		break;
		}
		// new switch
		switch (static_cast<MapObjectType>(lobby->tiles[i].monsterAndObject))
		{
		case MapObjectType::QueenPicture:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 0,4,31,32 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::Flag1:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 85,5,13,29 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::Flag2:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 108,6,13,29 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::Flag3:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 108,6,13,29 });
			spr->SetScale(0.5f, 0.5f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::HeadObject:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 39,14,13,14 });
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::Stair:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 58,10,18,18 });
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		case MapObjectType::TreasureRoomFlag:
		{
			SpriteGo* spr = (SpriteGo*)AddGo(new SpriteGo("graphics/InteractionGameObjects.png"));
			spr->sprite.setTextureRect({ 125,0,31,38 });
			spr->SetScale(0.5f, 0.75f);
			spr->SetOrigin(Origins::MC);
			spr->SetPosition(objpos.x + lobby->tiles[i].x * lobby->GetTileSize().x, objpos.y + lobby->tiles[i].y * lobby->GetTileSize().y);
			spr->sortLayer = 3;
			objects.push_back(spr);
		}
		break;
		}

	}

}

void SceneLobby::PlayerCollied()
{
	if (!lobby->vertexArray.getBounds().contains(currentplayer->GetPosition()))
	{
		currentplayer->SetPosition(currentplayer->GetPrevPos());
	}
	for (auto& collied : objects)
	{
		if (collied->sprite.getGlobalBounds().intersects(currentplayer->sprite.getGlobalBounds()))
		{
			currentplayer->SetPosition(currentplayer->GetPrevPos());
		}
	}
}
