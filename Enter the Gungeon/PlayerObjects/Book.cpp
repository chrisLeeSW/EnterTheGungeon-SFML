#include "stdafx.h"
#include "Book.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "Passive.h"
#include "Weapon.h"
#include "Active.h"
#include "ItemButton.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "DataTableMgr.h"
#include "ButtonTable.h"


Book::Book(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
}

void Book::Init()
{
	PLAYER_MGR.SetBook(this);

	windowsize = FRAMEWORK.GetWindowSize();

	windowsize *= 0.3f;

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Equipment.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EquipmentClose.csv"));
	animation.SetTarget(&sprite);

	SetPosition(windowsize * 0.5f);
	SetOrigin(Origins::MC);
	sortLayer = 103;
	draw = false;

	//sf::Vector2f bookleft(sprite.getPosition().x, sprite.getPosition().y);

	test1.setFillColor(sf::Color::Green);
	test1.setSize({ 10,10 });
	test2.setFillColor(sf::Color::Red);
	test2.setSize({ 10,10 });
	test3.setFillColor(sf::Color::Blue);
	test3.setSize({ 10,10 });

	weaponline = { windowsize.x * 0.45f, sprite.getPosition().y * 0.9f };
	passiveline = { windowsize.x * 0.45f, sprite.getPosition().y };
	activeline = {windowsize.x * 0.45f, sprite.getPosition().y * 1.1f};


	test1.setPosition(weaponline);
	test2.setPosition(passiveline);
	test3.setPosition(activeline);

	

	black.setFillColor(sf::Color::Black);
	black.setSize(windowsize);
	black.setOrigin(0,0);

}

void Book::Release()
{
}

void Book::Reset()
{
	SpriteGo::Reset();
	player = PLAYER_MGR.GetPlayer();
	Insert();

}

void Book::Update(float dt)
{
	SetOrigin(Origins::MC);
	animation.Update(dt);

	if(bookOn)
	{
		if(animation.GetCurrentClipId() != "Book")
		animation.Play("Book");

		if (animation.AnimationEnd())
		{
			isBookOpen = true;
		}
	}
	else
	{
		if (animation.GetCurrentClipId() != "BookClose")
		animation.Play("BookClose");
		isBookOpen = false;

		if (animation.AnimationEnd())
		{
			draw = false;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::I))
	{
		bookOn = !bookOn;
		draw = true;
		PLAYER_MGR.SetPause(bookOn);
	}

	if(isBookOpen)
	{
		for (auto it : weaponbuttons)
		{
			it->Update(dt);
		}
	}
}

void Book::Draw(sf::RenderWindow& window)
{
	if(draw)
	{
		window.draw(black);
		SpriteGo::Draw(window);

	}

	if(isBookOpen)
	{
		for (auto& it : weaponbuttons)
			window.draw(it->sprite);

		for (auto& it : passivebuttons)
			window.draw(it->sprite);

		for (auto& it : activebuttons)
			window.draw(it->sprite);

		if(currentClickButton!=nullptr)
		{
			currentClickButton->Draw(window);
		}

		window.draw(test1);
		window.draw(test2);
		window.draw(test3);
	}
}

void Book::Insert()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);


	TextGo* textbut = (TextGo*)sceneGame->AddGo(new TextGo("fonts/OpenSans-Semibold.ttf","textbut"));
	textbut->sortLayer = 103;
	textbut->text.setCharacterSize(50);
	textbut->text.setFillColor(sf::Color::Green);
	textbut->SetPosition(windowsize * 0.5f);

}

void Book::GetItem(Item::Types t, Item::WAP w)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);

	switch (w)
	{
	case Item::WAP::Active :
	{
		ItemButton* it = DATATABLE_MGR.Get<ButtonTable>(DataTable::Ids::Button)->Get(t);
		//sceneGame->AddGo(it);
		activebuttons.push_back(it);
		break;
	}

	case Item::WAP::Passive :
	{
		ItemButton* it = DATATABLE_MGR.Get<ButtonTable>(DataTable::Ids::Button)->Get(t);
		//sceneGame->AddGo(it);
		passivebuttons.push_back(it);
		break;
	}

	case Item::WAP::Weapon :
	{
		ItemButton* it = DATATABLE_MGR.Get<ButtonTable>(DataTable::Ids::Button)->Get(t);
		//sceneGame->AddGo(it);
		//it->Reset();
		it->Init();
		it->SetBook(this);
		weaponbuttons.push_back(it);
		if (weaponbuttons.size() == 1)
		{
			it->SetSpritePosition(200,110);
		}
		else
		{
			it->SetSpritePosition(weaponbuttons[weaponbuttons.size() - 2]->GetSpritePosition().x + 20.f, weaponbuttons[weaponbuttons.size() - 2]->GetSpritePosition().y);
			std::cout << weaponbuttons[weaponbuttons.size() - 1]->GetSpritePosition().x;
			for(int i = 0; i <= weaponbuttons.size() - 1; i++)
			{
				weaponbuttons[i]->SetSpritePosition(20.f);
			}
		}
		break;
	}
	}

}

