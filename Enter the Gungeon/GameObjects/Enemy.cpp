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
		if (animation.GetCurrentClipId() != "MoveUp" &&
			direction.x == 0.f && direction.y < 0.f)
		{
			animation.Play("MoveUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftUp" &&
			direction.x < 0.f && direction.y < 0.f)
		{
			animation.Play("MoveLeftUp");
		}
		else if (animation.GetCurrentClipId() != "MoveLeft" &&
			direction.x < 0.f && direction.y == 0.f)
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() != "MoveLeftDown" &&
			direction.x < 0.f && direction.y > 0.f)
		{
			animation.Play("MoveLeftDown");
		}
		else if (animation.GetCurrentClipId() != "MoveDown" &&
			direction.x == 0.f && direction.y > 0.f)
		{
			animation.Play("MoveDown");
		}
	}
	else
	{
		if (animation.GetCurrentClipId() == "MoveLeft" &&
			animation.GetCurrentClipId() != "IdleLeft")
		{
			animation.Play("IdleLeft");
		}
		else if (animation.GetCurrentClipId() == "MoveDown" &&
			animation.GetCurrentClipId() != "IdleDown")
		{
			animation.Play("IdleDown");
		}
		else if (animation.GetCurrentClipId() == "MoveUp" &&
			animation.GetCurrentClipId() != "IdleUp")
		{
			animation.Play("IdleUp");
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

void Enemy::SetEnemy(float speed, float maxHp)
{
	this->speed = speed;
	this->maxHp = maxHp;
}

void Enemy::OnDamage(float damage)
{
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
	if (animation.GetCurrentClipId() == "MoveLeft" ||
		animation.GetCurrentClipId() == "IdleLeft")
	{
		animation.Play("HitLeft");
	}
	else if (animation.GetCurrentClipId() == "MoveDown" ||
		animation.GetCurrentClipId() == "IdleDown")
	{
		animation.Play("HitDown");
	}
	else if (animation.GetCurrentClipId() != "MoveUp" ||
		animation.GetCurrentClipId() == "IdleUp")
	{
		animation.Play("HitUp");
	}
}

void Enemy::OnBump()
{
	//player에게 피해를 주는 함수
}

void Enemy::OnDie()
{
	if (animation.GetCurrentClipId() == "HitLeft")
	{
		animation.Play("DieLeft");
	}
	else if (animation.GetCurrentClipId() == "HitDown")
	{
		animation.Play("DieDown");
	}
	else if (animation.GetCurrentClipId() != "HitUp")
	{
		animation.Play("DieUp");
	}

	isAlive = false;
}
