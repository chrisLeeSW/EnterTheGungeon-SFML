#include "stdafx.h"
#include "GameMapTestScene.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "AnimationController.h"
#include "InteractionObject.h"
#include "BspNodeNew.h"
GameMapTestScene::GameMapTestScene() :Scene(SceneId::GameMapTestScene)
{
	resourceListPath = "script/GameMapTestScene.csv";
}

void GameMapTestScene::Init()
{
	tileRoom1 = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png"));
	sf::Vector2f pos = { 0,0 }; // ·£´ý ¼³Á¤
	tileRoom1->NoneFileLoad(100, 100);
	

	
	int min_width = 25;
	int min_height = 25;
	int max_depth = 3;

	root = new BSPNode({ 0, 0, 100 * 25, 100 * 25 });
	room = new Room1();
	room->Divide(root, min_width, min_height, max_depth);

	
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
	
}

void GameMapTestScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
}
void GameMapTestScene::GenerateTileMap(BSPNode* node)
{
	if (!node->left && !node->right)
	{
		int x = node->room.x / 25;
		int y = node->room.y / 25;
		int width = node->room.width / 25;
		int height = node->room.height / 25;

	}
	tileRoom1->Reset();
	if (node->left)
	{
		GenerateTileMap(node->left);
	}

	if (node->right)
	{
		GenerateTileMap(node->right);
	}
}