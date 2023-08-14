#include "stdafx.h"
#include "Bullet.h"
#include "BulletTable.h"
#include "DataTableMgr.h"
#include "SpriteGo.h"

Bullet::Bullet(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
}

void Bullet::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/PilotBullet.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/BasicBullet.csv"));

	animation.SetTarget(&sprite);

}

void Bullet::Release()
{
	SpriteGo::Release();
}

void Bullet::Reset()
{
	SpriteGo::Reset();
}

void Bullet::Update(float dt)
{
	SetOrigin(Origins::MC);
	animation.Update(dt);

	position += direction * speed * dt;
	SetPosition(position);

	animation.Play(anistirng);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Bullet::SetBullet(int types, sf::Vector2f pos, sf::Vector2f dir)
{
	const BulletInfo* info = DATATABLE_MGR.Get<BulletTable>(DataTable::Ids::Bullet)->Get((Bullet::Types)types);

	bulletType = info->bulletType;
	speed = info->speed;
	damage = info->damage;
	range = info->range;
	knockback = info->knockback;

	position = pos;
	sprite.setRotation(90 + Utils::Angle(dir));
	SetPosition(position);
	direction = dir;

	anistirng = std::to_string(types);
}

void Bullet::Shoot(Types type)
{
	switch (type)
	{
	case Types::PilotBullet :
		break;
	case Types::PrisonerBullet:
		break;
	case Types::Ak47:
		break;
	}
}

void Bullet::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	position = pos;
	sprite.setRotation(Utils::Angle(dir));
	SetPosition(position);
	direction = dir;
}
