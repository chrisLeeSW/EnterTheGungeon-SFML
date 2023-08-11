#include "stdafx.h"
#include "WeaponMgr.h"
#include "WeaponTable.h"
#include "DataTableMgr.h"
#include "Weapon.h"
#include "Scene.h"
#include "SceneGame.h"
#include "PilotWeapon.h"
#include "PrisonerWeapon.h"
#include "Ak47.h"


void WeaponMgr::Init()
{
	if (!weapons.empty())
	{
		Release();
	}


	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr](Bullet* bullet) {
		bullet->pool = ptr;
	};
	poolBullets.Init();

}


void WeaponMgr::Enter(Weapon::Types type)
{
	switch (type)
	{
	case Weapon::Types::PilotWeapon :
		weapons.push_back(new PilotWeapon());
		currentWeapon = weapons[0];
		currentWeapon->Init();
		std::cout << "�����Ŵ��� ���� : Ÿ�� ���Ϸ� ����";
		break;

	case Weapon::Types::PrisonerWeapon : 
		weapons.push_back(new PrisonerWeapon());
		currentWeapon = weapons[0];
		currentWeapon->Init();
		std::cout << "�����Ŵ��� ���� : Ÿ�� ������� ����";
		break;
	}

	withWeapon = true;
}

����ġ(Ŀ��Ʈ����->���� Ÿ��)

ĳ�̽� 1
����(����Ÿ��);


void WeaponMgr::Release()
{
	if (weapons.empty())
	{
		return;
	}

	for (auto weapon : weapons)
	{
		//scene->Release();
		delete weapon;
	}
	weapons.clear();

	currentWeaponType = Weapon::Types::None;
}

void WeaponMgr::SwapWeapon(int swap)
{
	if (swap >= 0 && swap < weapons.size())
	{
		swap--;
		currentWeapon = weapons[swap];
	}
	else
	{
		std::cout << "Invalid weapon index!" << std::endl;
	}
}

void WeaponMgr::Update(float dt)
{
	currentWeapon->Update(dt);
}

void WeaponMgr::Draw(sf::RenderWindow& window)
{
	currentWeapon->Draw(window);
}


void WeaponMgr::SetPlayer(Player* player)
{
	this->player = player;
}

Player* WeaponMgr::GetPlayer()
{
	return player;
}

bool WeaponMgr::GetWithWeapon()
{
	return withWeapon;
}

void WeaponMgr::SetHandOrigin(sf::Vector2f handori)
{
	orix = handori.x;
	oriy = handori.y;
}

sf::Vector2f WeaponMgr::GetHandOrigin()
{
	return sf::Vector2f{ orix,oriy };
}

void WeaponMgr::SetWeaPonFlipx(bool flip)
{
	currentWeapon->SetGunFlipx(flip);
}

Weapon::Types WeaponMgr::GetCurrentWeapon() const
{
	return currentWeaponType;
}

const void WeaponMgr::GetWeapon(Weapon::Types id)
{
	auto find = mapweapons.find(id);
	if (find == mapweapons.end())
	{
		std::cout << "�� ��ã����" << std::endl;
	}

	switch (id)
	{
	case ::Weapon::Types::Ak47:
		weapons.push_back(new Ak47());
		weapons.back()->Init();
		break;
	}
}