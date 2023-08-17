#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "EnemyTable.h"
#include "DataTableMgr.h"
#include "SceneGame.h"

//HaeJun
#include "ShotGun.h"
#include "ItemMgr.h"
#include "Weapon.h"
#include "Magnum.h"

Enemy::Enemy(EnemyName type, const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n), type(type)
{
	way.push_back({ 0.f, -1.f }); // Up
	way.push_back(Utils::Normalize({ 1.f, -1.f })); // LeftUp
	way.push_back({ 1.f, 0.f }); // Left
	way.push_back(Utils::Normalize({ 1.f, 1.f })); // LeftDown
	way.push_back({ 0.f, 1.f }); // Down
}

Enemy::~Enemy()
{
	Release();
}

void Enemy::Init()
{
	std::string name;
	switch (type)
	{
	case EnemyName::BulletKin:
		name = "BulletKin/BulletKin";
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			OneShot(dir, speed);
		};
		break;
	case EnemyName::KeyBulletKin:
		name = "KeyBulletKin/KeyBulletKin";
		// Runaway 함수
		break;
	case EnemyName::ShotgunKinRed:
		name = "ShotgunKinRed/ShotgunKinRed";
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			FiveWayShot(dir, speed);
		};
		IfDie = [this](sf::Vector2f dir)
		{
			SixWayDie(dir, speed, 20); // table 사용
		};
		break;
	case EnemyName::ShotgunKinBlue:
		name = "ShotgunKinBlue/ShotgunKinBlue";
		IfShoot = [this](sf::Vector2f dir, float speed)
		{
			FiveWayShot(dir, speed);
		};
		IfDie = [this](sf::Vector2f dir)
		{
			SixWayDie(dir, speed, 33); // table 사용
		};
		break;
	default:
		std::cerr << "ERROR: Not Exist EnemyName (Enemy Init())" << std::endl;
		break;
	}
	SetEnemy();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "IdleDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "MoveDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "AttackDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "HitDown.csv"));

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieLeftUp.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieLeft.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieLeftDown.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/" + name + "DieDown.csv"));

	animation.SetTarget(&sprite);

}

void Enemy::Reset()
{
	SpriteGo::Reset();
	if (isHanded)
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/BulletKin.png");
		if (tex != nullptr)
		{
			hand.setTexture(*tex);
			hand.setTextureRect({ 121, 16, 4, 4 });
		}
	}

	animation.Play("IdleDown");
	SetFlipX(false);
	SetOrigin(origin);
	hand.setOrigin(sprite.getLocalBounds().width * 0.8f, sprite.getLocalBounds().height * 0.25f);

	hp = maxHp;
	isAlive = true;
	attackTimer = attackInterval;


	Scene* scene = SCENE_MGR.GetCurrScene();
	switch (type)
	{
	case EnemyName::BulletKin:
		magnum = (Magnum*)scene->AddGo(new Magnum());
		magnum->SetEnemy(this);
		break;
	case EnemyName::ShotgunKinRed:
		shotgun = (ShotGun*)scene->AddGo(new ShotGun());
		shotgun->SetEnemy(this);
		break;
	case EnemyName::ShotgunKinBlue:
		shotgun = (ShotGun*)scene->AddGo(new ShotGun());
		shotgun->SetEnemy(this);
		break;
	default:
		break;
	}
}

void Enemy::Update(float dt)
{
	animation.Update(dt);

	if (!isAlive || player == nullptr) return;

	direction = Utils::Normalize(player->GetPosition() - position);
	SetFlipX(direction.x > 0.f);
	if (direction != sf::Vector2f{ 0.f, 0.f }) prevDir = direction;
	float distance = Utils::Distance(player->GetPosition(), position);
	sf::Vector2f min = WhereWay(direction);

	if (attackRange > distance)
	{
		direction = { 0.f, 0.f };

		attackTimer += dt;
		if (attackTimer >= attackInterval)
		{
			attackTimer = 0.f;
			if (IfShoot != nullptr)
			{
				IfShoot(prevDir, speed); //총알 속도 지정 필요
			}

			// Animation
			if (min == way[0] && animation.GetCurrentClipId() != "AttackUp")
			{
				animation.Play("AttackUp");
				animation.PlayQueue("IdleUp");
			}
			else if (min == way[1] && animation.GetCurrentClipId() != "AttackLeftUp")
			{
				animation.Play("AttackLeftUp");
				animation.PlayQueue("IdleLeftUp");
			}
			else if (min == way[2] && animation.GetCurrentClipId() != "AttackLeft")
			{
				animation.Play("AttackLeft");
				animation.PlayQueue("IdleLeft");
			}
			else if (min == way[3] && animation.GetCurrentClipId() != "AttackLeftDown")
			{
				animation.Play("AttackLeftDown");
				animation.PlayQueue("IdleLeftDown");
			}
			else if (min == way[4] && animation.GetCurrentClipId() != "AttackDown")
			{
				animation.Play("AttackDown");
				animation.PlayQueue("IdleDown");
			}
		}
	}

	if (player->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) // Collider 충돌로 변경 요구
	{
		if (IfBump != nullptr)
		{
			IfBump();
		}
		else
		{
			OnBump();
		}
	}
	

	// Animation
	if (direction.x != 0.f || direction.y != 0.f)
	{
		if (animation.GetCurrentClipId() != "MoveUp" && animation.AnimationEnd() &&
			min == way[0])
		{
			animation.Play("MoveUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftUp" && animation.AnimationEnd() &&
			min == way[1])
		{
			animation.Play("MoveLeftUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeft" && animation.AnimationEnd() &&
			min == way[2])
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftDown" && animation.AnimationEnd() &&
			min == way[3])
		{
			animation.Play("MoveLeftDown");
		}
		else if (animation.GetCurrentClipId() != "MoveDown" && animation.AnimationEnd() &&
			min == way[4])
		{
			animation.Play("MoveDown");
		}
		SetPosition(position + direction * speed * dt); // 피격 시 안움직이는 기능 구현 필요

	}
	else
	{
		if (animation.GetCurrentClipId() == "MoveUp")
		{
			animation.Play("IdleUp");
		}
		else if (animation.GetCurrentClipId() == "MoveLeftUp")
		{
			animation.Play("IdleLeftUp");
		}
		else if (animation.GetCurrentClipId() == "MoveLeft")
		{
			animation.Play("IdleLeft");
		}
		else if (animation.GetCurrentClipId() == "MoveLeftDown")
		{
			animation.Play("IdleLeftDown");
		}
		else if (animation.GetCurrentClipId() == "MoveDown")
		{
			animation.Play("IdleDown");
		}
	}

}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(hand);
}

void Enemy::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	hand.setPosition(p);
}

void Enemy::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	hand.setPosition(x, y);
}

void Enemy::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);

	if (isHanded)
	{
		sf::Vector2f scale = hand.getScale();
		scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
		hand.setScale(scale);
	}
}

sf::Vector2f Enemy::WhereWay(sf::Vector2f dir)
{
	sf::Vector2f result;
	float minf = 1.f;
	for (auto it : way)
	{
		if (float diff = Utils::Distance({ abs(dir.x), dir.y }, it) < minf)
		{
			minf = diff;
			result = it;
		}
	}
	return result;
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

void Enemy::SetEnemy()
{
	const EnemyInfo* info = DATATABLE_MGR.Get<EnemyTable>(DataTable::Ids::Enemy)->Get(type);

	this->maxHp = info->maxHp;
	this->speed = info->speed;
	this->attackRange = info->attackRange;
	this->attackInterval = info->attackInterval;
	this->superarmor = info->superarmor;
}

void Enemy::OnDamage(const float& damage, sf::Vector2f dir, const float& knockback)
{
	if (!isAlive) return;

	if (!superarmor) SetPosition(position + dir * knockback);
	dir = WhereWay(dir);
	SetFlipX(dir.x > 0.f);

	if (IfHit != nullptr)
	{
		IfHit(damage);
	}
	else
	{
		hp = std::max(0.f, hp - damage);

		if (hp <= 0.f)
		{
			if (IfDie != nullptr)
			{
				IfDie(dir);
			}
			else
			{
				OnDie(dir);
			}

			isAlive = false;
			isHanded = false;
			hand.setTextureRect({ 0, 0, 0, 0 });
			return;
		}
	}

	// Animation
	if (dir == way[0])
	{
		animation.Play("HitUp");
	}
	else if (dir == way[1])
	{
		animation.Play("HitLeftUp");
	}
	else if (dir == way[2])
	{
		animation.Play("HitLeft");
	}
	else if (dir == way[3])
	{
		animation.Play("HitLeftDown");
	}
	else if (dir == way[4])
	{
		animation.Play("HitDown");
	}

}

void Enemy::OnBump()
{
	//player에게 피해를 주는 함수
}

void Enemy::OnDie(const sf::Vector2f& look)
{
	// Animation
	if (look == way[0])
	{
		animation.Play("DieUp");
	}
	else if (look == way[1])
	{
		animation.Play("DieLeftUp");
	}
	else if (look == way[2])
	{
		animation.Play("DieLeft");
	}
	else if (look == way[3])
	{
		animation.Play("DieLeftDown");
	}
	else if (look == way[4])
	{
		animation.Play("DieDown");
	}
}

void Enemy::OneShot(sf::Vector2f dir, float speed, bool isBlink) // pool반환 필요
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = new EnemyBullet();
	bullet->Shoot(dir, speed);
	bullet->SetPosition(position);
	bullet->SetBullet(isBlink);
	bullet->SetPlayer(player);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);

}

void Enemy::AngleShot(sf::Vector2f dir, float speed, float angle)
{
	SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = new EnemyBullet();
	dir = Utils::RotateVector(dir, angle);
	bullet->Shoot(dir, speed);
	bullet->SetPosition(position);
	bullet->SetPlayer(player);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);

}

void Enemy::FiveWayShot(sf::Vector2f dir, float speed)
{
	for (int i = 0; i < 5; i++)
	{
		sf::Vector2f ang = Utils::RotateVector(dir, -30.f + 15.f * i);
		OneShot(ang, speed);
	}
}

void Enemy::SixWayDie(sf::Vector2f dir, float speed, int chance)
{
	if (int ran = Utils::RandomRange(1, 100) >= chance)
	{
		OnDie(dir);
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		OneShot(Utils::DirectionFromAngle(60.f + 60.f * i), speed, true);
	}

	SetActive(false);
}
