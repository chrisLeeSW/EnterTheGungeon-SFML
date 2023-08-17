#include "stdafx.h"
#include "Ak47.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"

#define FLIP_ANGLE_X 180

Ak47::Ak47(const std::string& textureId, const std::string& n)
{
}

void Ak47::Init()
{
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponShoot.csv"));

	gun.SetTarget(&sprite);

	SetType(Types::PilotWeapon);

	SpriteGo::Reset();

	gun.Play("Idle");

	sf::Vector2f GunSize = sf::Vector2f{ sprite.getLocalBounds().width, sprite.getLocalBounds().height };
	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);


	std::cout << sprite.getOrigin().x << std::endl;
}

void Ak47::Release()
{
}

void Ak47::Reset()
{
	SpriteGo::Reset();
	std::cout << "¸®¼Â" << std::endl;
}

void Ak47::Update(float dt)
{
	gun.Update(dt);
	SetPosition(player->GetPosition() + sf::Vector2f(WeaponXpos, -7.f));

	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	sprite.setRotation(Utils::Angle(look));
	if (flipX) sprite.setRotation(FLIP_ANGLE_X + Utils::Angle(look));
}

void Ak47::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Ak47::SetGunFlipx(bool flipX)
{
	if (!flipX)
	{
		WeaponXpos = abs(WeaponXpos);
	}
	else
	{
		WeaponXpos = -abs(WeaponXpos);
	}

	sf::Vector2f scale = sprite.getScale();
	this->flipX = flipX;
	scale.x = !this->flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}


void Ak47::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}
