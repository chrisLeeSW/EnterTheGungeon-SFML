#include "stdafx.h"
#include "EnemyBullet.h"
#include "SceneMgr.h"

EnemyBullet::EnemyBullet(std::string textureId, std::string name)
	:SpriteGo(textureId, name)
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EnemyBulletBlink.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EnemyBulletIdle.csv"));

	animation.SetTarget(&sprite);
}

EnemyBullet::~EnemyBullet()
{
	Release();
}

void EnemyBullet::Init()
{
	SetOrigin(Origins::MC);
	
}

void EnemyBullet::Reset()
{
	(isBlink) ? animation.Play("Blink") : animation.Play("Idle");
	SpriteGo::Reset();
}

void EnemyBullet::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);

	range -= speed * dt;
	SetPosition(position + direction * speed * dt);

	if (range <= 0.f)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}

	if (player == nullptr) return;
	if (sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()) && player->IsAlive())
	{
		if (player->isRolling())
			return;
		player->OnPlayerHit();
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
	}


	//Player-BlnakBullet 
	if (player->IsBlankBullet())
	{
		if (Utils::Distance(player->GetPosition(), GetPosition()) <= 150.f)
		{
			Scene* scene = SCENE_MGR.GetCurrScene();
			scene->RemoveGo(this);
		}
	}
}

void EnemyBullet::SetPlayer(Player* player)
{
	this->player = player;
}

void EnemyBullet::SetBullet(bool isBlink)
{
	this->isBlink = isBlink;
}

void EnemyBullet::Shoot(sf::Vector2f dir, float speed, float range, int damage)
{
	this->direction = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
}

bool EnemyBullet::IsBlink() const
{
	return isBlink;
}
