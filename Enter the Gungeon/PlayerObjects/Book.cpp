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


	weaponline = { windowsize.x * 0.45f, sprite.getPosition().y * 0.9f };
	passiveline = { windowsize.x * 0.45f, sprite.getPosition().y };
	activeline = {windowsize.x * 0.45f, sprite.getPosition().y * 1.1f};


	

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
			it->Update(dt);
		for (auto it : activebuttons)
			it->Update(dt);
		for (auto it : passivebuttons)
			it->Update(dt);
		
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
	}
}

void Book::GetItem(Item::Types t, Item::WAP w)
{

	switch (w)
	{
	case Item::WAP::Active :
	{
		ItemButton* it = DATATABLE_MGR.Get<ButtonTable>(DataTable::Ids::Button)->Get(t);
		it->Init();
		it->SetBook(this);
		activebuttons.push_back(it);
		if (activebuttons.size() == 1)
		{
			it->SetSpritePosition(200, 170);
		}
		else
		{
			it->SetSpritePosition(activebuttons[activebuttons.size() - 2]->GetSpritePosition().x + 20.f, activebuttons[activebuttons.size() - 2]->GetSpritePosition().y);
			std::cout << activebuttons[activebuttons.size() - 1]->GetSpritePosition().x;
			for (int i = 0; i <= activebuttons.size() - 1; i++)
			{
				activebuttons[i]->SetSpritePosition(20.f);
			}
		}
		break;
	}

	case Item::WAP::Passive :
	{
		ItemButton* it = DATATABLE_MGR.Get<ButtonTable>(DataTable::Ids::Button)->Get(t);
		it->Init();
		it->SetBook(this);
		passivebuttons.push_back(it);
		if (passivebuttons.size() == 1)
		{
			it->SetSpritePosition(200, 230);
		}
		else
		{
			it->SetSpritePosition(passivebuttons[passivebuttons.size() - 2]->GetSpritePosition().x + 20.f, passivebuttons[passivebuttons.size() - 2]->GetSpritePosition().y);
			std::cout << passivebuttons[passivebuttons.size() - 1]->GetSpritePosition().x;
			for (int i = 0; i <= passivebuttons.size() - 1; i++)
			{
				passivebuttons[i]->SetSpritePosition(20.f);
			}
		}
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

