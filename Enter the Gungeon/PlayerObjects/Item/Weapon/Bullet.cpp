#include "stdafx.h"
#include "Bullet.h"
#include "BulletTable.h"
#include "DataTableMgr.h"
#include "Enemy.h"
#include "PlayerMgr.h"

Bullet::Bullet(const std::string& textureId, const std::string& n) : SpriteGo(textureId, n)
{
}

void Bullet::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/PilotBullet.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/BasicBullet.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/PrisonerBullet.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/Pad.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("bulletcsv/PadFire.csv"));


	animation.SetTarget(&sprite);
	sortLayer = -1;
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
	if (PLAYER_MGR.IsPause())
		return;

	SetOrigin(Origins::MC);
	animation.Update(dt);

	position += direction * speed * dt;
	SetPosition(position);

	range -= speed * dt;

	if (range <= 0.f)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
		pool->Return(this);
		return;
	}

	if(animation.GetCurrentClipId()!= bulletid)
	animation.Play(bulletid);

	if (INPUT_MGR.GetKey(sf::Keyboard::Num6))
	{
		direction.x *= 1.01f;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::Num7))
	{
		direction.y *= 1.01f;
	}

	HitEnemy();

}



void Bullet::HitEnemy()
{
	if (!enemylist.empty())
	{
		for (Enemy* enemy : enemylist)
		{
			if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
			{
				std::cout << "맞음";
				enemy->OnDamage(damage, direction, knockback);
				SCENE_MGR.GetCurrScene()->RemoveGo(this);
				pool->Return(this);
				break;
			}
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Bullet::SetBullet(Types types, sf::Vector2f pos, sf::Vector2f dir, float santan)
{
	const BulletInfo* info = DATATABLE_MGR.Get<BulletTable>(DataTable::Ids::Bullet)->Get(types);

	bulletType = info->bulletType;
	bulletid = info->bulletid;
	speed = info->speed;
	damage = info->damage;
	range = info->range;
	knockback = info->knockback;

	position = pos;

	//sprite.setRotation(DEGREES_90 + Utils::Angle(dir));
	sprite.setRotation(Utils::Angle(dir));
	float spreadAngle = Utils::RandomRange(-santan, santan);

	// 원래 방향 벡터에 집탄 영향을 적용하여 새로운 방향 계산
	sf::Vector2f spreadDir = Utils::RotateVector(dir, spreadAngle);


	// 정규화된 방향 벡터를 사용하여 일정한 속도로 이동하도록 설정
	direction = Utils::Normalize(spreadDir);

}


void Bullet::Fire(sf::Vector2f pos, sf::Vector2f dir)
{
	position = pos;
	sprite.setRotation(Utils::Angle(dir));
	SetPosition(position);
	direction = dir;
}