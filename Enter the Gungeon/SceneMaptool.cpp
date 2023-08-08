#include "stdafx.h"
#include "SceneMaptool.h"
#include "SpriteGo.h"
#include "TileMap.h"
#include "UiButton.h"
#include	"TextGo.h"
SceneMaptool::SceneMaptool() : Scene(SceneId::MapTool), tileMap(nullptr), view(1.0f), makeWallWidthCount(5), makeWallHeightCount(3)
{
	resourceListPath = "script/SceneMapToolResourceList.csv";
}

void SceneMaptool::Init()
{
	Release();

	SettingUiSprite();
	SettingUiText();
	

	for (auto go : gameObjects)
	{
		go->Init();
	}
	/*tileMap = (TileMap*)AddGo(new TileMap("graphics/WallSprtie.png","TileMap"));

	testPlayerCollied = (SpriteGo*)AddGo(new SpriteGo("graphics/testPlayer.png", "test"));
	testPlayerCollied->SetOrigin(Origins::MC);
	testPlayerCollied->SetPosition(0.f,-250.f);
	for (auto go : gameObjects)
	{
		go->Init();
	
	//tileMap->Load("MapFile/map1.csv");
	//tileMap->SetOrigin(Origins::BC); // BC로 충돌검사 확인
	//shape.setSize(sf::Vector2f{ (-(tileMap->vertexArray.getBounds().left) + tileMap->vertexArray.getBounds().width), (-(tileMap->vertexArray.getBounds().top) + tileMap->vertexArray.getBounds().height) });
	*/

}

void SceneMaptool::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneMaptool::Enter()
{

	Scene::Enter();

	makeWallWidthCount=5;
	makeWallHeightCount=3;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0,0 });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	

	view = 1.0f;
}

void SceneMaptool::SettingUiSprite()
{
	saveUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "SaveUi"));
	saveUi->sprite.setTextureRect({ 10,27,50,20 });
	saveUi->SetScale(2.f, 2.f);
	saveUi->SetPosition(windowSize.x * 0.05f, windowSize.y * 0.5f);
	saveUi->SetOrigin(Origins::MC);
	saveUi->OnEnter = [this]()
	{
		saveUi->sprite.setTextureRect({ 11,55,50,20 });
		saveUi->SetScale(2.f, 2.f);
	};
	saveUi->OnExit = [this]()
	{
		saveUi->sprite.setTextureRect({ 10,27,50,20 });
		saveUi->SetScale(2.f, 2.f);
	};
	saveUi->OnClick = [this]()
	{
		std::cout << "Clock" << std::endl;
	};
	saveUi->sortLayer = 100;

	loadUi = (UiButton*)AddGo(new UiButton("graphics/MapMakerMenu.png", "LoadUi"));
	loadUi->sprite.setTextureRect({ 10,27,50,20 });
	loadUi->SetScale(2.f, 2.f);
	loadUi->SetPosition(windowSize.x * 0.11f, windowSize.y * 0.5f);
	loadUi->SetOrigin(Origins::MC);
	loadUi->OnEnter = [this]()
	{
		loadUi->sprite.setTextureRect({ 11,55,50,20 });
		loadUi->SetScale(2.f, 2.f);
	};
	loadUi->OnExit = [this]()
	{
		loadUi->sprite.setTextureRect({ 10,27,50,20 });
		loadUi->SetScale(2.f, 2.f);
	};
	loadUi->OnClick = [this]()
	{
		std::cout << "Clock" << std::endl;
	};
	loadUi->sortLayer = 100;
}
void SceneMaptool::Exit()
{
	Scene::Exit();
}

void SceneMaptool::SettingUiText()
{
	saveUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "SaveText"));
	saveUiText->text.setCharacterSize(20);
	saveUiText->SetOrigin(Origins::BC);
	saveUiText->text.setString("Save");
	saveUiText->sortLayer = 100;
	saveUiText->text.getCharacterSize();
	saveUiText->SetPosition(saveUi->GetPosition() - sf::Vector2f{ 0.f, saveUiText->text.getCharacterSize() * 0.25f });

	loadUiText = (TextGo*)AddGo(new TextGo("fonts/OpenSans-Semibold.ttf", "SaveText"));
	loadUiText->text.setCharacterSize(20);
	loadUiText->SetOrigin(Origins::BC);
	loadUiText->text.setString("Load");
	loadUiText->sortLayer = 100;
	loadUiText->text.getCharacterSize();
	loadUiText->SetPosition(loadUi->GetPosition() - sf::Vector2f{ 0.f, saveUiText->text.getCharacterSize() * 0.25f });
}

void SceneMaptool::Update(float dt)
{
	Scene::Update(dt);

	



	/*playerPos = testPlayerCollied->GetPosition();
	playerDir.x=INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	playerDir.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
	playerPos +=  playerDir * 100.f * dt;
	testPlayerCollied->SetPosition(playerPos);

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Middle))
	{
		sf::Vector2f worldPose = ScreenToWorldPos(INPUT_MGR.GetMousePos());
		float moveSpeed = 0.01f;
		worldView.move(-worldPose.x * moveSpeed,-worldPose.y * moveSpeed);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageUp))
	{
		view += 0.05f;
		tileMap->SetVewScale(view);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::PageDown))
	{
		view -= 0.05f;
		tileMap->SetVewScale(view);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::End))
	{
		view = 1.0f;
		tileMap->SetVewScale(view);
	}
	////csv 파일로 해서 그리는거 확인 완료 */
	
}

void SceneMaptool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
