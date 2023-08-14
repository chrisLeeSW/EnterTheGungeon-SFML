#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "SceneGame.h"

#include "SceneLobby.h" //test

Enemy::Enemy(EnemyTypes type, const std::string& textureId, const std::string& n)
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

}

void Enemy::Init()
{
	std::string name;
	switch (type)
	{
	case EnemyTypes::BulletKin:
		name = "BulletKin";
		isHanded = true;
		IfShoot = [&](sf::Vector2f dir, float speed)
		{
			OneShot(dir, speed);
		};
		maxHp = 15.f; // table 사용
		break;
	case EnemyTypes::KeyBulletKin:
		name = "KeyBulletKin";
		// Runaway 함수
		maxHp = 15.f;
		break;
	case EnemyTypes::ShotgunKinRed:
		name = "ShotgunKinRed";
		isHanded = true;
		IfShoot = [&](sf::Vector2f dir, float speed)
		{
			FiveWayShot(dir, speed);
		};
		IfDie = [&](sf::Vector2f dir)
		{
			SixWayDie(dir, speed, 20); // table 사용
		};
		maxHp = 30.f; // table 사용
		break;
	case EnemyTypes::ShotgunKinBlue:
		name = "ShotgunKinBlue";
		isHanded = true;
		IfDie = [&](sf::Vector2f dir)
		{
			SixWayDie(dir, speed, 33); // table 사용
		};
		maxHp = 40.f; // table 사용
		break;
	default:
		std::cerr << "ERROR: Not Exist EnemyTypes (Enemy Init())" << std::endl;
		break;
	}
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
	hand.setOrigin(sprite.getLocalBounds().width * 0.8, sprite.getLocalBounds().height * 0.25);

	hp = maxHp;
	isAlive = true;
	attackTimer = attackInterval;
}

void Enemy::Update(float dt)
{
	animation.Update(dt);

	if (!isAlive || player == nullptr) return;

	direction = Utils::Normalize(player->GetPosition() - position);
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
			if (min == way[0])
			{
				animation.Play("AttackUp");
			}
			else if (min == way[1])
			{
				animation.Play("AttackLeftUp");
			}
			else if (min == way[2])
			{
				animation.Play("AttackLeft");
			}
			else if (min == way[3])
			{
				animation.Play("AttackLeftDown");
			}
			else if (min == way[4])
			{
				animation.Play("AttackDown");
			}
		}
	}
	else
	{
		SetPosition(position + direction * speed * dt);
	}
	SetFlipX(direction.x > 0.f);

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
		if (animation.GetCurrentClipId() != "MoveUp" &&
			min == way[0])
		{
			animation.Play("MoveUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftUp" &&
			min == way[1])
		{
			animation.Play("MoveLeftUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeft" &&
			min == way[2])
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftDown" &&
			min == way[3])
		{
			animation.Play("MoveLeftDown");
		}
		else if (animation.GetCurrentClipId() != "MoveDown" &&
			min == way[4])
		{
			animation.Play("MoveDown");
		}
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

void Enemy::SetEnemy(float speed, float maxHp, float attackRange, float attackInterval, bool superarmor)
{
	this->speed = speed;
	this->maxHp = maxHp;
	this->attackRange = attackRange;
	this->attackInterval = attackInterval;
	this->superarmor = superarmor;
}

void Enemy::OnDamage(const float& damage, sf::Vector2f dir, const float& knockback)
{
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

	isAlive = false;
	isHanded = false;
	hand.setTextureRect({ 0, 0, 0, 0 });
}

void Enemy::OneShot(sf::Vector2f dir, float speed, bool isBlink) // pool반환 필요
{
	//SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrScene();
	SceneLobby* scene = (SceneLobby*)SCENE_MGR.GetCurrScene();
	EnemyBullet* bullet = new EnemyBullet();
	//bullet->Shoot(Utils::Normalize(player->GetPosition() - position), speed);
	bullet->Shoot(dir, speed);
	bullet->SetPosition(position);
	bullet->SetBullet(isBlink);
	bullet->Init();
	bullet->Reset();
	scene->AddGo(bullet);

}

void Enemy::FiveWayShot(sf::Vector2f dir, float speed)
{
	for (int i = 0; i < 5; i++)
	{
		//dir = Utils::Normalize(player->GetPosition() - position);
		sf::Vector2f ang =
		{
			dir.x * cos(-0.5f + 0.25f * i) - dir.y * sin(-0.5f + 0.25f * i),
			dir.x * sin(-0.5f + 0.25f * i) + dir.y * cos(-0.5f + 0.25f * i)
		};
		OneShot(ang, speed);
		std::cout << ang.x << " / " << ang.y << std::endl;
	}
}

void Enemy::SixWayDie(sf::Vector2f dir, float speed, int chance)
{
	if (int ran = Utils::RandomRange(1, 100) <= chance)
	{
		OnDie(dir);
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		OneShot(Utils::DirectionFromAngle(60.f + 60.f * i), speed, true);
	}

	isAlive = false;
	isHanded = false;
	hand.setTextureRect({ 0, 0, 0, 0 });

	SetActive(false);
}
