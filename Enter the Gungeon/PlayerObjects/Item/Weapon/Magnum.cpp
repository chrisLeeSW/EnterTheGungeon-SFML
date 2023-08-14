#include "stdafx.h"
#include "Magnum.h"
#include "DataTableMgr.h"
#include "WeaponTable.h"
#include "Player.h"
#include "WeaponMgr.h"
#include "Scene.h"
#include "SceneGame.h"

Magnum::Magnum(const std::string& textureId, const std::string& n) : Weapon(textureId, n)
{
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumIdle.csv"));
	gun.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/MagnumShoot.csv"));

	gun.SetTarget(&sprite);

	SetType(Types::Magnum);
	SpriteGo::Reset();

	gun.Play("Idle");

	sf::Vector2f GunSize = sf::Vector2f{ sprite.getLocalBounds().width, sprite.getLocalBounds().height };
	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);

	SetScale(0.5f,0.5f);
}

void Magnum::Init()
{
	player = PLAYER_MGR.GetPlayer();
	//gun.Play("Idle");
}

void Magnum::Release()
{
}

void Magnum::Reset()
{
	player = PLAYER_MGR.GetPlayer();
}

void Magnum::Update(float dt)
{
	gun.Update(dt);
	SetPosition(player->GetPosition() + sf::Vector2f(WeaponXpos, -7.f));
	SetOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().height);
	mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	look = Utils::Normalize(mousePos - playerScreenPos);
	sprite.setRotation(Utils::Angle(look));
	if (flipX) sprite.setRotation(FLIP_ANGLE_X + Utils::Angle(look));

	SetGunFlipx(player->GetFilpX());


	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left))
	{
		gun.Play("Shoot");
		Shoot();
	}
}

void Magnum::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Magnum::SetGunFlipx(bool flipX)
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

void Magnum::Shoot()
{
	bullet = poolBullets.Get();
	bullet->SetBullet((int)Bullet::Types::PilotBullet, GetPosition(), Look());

	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	sceneGame->AddGo(bullet);
}