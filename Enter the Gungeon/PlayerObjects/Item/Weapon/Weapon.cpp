#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "SceneGame.h"
#include "Scene.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "GameObject.h"



Weapon::Weapon(const std::string& textureId, const std::string& n) : Item(textureId, n)
{
}

void Weapon::Init()
{
	scene = SCENE_MGR.GetGameScene();
	sceneGame = dynamic_cast<SceneGame*>(scene);

	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr](Bullet* bullet) {
		bullet->pool = ptr;
	};
	poolBullets.Init();
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
	bullet = poolBullets.Get();
	bullet->SetBullet(type, pos, dir);

	if (sceneGame != nullptr)
	{
		bullet->SetEnemy(WEAPON_MGR.GetEnemyList());
		sceneGame->AddGo(bullet);
	}
}

void Weapon::SetType(Types t)
{

}

void Weapon::SwapWeapon()
{
	for (const auto& pair : keyToIndexMap)
	{
		if (INPUT_MGR.GetKeyDown(pair.first))
		{
			int weaponIndex = pair.second;
			//WEAPON_MGR.SwapWeapon(weaponIndex);
			std::cout << "스왑웨폰, 현재 웨폰 인덱스 : " << weaponIndex << std::endl;
			break;
		}
	}
}

sf::Vector2f Weapon::Look()
{
	return look;
}

void Weapon::SetEnemy(Enemy* enemy)
{
}

