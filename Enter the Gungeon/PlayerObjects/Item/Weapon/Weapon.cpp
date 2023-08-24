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

	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);

}

void Weapon::Draw(sf::RenderWindow& window)
{

}


void Weapon::SetPlayer(Player* player)
{

}

void Weapon::Shoot(Bullet::Types type, sf::Vector2f pos, sf::Vector2f dir)
{

}

void Weapon::SetType(Types t)
{

}

void Weapon::SwapWeapon()
{
	
}

sf::Vector2f Weapon::Look()
{
	return look;
}

void Weapon::SetEnemy(Enemy* enemy)
{
}

