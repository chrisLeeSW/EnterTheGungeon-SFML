#include "stdafx.h"
#include "Bullet.h"
#include "SceneMgr.h"

Bullet::Bullet(BulletType type, std::string textureId, std::string name)
	:SpriteGo(textureId, name), type(type)
{
	switch (type)
	{
	case BulletType::EnemyBullet:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EnemyBulletBlink.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EnemyBulletIdle.csv"));
		break;
	}
	animation.SetTarget(&sprite);
}

Bullet::~Bullet()
{
	Release();
}

void Bullet::Init()
{
	SetOrigin(Origins::MC);
	
}

void Bullet::Reset()
{
	(isBlink) ? animation.Play("Blink") : animation.Play("Idle");
	SpriteGo::Reset();
}

void Bullet::Update(float dt)
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
}

void Bullet::SetBullet(bool isBlink)
{
	this->isBlink = isBlink;
}

void Bullet::Shoot(sf::Vector2f dir, float speed, float range, int damage)
{
	this->direction = dir;
	this->speed = speed;
	this->range = range;
	this->damage = damage;
}

bool Bullet::IsBlink() const
{
	return isBlink;
}
