#include "stdafx.h"
#include "SceneLobby.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SceneGame.h"
#include "Enemy.h" //test

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

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


	pilot = (Player*)AddGo(new Player(Player::Types::Pilot));
	prisoner = (Player*)AddGo(new Player(Player::Types::Prisoner));



	playerui = (SpriteGo*)AddGo(new SpriteGo("graphics/PilotUI.png", "pilot"));
	playerui->SetOrigin(Origins::BC);
	playerui->SetActive(false);
	currentchoise.push_back(playerui);

	playerui = (SpriteGo*)AddGo(new SpriteGo("graphics/PrisonerUI.png", "prisoner"));
	playerui->SetOrigin(Origins::BC);
	playerui->SetActive(false);
	currentchoise.push_back(playerui);

	elevator = (SpriteGo*)AddGo(new SpriteGo("graphics/elevator.png", ""));
	elevator->SetPosition(200,-200);
	elevator->SetOrigin(Origins::MC);
	elevator->sortLayer = -1;
	elevator->SetScale(0.3f,0.3f);

	currentplayer = pilot;

	test = (Enemy*)AddGo(new Enemy(EnemyTypes::BulletKin)); //test
	test->SetOrigin(Origins::BC); //test
	test->SetPlayer(currentplayer); //test
	test->SetEnemy(100.f, 5.f); //test
	test->SetPosition(-200, -200); //test

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
	Scene::Enter();

	pilot->SetPosition(pilotSetPosition);
	prisoner->SetPosition(prisonerSetPosition);
	
	currentchoise[0]->SetPosition(pilot->sprite.getGlobalBounds().top, (pilot->sprite.getGlobalBounds().left + pilot->sprite.getGlobalBounds().width) * 0.5);
	currentchoise[1]->SetPosition(prisoner->sprite.getGlobalBounds().top, (prisoner->sprite.getGlobalBounds().left + prisoner->sprite.getGlobalBounds().width) * 0.5);
}

void SceneLobby::Exit()
{
	Scene::Exit();
}

void SceneLobby::Update(float dt)
{

	Scene::Update(dt);
	PlayerChoise();
	
	if(currentplayer->sprite.getGlobalBounds().intersects(elevator->sprite.getGlobalBounds()))
	{

		Scene* scene = SCENE_MGR.GetGameScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		if (playertype == Types::Pilot)
		{
			playertype = Types::WeaponPilot;
		}
		else if (playertype == Types::Prisoner)
		{
			playertype = Types::WeaponPrsioner;
		}
		sceneGame->SetPlayer((int)playertype);
		SCENE_MGR.ChangeScene(SceneId::Game);
	}

	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left)) //test
	{
		test->OnDamage(0.1f);
	}
}


void SceneLobby::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneLobby::PlayerChoise()
{
	if (!playerchoise)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
		{
			currentchoise[choiseindex]->SetActive(false);
			choiseindex--;

			if (choiseindex < 0)
			{
				choiseindex = currentchoise.size() - 1;
			}

			currentchoise[choiseindex]->SetActive(true);
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::D))
		{
			currentchoise[choiseindex]->SetActive(false);
			choiseindex++;

			if (choiseindex == currentchoise.size())
			{
				choiseindex = 0;
			}
			currentchoise[choiseindex]->SetActive(true);
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
		}
	}
	else
	{
		for (int i = 0; i < currentchoise.size(); ++i)
		{
			currentchoise[i]->SetActive(false);
		}
	}

	if (playerchoise)
	{
		switch (playertype)
		{
		case Types::Pilot:
			if (Utils::Distance(pilot->GetPosition(), prisoner->GetPosition()) <= 30.f)
			{
				currentchoise[(int)Types::Prisoner]->SetActive(true);
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
				{
					prisoner->ChangePlayer(prisonerSetPosition, true);
					pilot->ChangePlayer(pilotSetPosition, false);
					playertype = Types::Prisoner;
					currentplayer = prisoner;
				}
			}
			else
			{
				currentchoise[(int)Types::Prisoner]->SetActive(false);
			}
			break;

		case Types::Prisoner:
			if (Utils::Distance(prisoner->GetPosition(), pilot->GetPosition()) <= 30.f)
			{
				currentchoise[(int)Types::Pilot]->SetActive(true);
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
				{
					pilot->ChangePlayer(pilotSetPosition, true);
					prisoner->ChangePlayer(prisonerSetPosition, false);
					playertype = Types::Pilot;
					currentplayer = pilot;
				}
			}
			else
			{
				currentchoise[(int)Types::Pilot]->SetActive(false);
			}
			break;
		}
	}
}