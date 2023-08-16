#include "stdafx.h"
#include "TestRom.h"

TestRom::TestRom() :Scene(SceneId::TestRoom)
{
}

void TestRom::Init()
{
	for (auto go : gameObjects)
	{
		go->Init();
	}

}

void TestRom::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	if (room)
	{
		delete room;
		room = nullptr;
	}
}

void TestRom::Enter()
{

	Scene::Enter();
	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


}

void TestRom::Exit()
{
	Scene::Exit();
}

void TestRom::Update(float dt)
{
	Scene::Update(dt);
	MoveWorldView();
}

void TestRom::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
}

void TestRom::MoveWorldView()
{
	if (INPUT_MGR.GetKey(sf::Keyboard::Right))
	{
		worldView.move(3.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Left))
	{
		worldView.move(-3.f, 0.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Up))
	{
		worldView.move(0.0f, -3.f);
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Down))
	{
		worldView.move(0.0f, 3.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		worldView.zoom(0.9f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		worldView.zoom(1.1f);
	}
}
