#include "stdafx.h"
#include "PilotWeapon.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"


PilotWeapon::PilotWeapon(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PilotWeaponShoot.csv"));

	gun.SetTarget(&sprite);

	SetType(Types::PilotWeapon);

	SpriteGo::Reset();

	gun.Play("Idle");

	sf::Vector2f GunSize = sf::Vector2f{ sprite.getLocalBounds().width, sprite.getLocalBounds().height };
	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);


}

void PilotWeapon::Init()
{
	player = PLAYER_MGR.GetPlayer();
	std::cout << sprite.getOrigin().x << std::endl;
}

void PilotWeapon::Release()
{
}

void PilotWeapon::Reset()
{
	//SpriteGo::Reset();
	std::cout << "리셋" << std::endl;
	player = PLAYER_MGR.GetPlayer();

}

void PilotWeapon::Update(float dt)
{
	
	gun.Update(dt);
	SetPosition(player->GetPosition() + sf::Vector2f(WeaponXpos,-7.f));
	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	sprite.setRotation(Utils::Angle(look));
	if (flipX) sprite.setRotation(FLIP_ANGLE_X +  Utils::Angle(look));

	SetGunFlipx(player->GetFilpX());


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F1))
	{
		WEAPON_MGR.TestAddWeapon();
	}

	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
	{
		Shoot();
	}
	std::cout << "지금 무기는 파일럿 무기에용" << std::endl;
}

void PilotWeapon::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PilotWeapon::SetGunFlipx(bool flipX)
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


void PilotWeapon::SetType(Types t)
{
	const WeaponInfo* info = DATATABLE_MGR.Get<WeaponTable>(DataTable::Ids::Weapon)->Get(t);

	weaponType = (Types)info->weaponType;
	attackrate = info->attackrate;
	bulletcount = info->bulletcount;
	bulletmax = info->bulletmax;
	reload = info->reload;
	santan = info->santan;
}

void PilotWeapon::Shoot()
{
	bullet = poolBullets.Get();
	bullet->SetBullet((int)Bullet::Types::PilotBullet, GetPosition(), Look());

	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	sceneGame->AddGo(bullet);
}