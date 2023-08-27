#include "stdafx.h"
#include "DropEquipItem.h"

DropEquipItem::DropEquipItem(const std::string& textureId, const std::string& n)
{
}

void DropEquipItem::Init()
{
	SetOrigin(Origins::MC);
}

void DropEquipItem::Reset()
{
	switch (type)
	{
	case Weapon::Types::Pad:
		textureId = "graphics/padbutton.png";
		break;
	case Weapon::Types::ShotGun:
		textureId = "graphics/PlayerShotGunButton.png";
		break;
	case Weapon::Types::PrisonerWeapon:
		textureId = "graphics/prisonerweaponbutton.png";
		break;
	case Weapon::Types::PilotWeapon:
		textureId = "graphics/pilotweaponbutton.png";
		break;
		
	default:

		break;
	}

	SpriteGo::Reset();
	player = PLAYER_MGR.GetPlayer();

	OnBump = [this]()
	{
		player->GetItem(type);
	};
}

void DropEquipItem::Update(float dt)
{
	if (sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
	{
		OnBump();
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}
}

void DropEquipItem::SetType(Weapon::Types type)
{
	this->type = type;
	//player = PLAYER_MGR.GetPlayer();
}

