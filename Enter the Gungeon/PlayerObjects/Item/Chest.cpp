#include "stdafx.h"
#include "Chest.h"
#include "SceneGame.h"
#include "DropEquipItem.h"
#include "ItemMgr.h"

Chest::Chest()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/ChestIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/ChestOpen.csv"));

	animation.SetTarget(&sprite);
}

void Chest::Init()
{
	
}

void Chest::Reset()
{
	player = PLAYER_MGR.GetPlayer();
	interaction = false;
	isOpened = false;

	SpriteGo::Reset();
	animation.Play("Idle");
}

void Chest::Update(float dt)
{
	animation.Update(dt);

	if (isOpened) return;

	float distance = Utils::Distance(player->GetPosition(), position);
	if (distance <= 30.f)
	{
		interaction = true;
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::E)) // 상호작용
		{
			if (player->GetKey() <= 0) return;

			player->AddKey(-1);
			animation.Play("Open");
			isOpened = true;
			interaction = false;

			// DropItem Drop
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
			DropItem* dropitem = scene->GetPoolDropItem().Get();
			dropitem->SetType((DropItem::Types)Utils::RandomRange(0, (int)DropItem::Types::Count));
			dropitem->SetPosition(position + sf::Vector2f{ 50.f, 0.f});
			dropitem->Init();
			dropitem->Reset();
			scene->AddGo(dropitem);

			// Equip Drop
			DropEquipItem* dropequipitem = ITEM_MGR.GetDropItem();

			for (auto it : player->GetPlayerWeaponList())
			{
				Weapon::Types t = (Weapon::Types)Utils::RandomRange((int)Weapon::Types::Pad, (int)Weapon::Types::Count);
				if (it != t)
				{
					dropequipitem->SetType(t);
					break;
				}
			}

			dropequipitem->SetPosition(position + sf::Vector2f{-50.f,0.f});
			dropequipitem->Init();
			dropequipitem->Reset();

			scene->AddGo(dropequipitem);

		}
	}
	else
	{
		interaction = false;
	}
}