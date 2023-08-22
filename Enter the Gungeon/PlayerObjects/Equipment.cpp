#include "stdafx.h"
#include "Equipment.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "Passive.h"
#include "Weapon.h"
#include "Active.h"
#include "UiButton.h"

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
	SetScale(2, 2);
	sortLayer = 103;
	draw = false;

	//sf::Vector2f bookleft(sprite.getPosition().x, sprite.getPosition().y);

	test1.setFillColor(sf::Color::Green);
	test1.setSize({ 10,10 });
	test2.setFillColor(sf::Color::Red);
	test2.setSize({ 10,10 });
	test3.setFillColor(sf::Color::Blue);
	test3.setSize({ 10,10 });

	weaponline = { windowsize.x * 0.4f, sprite.getPosition().y * 0.8f };
	passiveline = { windowsize.x * 0.4f, sprite.getPosition().y };
	activeline = {windowsize.x * 0.4f, sprite.getPosition().y * 1.2f};


	test1.setPosition(weaponline);
	test2.setPosition(passiveline);
	test3.setPosition(activeline);
	std::cout << "Ã¥ ¿ÞÂÊ : " << sprite.getGlobalBounds().left << std::endl;

	black.setFillColor(sf::Color::Black);
	black.setSize(windowsize);
	black.setOrigin(0,0);


	









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
			isSprite = true;
		}
	}
	else
	{
		if (animation.GetCurrentClipId() != "BookClose")
		animation.Play("BookClose");
			isSprite = false;

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
		window.draw(black);
		window.draw(test1);
		window.draw(test2);
		window.draw(test3);
		SpriteGo::Draw(window);
		window.draw(pilotweapon->sprite);
	}
}

void Equipment::Insert()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	pilotweapon = new UiButton("graphics/pilotweaponbutton.png");
	
	pilotweapon->SetPosition(weaponline);
	pilotweapon->sortLayer = 106;
	pilotweapon->SetActive(false);

	//prisonerweapon
	//pad
	//prisonerPassive
	//pilotPassive
	//bulletTime
	//prisonerActive

	//sf::Sprite pilotweaponsprite;
	//sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/pilotweaponsprite.png");
	//pilotweaponsprite.setTexture(*tex);


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
	};

	but1->OnExit = [this, textbut]() {
		textbut->SetActive(false);
	};
	

}

void Equipment::GetItem(Weapon::Types type)
{
	switch (type)
	{
	case Weapon::Types::PilotWeapon:

		break;
	case Weapon::Types::PrisonerWeapon:

		break;
	case Weapon::Types::Pad :

		break;

	}
}

void Equipment::GetItem(Passive::Types type)
{
	switch (type)
	{
	case Passive::Types::PilotPassive :

		break;
	case Passive::Types::PrisonerPassive :

		break;

	}
}

void Equipment::GetItem(Active::Types type)
{
	switch (type)
	{
	case Active::Types::BulletTime :
		
		break;
	case Active::Types::PrisonerActive :

		break;
	case Active::Types::PilotActive :

		break;
	}
}
