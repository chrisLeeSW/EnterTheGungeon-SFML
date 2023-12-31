#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "SceneTitle.h"
#include "SceneMaptool.h"
#include "SceneBulletEditor.h"
#include "SceneLobby.h"
#include "GameMapTestScene.h"
#include "TestRom.h"

void SceneMgr::Init() 
{
	if (!scenes.empty())
	{
		Release();
	}
	scenes.push_back(new SceneTitle());
	scenes.push_back(new SceneLobby());
	scenes.push_back(new SceneGame());
	scenes.push_back(new SceneMaptool());
	scenes.push_back(new SceneBulletEditor());
	scenes.push_back(new GameMapTestScene());
	scenes.push_back(new TestRom());
	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentSceneId = startSceneId;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();


}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		//scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;

}

void SceneMgr::UpdateEvent(float dt)
{
	currentScene->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	currentScene->Draw(window);
}

void SceneMgr::ChangeScene(SceneId id)
{
	currentScene->Exit();
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

Scene* SceneMgr::GetCurrScene() const
{
	return currentScene;
}

Scene* SceneMgr::GetGameScene() const
{
	return scenes[2];
}