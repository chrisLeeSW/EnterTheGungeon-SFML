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
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleUp.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveUp.csv"));

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
	SetOrigin(origin);
	hand.setOrigin(sprite.getLocalBounds().width * 0.8, sprite.getLocalBounds().height * 0.3);
}

void Enemy::Update(float dt)
{
	animation.Update(dt);

	direction = Utils::Normalize(player->GetPosition() - position);

	if (direction.x != 0 || direction.y != 0)
	{
		if (animation.GetCurrentClipId() != "MoveLeft" &&
			INPUT_MGR.GetAxisRaw(Axis::Horizontal) != 0.f)
		{
			animation.Play("MoveLeft");
		}
		else if (animation.GetCurrentClipId() != "MoveDown" &&
			INPUT_MGR.GetAxisRaw(Axis::Vertical) > 0.f &&
			INPUT_MGR.GetAxisRaw(Axis::Horizontal) == 0.f)
		{
			animation.Play("MoveDown");
		}
		else if (animation.GetCurrentClipId() != "MoveUp" &&
			INPUT_MGR.GetAxisRaw(Axis::Vertical) < 0.f &&
			INPUT_MGR.GetAxisRaw(Axis::Horizontal) == 0.f)
		{
			animation.Play("MoveUp");
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
	SetFlipX(direction.x > 0);

	SetPosition(position + direction * speed * dt);
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
