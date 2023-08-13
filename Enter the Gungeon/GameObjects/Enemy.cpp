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
	std::string name;
	switch (type)
	{
	case EnemyTypes::BulletKin:
		name = "BulletKin";
		isHanded = true;
		break;
	case EnemyTypes::KeyBulletKin:
		name = "KeyBulletKin";
		break;
	case EnemyTypes::ShotgunKinRed:
		name = "ShotgunKinRed";
		isHanded = true;
		break;
	case EnemyTypes::ShotgunKinBlue:
		name = "ShotgunKinBlue";
		isHanded = true;
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
}

void Enemy::Update(float dt)
{
	animation.Update(dt);

	if (!isAlive) return;

	direction = Utils::Normalize(player->GetPosition() - position);
	float distance = Utils::Distance(player->GetPosition(), position);

	if (attackRange > distance) //���� ������ �� ����� �� �ְ� �缳�� �ʿ�
	{
		direction = { 0.f, 0.f };
	}
	SetPosition(position + direction * speed * dt);

	if (player->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) // Collider �浹�� ���� �䱸
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

void Enemy::SetEnemy(float speed, float maxHp, float attackRange, bool superarmor)
{
	this->speed = speed;
	this->maxHp = maxHp;
	this->attackRange = attackRange;
	this->superarmor = superarmor;
}

void Enemy::OnDamage(const float& damage, const sf::Vector2f& dir, const float& knockback)
{
	if (!superarmor) SetPosition(position + dir * knockback);

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
	// dir�� �°� �缳�� �ʿ� - dir�� 8������ Distance�� �缭 �ּҰ��� �������� �ִϸ��̼��� ����ϴ°��� ���?
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
	//player���� ���ظ� �ִ� �Լ�
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
