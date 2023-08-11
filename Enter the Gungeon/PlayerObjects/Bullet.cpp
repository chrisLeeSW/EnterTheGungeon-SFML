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
	SetOrigin(Origins::TR);
	animation.Update(dt);

	position += 0.f * direction * (float)speed * dt;
	SetPosition(position);

	animation.Play("Shoot");
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Bullet::SetType(int types)
{

	const BulletInfo* info = DATATABLE_MGR.Get<BulletTable>(DataTable::Ids::Bullet)->Get((Bullet::Types)types);

	bulletType = info->bulletType;
	speed = info->speed;
	damage = info->damage;
	range = info->range;
	knockback = info->knockback;

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

PilotGun::PilotGun(Types type)
{
}

void PilotGun::Update(float dt)
{

}
PrisonerGun::PrisonerGun()
{

}

void PrisonerGun::Update(float dt)
{

}

Ak47::Ak47()
{
}

void Ak47::Update(float dt)
{
}
