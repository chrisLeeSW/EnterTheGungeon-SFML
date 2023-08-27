#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "DataTableMgr.h"
#include "EnemyTable.h"
#include "StringTable.h"

SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	resourceListPath = "script/SceneTitleResourceList.csv";
}

void SceneTitle::Init() 
{
	Release();

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	SpriteGo* bg = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png"));
	bg->SetOrigin(Origins::MC);
	bg->sortLayer = -1;

	SpriteGo* logo = (SpriteGo*)AddGo(new SpriteGo("graphics/titletext.png"));
	logo->SetOrigin(Origins::MC);
	logo->SetPosition(0, -200.f);
	logo->sortLayer = 0;
	sf::Texture texture;
	texture.loadFromFile("graphics/background.png");

	sf::Vector2f originalTextureSize(texture.getSize().x, texture.getSize().y);



	sf::Vector2f desiredSize(windowSize); // 원하는 크기
	bg->SetScale(desiredSize.x / originalTextureSize.x, desiredSize.y / originalTextureSize.y);

	
	StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String);

	std::wstring name;


	sf::Font* font = RESOURCE_MGR.GetFont("fonts/PF.ttf");

	if (font != nullptr)
	{
		play.setFont(*font);
		play.setCharacterSize(20);
		language.setFont(*font);
		language.setCharacterSize(20);
		close.setFont(*font);
		close.setCharacterSize(20);
	}

	name = table->GetW("PLAY");
	play.setString(name);
	name = table->GetW("LANGUAGE");
	language.setString(name);
	name = table->GetW("CLOSE");
	close.setString(name);

	transparentColor = sf::Color(255, 255, 255, 158);
	originalColor = sf::Color(255, 255, 255, 255);
	play.setPosition(50, windowSize.y * 0.75f);
	language.setPosition(50, windowSize.y * 0.8f);
	close.setPosition(50, windowSize.y * 0.85f);

	play.setFillColor(originalColor);
	language.setFillColor(transparentColor);
	close.setFillColor(transparentColor);

	for (auto go : gameObjects)	
	{
		go->Init();
	}

}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
	
}

void SceneTitle::Enter()
{
	Scene::Enter();

	if (ValidFilePath("SaveFile.csv"))
	{
		LoadCSV("SaveFile.csv");
	}
	else
	{
		SaveCSV("SaveFile.csv");
	}

}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	//animation.Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::W))
	{
		selectedTextIndex--;
		
		if (selectedTextIndex < 0)
		{
			selectedTextIndex = 2;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::S))
	{
		selectedTextIndex++;

		if (selectedTextIndex >= 3)
		{
			selectedTextIndex = 0;
		}
	}

	switch (selectedTextIndex)
	{
	case 0:
		play.setFillColor(originalColor);
		language.setFillColor(transparentColor);
		close.setFillColor(transparentColor);
		break;

	case 1:
		play.setFillColor(transparentColor);
		language.setFillColor(originalColor);
		close.setFillColor(transparentColor);
		break;

	case 2:
		play.setFillColor(transparentColor);
		language.setFillColor(transparentColor);
		close.setFillColor(originalColor);
		break;
	}
	

	//스위치로 변환하기
	if (selectedTextIndex == 0 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		SCENE_MGR.ChangeScene(SceneId::Lobby);
	}
	if (selectedTextIndex == 1 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		if (Variables::CurrentLang == Languages::ENG)
		{
			Variables::CurrentLang = Languages::KOR;
		}
		else
		{
			Variables::CurrentLang = Languages::ENG;
		}

		StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String); // StringTable 사용
		std::wstring name = table->GetW("PLAY");
		play.setString(name);
		name = table->GetW("LANGUAGE");
		language.setString(name);
		name = table->GetW("CLOSE");
		close.setString(name);
		
	}
	if (selectedTextIndex == 2 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		//나가기
		window.close();
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneId::Lobby);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.ChangeScene(SceneId::BulletEditor);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
	{
		SCENE_MGR.ChangeScene(SceneId::MapTool);
	}
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}*/
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
	{
		SCENE_MGR.ChangeScene(SceneId::GameMapTestScene);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
	{
		SCENE_MGR.ChangeScene(SceneId::TestRoom);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(play);
	window.draw(language);
	window.draw(close);
}

bool SceneTitle::ValidFilePath(const std::string& filepath)
{
	std::ifstream fileStream(filepath);
	return fileStream.is_open();
}

void SceneTitle::LoadCSV(const std::string& filepath)
{
	rapidcsv::Document doc(filepath, rapidcsv::LabelParams(-1, -1));

	hegemonyCredit = doc.GetCell<int>(0, 1); // Type 지정

	Variables::CurrentLang = (Languages)doc.GetCell<int>(1, 1);

	StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String); // StringTable 사용
	std::wstring name = table->GetW("PLAY");
	play.setString(name);
	name = table->GetW("LANGUAGE");
	language.setString(name);
	name = table->GetW("CLOSE");
	close.setString(name);

}

void SceneTitle::SaveCSV(const std::string& filepath)
{
	std::ofstream outputFile(filepath);

	hegemonyCredit = 0;

	OverwriteCSV(filepath);
}

void SceneTitle::OverwriteCSV(const std::string& filepath)
{
	rapidcsv::Document doc("SaveFile.csv", rapidcsv::LabelParams(-1, -1));
	doc.Clear();
	doc.SetCell<std::string>(0, 0, "HegemonyCredit");
	doc.SetCell<std::string>(1, 0, "Language");



	doc.SetCell<int>(0, 1, hegemonyCredit); // Type 지정
	doc.SetCell<int> (1, 1, (int)Variables::CurrentLang);


	doc.Save();
}