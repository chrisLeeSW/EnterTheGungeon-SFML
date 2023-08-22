#include "stdafx.h"
#include "SceneLobby.h"
#include "UiButton.h"
#include "Player.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SceneGame.h"

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

	pilot->SetOrigin(Origins::BC);
	prisoner->SetOrigin(Origins::BC);

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PilotFace.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PilotFaceIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PrisonerFace.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/Choise/PrisonerFaceIdle.csv"));

	animation.SetTarget(&sprite);


	elevator = (SpriteGo*)AddGo(new SpriteGo("graphics/elevator.png", ""));
	elevator->SetPosition(200,-200);
	elevator->SetOrigin(Origins::MC);
	elevator->sortLayer = -1;
	elevator->SetScale(0.3f,0.3f);

	currentplayer = pilot;

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
	
	sprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.4f);


}

void SceneLobby::Exit()
{
	Scene::Exit();
}

void SceneLobby::Update(float dt)
{

	Scene::Update(dt);
	PlayerChoise();
	
	animation.Update(dt);

	if (currentplayer->sprite.getGlobalBounds().intersects(elevator->sprite.getGlobalBounds()))
	{
		//여기 스위치로
		Scene* scene = SCENE_MGR.GetGameScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

		switch (playertype)
		{
		case Types::Pilot:
			playertype = Types::WeaponPilot;
			break;
		case Types::Prisoner :
			playertype = Types::WeaponPrsioner;
			break;
		}
		sceneGame->SetPlayer((int)playertype);
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}


void SceneLobby::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	if(playerface)
	window.draw(sprite);
}

void SceneLobby::PlayerChoise()
{
	if (choiseindex == 0)
	{
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(windowSize.x * 0.5f, windowSize.y * 0.44f);
		if(animation.GetCurrentClipId() != "PilotFace" && animation.GetCurrentClipId() != "PilotFaceIdle")
			animation.Play("PilotFace");

		if (animation.AnimationEnd())
			if (animation.GetCurrentClipId() != "PilotFaceIdle")
				animation.Play("PilotFaceIdle");
	}
	else
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
			if (choiseindex < 0)
			{
				choiseindex = 1;
			}
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::D))
		{
			choiseindex++;
			if (choiseindex == 2)
			{
				choiseindex = 0;
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

	}

	if (playerchoise)
	{
		switch (playertype)
		{
		case Types::Pilot:
			if (Utils::Distance(pilot->GetPosition(), prisoner->GetPosition()) <= 30.f)
			{
				playerface = true;
				sprite.setPosition(windowSize.x * 0.604f, windowSize.y * 0.625f);

				choiseindex = 1;
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

				choiseindex = 0;
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