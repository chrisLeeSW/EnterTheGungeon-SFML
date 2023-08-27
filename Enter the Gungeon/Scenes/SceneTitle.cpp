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

	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Title.csv"));
	//animation.SetTarget(&sprite);
	//sprite.setPosition(windowSize * 0.5f);

	//Utils::SetOrigin(sprite, Origins::MC);

	sf::Texture texture;
	texture.loadFromFile("graphics/background.png");

	//animation.Play("Title");
	sf::Vector2f originalTextureSize(texture.getSize().x, texture.getSize().y);


	//sf::Vector2f originalTextureSize(bg->sprite.getTexture().getSize().x, bg->sprite.getTexture().getSize().y);

	// 원하는 크기로 스케일 조절

	sf::Vector2f desiredSize(windowSize); // 원하는 크기
	bg->SetScale(desiredSize.x / originalTextureSize.x, desiredSize.y / originalTextureSize.y);

	sf::Font* font = RESOURCE_MGR.GetFont("fonts/PF.ttf");
	if (font != nullptr)
	{
		play.setFont(*font);
		play.setCharacterSize(20);
		maptool.setFont(*font);
		maptool.setCharacterSize(20);
		bulletEditor.setFont(*font);
		bulletEditor.setCharacterSize(20);
		language.setFont(*font);
		language.setCharacterSize(20);
		close.setFont(*font);
		close.setCharacterSize(20);
	}

	StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String); // StringTable 사용
	std::wstring name;
	name = table->GetW("PLAY");
	play.setString(name);
	name = table->GetW("MAPTOOL");
	maptool.setString(name);
	name = table->GetW("BULLET_EDITOR");
	bulletEditor.setString(name);
	name = table->GetW("LANGUAGE");
	language.setString(name);
	name = table->GetW("CLOSE");
	close.setString(name);

	transparentColor = sf::Color(255, 255, 255, 158);
	originalColor = sf::Color(255, 255, 255, 255);
	play.setPosition(50, windowSize.y * 0.65f);
	maptool.setPosition(50, windowSize.y * 0.7f);
	bulletEditor.setPosition(50, windowSize.y * 0.75f);
	language.setPosition(50, windowSize.y * 0.8f);
	close.setPosition(50, windowSize.y * 0.85f);

	play.setFillColor(originalColor);
	maptool.setFillColor(transparentColor);
	bulletEditor.setFillColor(transparentColor);
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
			selectedTextIndex = 4;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::S))
	{
		selectedTextIndex++;

		if (selectedTextIndex >= 5)
		{
			selectedTextIndex = 0;
		}
	}

	switch (selectedTextIndex)
	{
	case 0:
		play.setFillColor(originalColor);
		maptool.setFillColor(transparentColor);
		bulletEditor.setFillColor(transparentColor);
		language.setFillColor(transparentColor);
		close.setFillColor(transparentColor);
		break;

	case 1:
		play.setFillColor(transparentColor);
		maptool.setFillColor(originalColor);
		bulletEditor.setFillColor(transparentColor);
		language.setFillColor(transparentColor);
		close.setFillColor(transparentColor);
		break;

	case 2:
		play.setFillColor(transparentColor);
		maptool.setFillColor(transparentColor);
		bulletEditor.setFillColor(originalColor);
		language.setFillColor(transparentColor);
		close.setFillColor(transparentColor);
		break;

	case 3:
		play.setFillColor(transparentColor);
		maptool.setFillColor(transparentColor);
		bulletEditor.setFillColor(transparentColor);
		language.setFillColor(originalColor);
		close.setFillColor(transparentColor);
		break;

	case 4:
		play.setFillColor(transparentColor);
		maptool.setFillColor(transparentColor);
		bulletEditor.setFillColor(transparentColor);
		language.setFillColor(transparentColor);
		close.setFillColor(originalColor);
		break;
	}

	if (selectedTextIndex == 0 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		SCENE_MGR.ChangeScene(SceneId::Lobby);
	}
	if (selectedTextIndex == 1 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		SCENE_MGR.ChangeScene(SceneId::MapTool);
	}
	if (selectedTextIndex == 2 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		SCENE_MGR.ChangeScene(SceneId::BulletEditor);
	}
	if (selectedTextIndex == 3 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
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
		name = table->GetW("MAPTOOL");
		maptool.setString(name);
		name = table->GetW("BULLET_EDITOR");
		bulletEditor.setString(name);
		name = table->GetW("LANGUAGE");
		language.setString(name);
		name = table->GetW("CLOSE");
		close.setString(name);
		
	}
	if (selectedTextIndex == 4 && INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		//나가기
		window.close();
	}

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

	//window.draw(sprite);
	window.draw(play);
	window.draw(maptool);
	window.draw(bulletEditor);
	window.draw(language);
	window.draw(close);
}

