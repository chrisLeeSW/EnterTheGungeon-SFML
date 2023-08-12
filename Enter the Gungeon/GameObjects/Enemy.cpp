#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(EnemyTypes type, const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n), type(type)
{
	
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	switch (type)
	{
	case EnemyTypes::None:

		break;
	case EnemyTypes::BulletKin:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleLeftUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleLeftDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleDown.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveLeftUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveLeftDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveDown.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinHitUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinHitLeftUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinHitLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinHitLeftDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinHitDown.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinDieUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinDieLeftUp.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinDieLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinDieLeftDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinDieDown.csv"));

		isHanded = true;
		break;
	default:

		break;
	}
	animation.SetTarget(&sprite);
}

void Enemy::Release()
{
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
}

void Enemy::Update(float dt)
{
	animation.Update(dt);

	if (!isAlive) return;

	direction = Utils::Normalize(player->GetPosition() - position);
	float distance = Utils::Distance(player->GetPosition(), position);

	if (attackRange > distance) //벽을 만났을 때 사격할 수 있게 재설정 필요
	{
		direction = { 0.f, 0.f };
	}
	SetPosition(position + direction * speed * dt);

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
	SetFlipX(direction.x > 0.f);
	if (direction.x != 0.f || direction.y != 0.f)
	{
		if (animation.GetCurrentClipId() == "IdleUp" &&
			direction.x == 0.f && direction.y < 0.f)
		{
			animation.Play("MoveUp");
		}
		else if (animation.GetCurrentClipId() == "IdleLeftUp" &&
			direction.x < 0.f && direction.y < 0.f)
		{
			animation.Play("MoveLeftUp");
		}
		else if (animation.GetCurrentClipId() == "IdleLeft" &&
			direction.x < 0.f && direction.y == 0.f)
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() == "IdleLeftDown" &&
			direction.x < 0.f && direction.y > 0.f)
		{
			animation.Play("MoveLeftDown");
		}
		else if (animation.GetCurrentClipId() == "IdleDown" &&
			direction.x == 0.f && direction.y > 0.f)
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

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

void Enemy::SetEnemy(float speed, float maxHp, float attackRange)
{
	this->speed = speed;
	this->maxHp = maxHp;
	this->attackRange = attackRange;
}

void Enemy::OnDamage(const float& damage, const sf::Vector2f& dir, const float& knockback)
{
	SetPosition(position + dir * knockback);

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
				IfDie();
			}
			else
			{
				OnDie();
			}
		}
	}

	// Animation
	// dir에 맞게 재설정 필요 - dir과 8방향의 Distance를 재서 최소값을 기준으로 애니메이션을 재생하는것은 어떨까?
	if (animation.GetCurrentClipId() == "MoveUp" ||
		animation.GetCurrentClipId() == "IdleUp")
	{
		animation.Play("HitUp");
		animation.PlayQueue("IdleUp");
	}
	else if (animation.GetCurrentClipId() == "MoveLeftUp" ||
		animation.GetCurrentClipId() == "IdleLeftUp")
	{
		animation.Play("HitLeftUp");
		animation.PlayQueue("IdleLeftUp");
	}
	else if (animation.GetCurrentClipId() == "MoveLeft" ||
		animation.GetCurrentClipId() == "IdleLeft")
	{
		animation.Play("HitLeft");
		animation.PlayQueue("IdleLeft");
	}
	else if (animation.GetCurrentClipId() == "MoveLeftDown" ||
		animation.GetCurrentClipId() == "IdleLeftDown")
	{
		animation.Play("HitLeftDown");
		animation.PlayQueue("IdleLeftDown");
	}
	else if (animation.GetCurrentClipId() == "MoveDown" ||
		animation.GetCurrentClipId() == "IdleDown")
	{
		animation.Play("HitDown");
		animation.PlayQueue("IdleDown");
	}
}

void Enemy::OnBump()
{
	//player에게 피해를 주는 함수
}

void Enemy::OnDie()
{
	if (animation.GetCurrentClipId() != "HitUp")
	{
		animation.Play("DieUp");
	}
	else if (animation.GetCurrentClipId() == "HitLeftUp")
	{
		animation.Play("DieLeftUp");
	}
	else if (animation.GetCurrentClipId() == "HitLeft")
	{
		animation.Play("DieLeft");
	}
	else if (animation.GetCurrentClipId() == "HitLeftDown")
	{
		animation.Play("DieLeftDown");
	}
	else if (animation.GetCurrentClipId() == "HitDown")
	{
		animation.Play("DieDown");
	}

	isAlive = false;
	isHanded = false;
	hand.setTextureRect({ 0, 0, 0, 0 });
}
