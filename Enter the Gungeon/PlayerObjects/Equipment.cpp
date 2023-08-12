#include "stdafx.h"
#include "Equipment.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TextGo.h"

Equipment::Equipment(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
}

void Equipment::Init()
{

	windowsize = FRAMEWORK.GetWindowSize();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Equipment.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EquipmentClose.csv"));
	animation.SetTarget(&sprite);

	SetPosition(windowsize * 0.5f);
	SetScale(2,2);
	sortLayer = 101;
	//SetActive(false);
	draw = false;

}

void Equipment::Release()
{
}

void Equipment::Reset()
{
	SpriteGo::Reset();
	Insert();

}

void Equipment::Update(float dt)
{
	SetOrigin(Origins::MC);
	animation.Update(dt);

	if(bookOn)
	{
		if(animation.GetCurrentClipId() != "Book")
		animation.Play("Book");

		if (animation.AnimationEnd())
		{
			but1->SetActive(true);
		}
	}
	else
	{
		if (animation.GetCurrentClipId() != "BookClose")
		animation.Play("BookClose");

		but1->SetActive(false);
		if (animation.AnimationEnd())
		{
			draw = false;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::I))
	{
		bookOn = !bookOn;
		draw = true;
	}
}

void Equipment::Draw(sf::RenderWindow& window)
{
	if(draw)
	{
		SpriteGo::Draw(window);
	}
}

void Equipment::Insert()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	but1 = (UiButton*)sceneGame->AddGo(new UiButton("graphics/PilotWeapon.png"));
	but1->SetPosition(windowsize * 0.4f);
	but1->sortLayer = 102;
	but1->SetActive(false);
	but1->SetScale(5,5);

	weaponsUI.push_back(but1);

	mapweapons.insert({ but1,"PilotWeapon" });
	//"fonts/OpenSans-Semibold.ttf", "SaveText"
	TextGo* textbut = (TextGo*)sceneGame->AddGo(new TextGo("fonts/OpenSans-Semibold.ttf","textbut"));
	textbut->sortLayer = 103;
	textbut->text.setCharacterSize(50);
	textbut->text.setFillColor(sf::Color::Green);
	textbut->SetPosition(windowsize * 0.5f);
	auto it = mapweapons.find(but1);
	textbut->text.setString(it->second);
	textbut->SetActive(false);

	but1->OnEnter = [this, textbut]() {

		textbut->SetActive(true);
		std::cout << "장비인써트!";
	};

	but1->OnExit = [this, textbut]() {
		textbut->SetActive(false);
		std::cout << "장비인써트!";
	};
	
	std::cout << "흑흑 제발 나와라 : " << it->second << std::endl;

}