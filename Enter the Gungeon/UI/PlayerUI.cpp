#include "stdafx.h"
#include "PlayerUI.h"
#include "Weapon.h"
#include "Player.h"

PlayerUI::PlayerUI(Player* player, const std::string& textureId, const std::string& n)
{
	windowsize = FRAMEWORK.GetWindowSize();

	this->player = player;
	this->player->SetPlayerUI(this);

	sortLayer = 101;
	sf::Texture* tex;


	tex = RESOURCE_MGR.GetTexture("graphics/hp_empty.png");
	playermaxhp.push_back(CreateSprite(tex, 0, 0));
	playermaxhp.push_back(CreateSprite(tex, 50, 0));
	playermaxhp.push_back(CreateSprite(tex, 100, 0));

	// Intact HP sprites
	sf::Texture* tex1 = RESOURCE_MGR.GetTexture("graphics/hp_left.png");
	sf::Texture* tex2 = RESOURCE_MGR.GetTexture("graphics/hp_right.png");
	playerhp.push_back(CreateSprite(tex1, 0, 0));
	playerhp.push_back(CreateSprite2(tex2, 0, 0));
	playerhp.push_back(CreateSprite(tex1, 50, 0));
	playerhp.push_back(CreateSprite2(tex2, 50, 0));
	playerhp.push_back(CreateSprite(tex1, 100, 0));
	playerhp.push_back(CreateSprite2(tex2, 100, 0));


	sf::Texture* tex3 = RESOURCE_MGR.GetTexture("graphics/weaponBox.png");
	weaponBox.setTexture(*tex3);
	weaponBox.setPosition(500,500);

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
	weapon.setPosition(500,500);

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
		currentweapon.Play("Relode");
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