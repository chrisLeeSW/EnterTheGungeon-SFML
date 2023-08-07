#include "stdafx.h"
#include "SceneBulletEditor.h"
#include "Bullet.h"

SceneBulletEditor::SceneBulletEditor() : Scene(SceneId::BulletEditor)
{
	resourceListPath = "script/SceneBulletEditorResourceList.csv";
}

void SceneBulletEditor::Init()
{
	Release();

	Bullet* test1 = (Bullet*)AddGo(new Bullet(BulletType::EnemyBullet));
	test1->SetScale(3.0f, 3.0f);
	test1->Shoot({ 1.0f, 0.0f }, 10.0f);
	test1->SetBullet(false);

	Bullet* test2 = (Bullet*)AddGo(new Bullet(BulletType::EnemyBullet));
	test2->SetScale(3.0f, 3.0f);
	test2->Shoot({ 0.0f, 1.0f }, 10.0f);
	test2->SetBullet(true);

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneBulletEditor::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneBulletEditor::Enter()
{
	Scene::Enter();
}

void SceneBulletEditor::Exit()
{
	Scene::Exit();
}

void SceneBulletEditor::Update(float dt)
{
	Scene::Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
}

void SceneBulletEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
