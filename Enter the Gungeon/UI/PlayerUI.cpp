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

	currentMagazine.setScale(0.3f, 0.3f);
	remainingAmmo.setScale(0.3f, 0.3f);
	remainingAmmoMax.setScale(0.3f, 0.3f);
	currentmoney.setScale(0.3f, 0.3f);
	currentkey.setScale(0.3f, 0.3f);

	sf::Font* font = RESOURCE_MGR.GetFont("fonts/PF.ttf");

	currentmoney.setFont(*font);
	currentmoney.setFillColor(sf::Color::White);
	currentmoney.setCharacterSize(45);
	currentmoney.setPosition(45,45);
	currentmoney.setString(std::to_string(player->GetMoney()));


	currentkey.setFont(*font);
	currentkey.setFillColor(sf::Color::White);
	currentkey.setCharacterSize(45);
	currentkey.setPosition(20, 45);
	currentkey.setString(std::to_string(player->GetKey()));

	currentMagazine.setFont(*font);
	currentMagazine.setFillColor(sf::Color::White);
	currentMagazine.setCharacterSize(30);
	currentMagazine.setPosition(weaponBox.getGlobalBounds().left + weaponBox.getGlobalBounds().width, weaponBox.getGlobalBounds().top + weaponBox.getGlobalBounds().height / 2);
	currentMagazine.setString(std::to_string(player->GetCurrenWeapon()->GetCurrentBulleCount()));

	remainingAmmo.setFont(*font);
	remainingAmmo.setFillColor(sf::Color::White);
	remainingAmmo.setCharacterSize(27);
	remainingAmmo.setPosition(weaponBox.getPosition().x, weaponBox.getGlobalBounds().top);
	remainingAmmo.setString(std::to_string(player->GetCurrenWeapon()->GetRemainingAmmo()));
	
	remainingAmmoMax.setFont(*font);
	remainingAmmoMax.setFillColor(sf::Color::White);
	remainingAmmoMax.setCharacterSize(27);
	remainingAmmoMax.setPosition(remainingAmmo.getGlobalBounds().left + remainingAmmo.getGlobalBounds().width, weaponBox.getGlobalBounds().top + 1);
	remainingAmmoMax.setString("/" + std::to_string(player->GetCurrenWeapon()->GetCurrentRamainingAmmo()));

	Utils::SetOrigin(remainingAmmo, Origins::BL);
	Utils::SetOrigin(remainingAmmoMax, Origins::BL);
	Utils::SetOrigin(currentMagazine, Origins::ML);



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
		currentweapon.Play("Reload");
		reload.setPosition(windowsize.x * 0.5f, windowsize.y * 0.4);

		float reloadProgressRatio = playerweapon->GetCurrentReloadTime() / playerweapon->GetReloadTime();
		float indicatorPosX = reload.getGlobalBounds().left + reloadProgressRatio * reload.getLocalBounds().width * 0.95;

		reloadBar.setPosition(indicatorPosX, windowsize.y * 0.4f);

		break;
	}
}


void PlayerUI::Draw(sf::RenderWindow& window)
{
	for (auto& it : playermaxhp)
	{
		window.draw(it);
	}

	for (auto& it : playerhp)
	{
		window.draw(it);
	}

	window.draw(weaponBox);
	window.draw(weapon);
	window.draw(activeBox);
	window.draw(active);
	window.draw(money);
	window.draw(key);
	window.draw(currentmoney);
	window.draw(currentkey);
	window.draw(currentMagazine);
	window.draw(remainingAmmo);
	window.draw(remainingAmmoMax);



	for (auto& it : blankbullets)
	{
		window.draw(it);
	}


	if (playerweapon->GetWeaponState() == Weapon::State::Reload)
	{
		window.draw(reload);
		window.draw(reloadBar);
	}
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

void PlayerUI::RenewHp(int hp, int maxHp)
{
	playermaxhp.clear();
	sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/hp_empty.png");
	for (int i = 0; i < maxHp / 2; i++)
	{
		playermaxhp.push_back(CreateSprite(tex, 20 * i, 0));

	}

	playerhp.clear();
	sf::Texture* tex1 = RESOURCE_MGR.GetTexture("graphics/hp_left.png");
	sf::Texture* tex2 = RESOURCE_MGR.GetTexture("graphics/hp_right.png");
	for (int i = 0; i < hp; i++)
	{
		int p = i / 2;
		(i % 2 == 0) ? playerhp.push_back(CreateSprite(tex1, 20 * p, 0)) : playerhp.push_back(CreateSprite2(tex2, 20 * p, 0));
	}
}

void PlayerUI::RenewMoney()
{
	currentmoney.setString(std::to_string(player->GetMoney()));
}

void PlayerUI::RenewKey()
{
	currentkey.setString(std::to_string(player->GetKey()));
}

void PlayerUI::ShootWeapon()
{
	currentMagazine.setString(std::to_string(player->GetCurrenWeapon()->GetCurrentBulleCount()));
	remainingAmmo.setString(std::to_string(player->GetCurrenWeapon()->GetCurrentRamainingAmmo()));
}

void PlayerUI::SwapWeaponText()
{
	currentMagazine.setString(std::to_string(player->GetCurrenWeapon()->GetCurrentBulleCount()));
	remainingAmmo.setString(std::to_string(player->GetCurrenWeapon()->GetCurrentRamainingAmmo()));
	remainingAmmoMax.setString("/" + std::to_string(player->GetCurrenWeapon()->GetRemainingAmmo()));
}
