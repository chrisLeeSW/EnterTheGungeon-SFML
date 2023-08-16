#include "stdafx.h"
#include "PrisonerWeapon.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"


PrisonerWeapon::PrisonerWeapon(const std::string& textureId, const std::string& n)
{
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerWeaponIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerWeaponShoot.csv"));

	gun.SetTarget(&sprite);

	SetPlayer();
	SetType(Types::PrisonerWeapon);

	SpriteGo::Reset();

	gun.Play("Idle");

	sf::Vector2f GunSize = sf::Vector2f{ sprite.getLocalBounds().width, sprite.getLocalBounds().height };
	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);


	std::cout << sprite.getOrigin().x << std::endl;
}

void PrisonerWeapon::Init()
{

}

void PrisonerWeapon::Release()
{
}

void PrisonerWeapon::Reset()
{
	SpriteGo::Reset();
}

void PrisonerWeapon::Update(float dt)
{
	Weapon::SwapWeapon();

	gun.Update(dt);
	SetPosition(player->GetPosition() + sf::Vector2f(WeaponXpos, -7.f));

	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	sprite.setRotation(Utils::Angle(look));
	if (flipX) sprite.setRotation(FLIP_ANGLE_X + Utils::Angle(look));

	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		//WEAPON_MGR.Shoot();
	}
}

void PrisonerWeapon::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PrisonerWeapon::SetGunFlipx(bool flipX)
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

void PrisonerWeapon::SetPlayer()
{
	this->player = WEAPON_MGR.GetPlayer();
}

void PrisonerWeapon::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}
