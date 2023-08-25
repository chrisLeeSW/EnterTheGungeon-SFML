#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "GameObject.h"
#include "PlayerMgr.h"


Weapon::Weapon(const std::string& textureId, const std::string& n) : Item(textureId, n)
{
}

void Weapon::Init()
{
	
}

void Weapon::Release()
{
}

void Weapon::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void Weapon::Update(float dt)
{
	if (PLAYER_MGR.IsPause())
		return;

	SetPosition(player->PlayerHandPos());

	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);

}

void Weapon::Draw(sf::RenderWindow& window)
{
	if (!player->isRolling())
		SpriteGo::Draw(window);
	window.draw(gunend);
}


void Weapon::SetPlayer(Player* player)
{

}

void Weapon::SetType(Types t)
{

}

void Weapon::SetGunFlipx(bool flip)
{
	sf::Vector2f scale = sprite.getScale();
	this->flipX = flip;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

	scale = shooteffect.getScale();
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	shooteffect.setScale(scale);
}

void Weapon::SwapWeapon()
{
	
}


void Weapon::SetEnemy(Enemy* enemy)
{
	this->enemy = enemy;

	gunPos = { enemy->sprite.getLocalBounds().width * 0.5f, -enemy->sprite.getLocalBounds().height * 0.3f };
}

