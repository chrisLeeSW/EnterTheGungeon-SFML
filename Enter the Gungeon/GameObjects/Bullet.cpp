#include "stdafx.h"
#include "Bullet.h"

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
	
}

void Bullet::Reset()
{
	SetOrigin(Origins::MC);
	(isBlink) ? animation.Play("Blink") : animation.Play("Idle");
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);

	SetPosition(position + direction * speed * dt);
}

void Bullet::SetBullet(bool isBlink)
{
	this->isBlink = isBlink;
}

void Bullet::Shoot(sf::Vector2f dir, float speed, int damage)
{
	this->direction = dir;
	this->speed = speed;
	this->damage = damage;
}