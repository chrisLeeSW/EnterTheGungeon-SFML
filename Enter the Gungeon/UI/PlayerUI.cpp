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

	// Intact HP sprites
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
	weaponBox.setPosition(windowsize * 0.9f);

	tex = RESOURCE_MGR.GetTexture("graphics/ui_blank.png");

	blankbullets.push_back(CreateSprite(tex,0,30));
	blankbullets.push_back(CreateSprite(tex,15,30));

	weapon.setPosition(weaponBox.getGlobalBounds().left + weaponBox.getGlobalBounds().width * 0.5f, weaponBox.getGlobalBounds().top + weaponBox.getGlobalBounds().height * 0.5f);
	
	tex = RESOURCE_MGR.GetTexture("graphics/Reload.png");
	reload.setTexture(*tex);
	tex = RESOURCE_MGR.GetTexture("graphics/ReloadBar.png");
	reloadBar.setTexture(*tex);

	Utils::SetOrigin(reload,Origins::MC);

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

	weapon.setOrigin(weapon.getLocalBounds().width / 2.f, weapon.getLocalBounds().height / 2.f);



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
		break;
	}
}


void PlayerUI::Draw(sf::RenderWindow& window)
{
	for(auto& it : playermaxhp)
	window.draw(it);

	for (auto& it : playerhp)
		window.draw(it);

	window.draw(weaponBox);

	window.draw(weapon);

	for (auto& it : blankbullets)
		window.draw(it);


	if(playerweapon->GetWeaponState() == Weapon::State::Reload)
	window.draw(reload);

	window.draw(reloadBar);

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

void PlayerUI::UseBlankBullet()
{
	blankbullets.pop_back();
}