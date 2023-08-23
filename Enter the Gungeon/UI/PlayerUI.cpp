#include "stdafx.h"
#include "PlayerUI.h"
#include "Weapon.h"
#include "Player.h"

PlayerUI::PlayerUI(Player* player, const std::string& textureId, const std::string& n)
{
	windowsize = FRAMEWORK.GetWindowSize();

	windowsize *= 0.3f;
	this->player = player;
	this->player->SetPlayerUI(this);

	sortLayer = 101;
	sf::Texture* tex;


	tex = RESOURCE_MGR.GetTexture("graphics/hp_empty.png");
	playermaxhp.push_back(CreateSprite(tex, 0, 0));
	playermaxhp.push_back(CreateSprite(tex, 20, 0));
	playermaxhp.push_back(CreateSprite(tex, 40, 0));


	sf::Texture* tex1 = RESOURCE_MGR.GetTexture("graphics/hp_left.png");
	sf::Texture* tex2 = RESOURCE_MGR.GetTexture("graphics/hp_right.png");
	playerhp.push_back(CreateSprite(tex1, 0, 0));
	playerhp.push_back(CreateSprite2(tex2, 0, 0));
	playerhp.push_back(CreateSprite(tex1, 20, 0));
	playerhp.push_back(CreateSprite2(tex2, 20, 0));
	playerhp.push_back(CreateSprite(tex1, 40, 0));
	playerhp.push_back(CreateSprite2(tex2, 40, 0));


	sf::Texture* tex3 = RESOURCE_MGR.GetTexture("graphics/weaponBox.png");
	weaponBox.setTexture(*tex3);
	activeBox.setTexture(*tex3);
	weaponBox.setPosition(windowsize * 0.9f);
	activeBox.setPosition(windowsize.x * 0.05f, windowsize.y * 0.9f);


	tex = RESOURCE_MGR.GetTexture("graphics/ui_blank.png");

	blankbullets.push_back(CreateSprite(tex,0,20));
	blankbullets.push_back(CreateSprite(tex,15,20));

	weapon.setPosition(weaponBox.getGlobalBounds().left + weaponBox.getGlobalBounds().width * 0.5f, weaponBox.getGlobalBounds().top + weaponBox.getGlobalBounds().height * 0.5f);
	
	tex = RESOURCE_MGR.GetTexture("graphics/Reload.png");
	reload.setTexture(*tex);
	tex = RESOURCE_MGR.GetTexture("graphics/ReloadBar.png");
	reloadBar.setTexture(*tex);

	tex = RESOURCE_MGR.GetTexture("graphics/ui_coin.png");
	money.setTexture(*tex);
	money.setPosition(30,45);

	tex = RESOURCE_MGR.GetTexture("graphics/ui_key.png");
	key.setTexture(*tex);
	key.setPosition(0,45);


	Utils::SetOrigin(reload,Origins::MC);
	Utils::SetOrigin(reloadBar, Origins::MC);
	Utils::SetOrigin(weaponBox, Origins::TL);
	Utils::SetOrigin(activeBox, Origins::TL);

	sf::Font* font = RESOURCE_MGR.GetFont("fonts/AurulentSansMono-Regular.otf");

	currentmoney.setFont(*font);
	currentmoney.setFillColor(sf::Color::White);
	currentmoney.setCharacterSize(15);
	currentmoney.setPosition(45,45);
	currentmoney.setString(std::to_string(player->GetMoney()));


	currentkey.setFont(*font);
	currentkey.setFillColor(sf::Color::White);
	currentkey.setCharacterSize(15);
	currentkey.setPosition(20, 45);
	currentkey.setString(std::to_string(player->GetMoney()));
}

void PlayerUI::Init()
{
}

void PlayerUI::Release()
{
}

void PlayerUI::Reset()
{
}

void PlayerUI::Update(float dt)
{
	currentweapon.Update(dt);


	//sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->UiPosPosToScreen(player->GetPosition());


	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(player->GetPosition());

	//weapon.setOrigin(weapon.getLocalBounds().width / 2.f, weapon.getLocalBounds().height / 2.f);
	Utils::SetOrigin(weapon, Origins::MC);
	Utils::SetOrigin(active, Origins::MC);



	switch(playerweapon->GetWeaponState())
	{
	case Weapon::State::Idle :
		currentweapon.Play("Idle");
		break;

	case Weapon::State::Shoot :
		if(INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		currentweapon.Play("Shoot");
		break;

	case Weapon::State::Reload :
		if(INPUT_MGR.GetKeyDown(sf::Keyboard::R))
		currentweapon.Play("Relode");
		reload.setPosition(windowsize.x * 0.5f, windowsize.y * 0.4);

		float reloadProgressRatio = playerweapon->GetCurrentReloadTime() / playerweapon->GetReloadTime();
		float indicatorPosX = reload.getGlobalBounds().left + reloadProgressRatio * reload.getLocalBounds().width * 0.95;

		reloadBar.setPosition(indicatorPosX, windowsize.y * 0.4f);

		break;
	}

	std::cout << active.getPosition().x << std::endl;
}


void PlayerUI::Draw(sf::RenderWindow& window)
{
	for(auto& it : playermaxhp)
	window.draw(it);

	for (auto& it : playerhp)
		window.draw(it);

	window.draw(weaponBox);
	window.draw(weapon);
	window.draw(activeBox);
	window.draw(active);
	window.draw(money);
	window.draw(key);
	window.draw(currentmoney);
	window.draw(currentkey);


	for (auto& it : blankbullets)
		window.draw(it);


	if(playerweapon->GetWeaponState() == Weapon::State::Reload)
	{
		window.draw(reload);
		window.draw(reloadBar);
	}


}

void PlayerUI::IsHited()
{
	playerhp.pop_back();
}



sf::Sprite PlayerUI::CreateSprite(sf::Texture* texture, float x, float y)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setOrigin(sprite.getLocalBounds().left, -sprite.getLocalBounds().height);
	sprite.setPosition(x, y);
	return sprite;
}

sf::Sprite PlayerUI::CreateSprite2(sf::Texture* texture, float x, float y)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setOrigin(-sprite.getLocalBounds().width * 0.25f, -sprite.getLocalBounds().height);
	sprite.setPosition(x, y);
	return sprite;
}


void PlayerUI::CurrentWeapon(Weapon* weapon)
{
	playerweapon = dynamic_cast<Weapon*>(weapon);
	currentweapon = *playerweapon->GetWeaponAnimation();
	currentweapon.SetTarget(&this->weapon);
	currentweapon.Play("Idle");
}

void PlayerUI::CurrentActive(Active* active)
{
	currentActive = active;
	switch (active->GetItemType())
	{
	case Item::Types::PrisonerActive:
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/PrisonerBottle.png");
		this->active.setTexture(*tex);
		this->active.setPosition(activeBox.getGlobalBounds().left + activeBox.getGlobalBounds().width * 0.5f, activeBox.getGlobalBounds().top + activeBox.getGlobalBounds().height * 0.5f);
		break;
	}

	default:
		break;
	}
}

void PlayerUI::UseBlankBullet()
{
	blankbullets.pop_back();
}

void PlayerUI::AddBlankBullet()
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ui_blank.png");
	blankbullets.push_back(CreateSprite(tex, blankbullets.size() * 15, 20));
}

void PlayerUI::AddHp()
{

	if (player->GetHp() % 2 == 1)
	{
		sf::Texture* tex1 = RESOURCE_MGR.GetTexture("graphics/hp_left.png");
		playerhp.push_back(CreateSprite(tex1, playerhp.size() * 10, 0));
	}
	else
	{
		sf::Texture* tex2 = RESOURCE_MGR.GetTexture("graphics/hp_right.png");
		playerhp.push_back(CreateSprite2(tex2, playerhp.back().getPosition().x, 0));
	}
}

void PlayerUI::AdjustMoney()
{
	currentmoney.setString(std::to_string(player->GetHp()));
}

void PlayerUI::AdjustKey()
{
	currentkey.setString(std::to_string(player->GetKey()));
}
