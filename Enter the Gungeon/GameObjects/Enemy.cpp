#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(MonsterTypes type, const std::string& textureId, const std::string& n)
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
	case MonsterTypes::None:

		break;
	case MonsterTypes::BulletKin:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinIdleUp.csv"));

		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveLeft.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveDown.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Enemy/BulletKinMoveUp.csv"));

		isHanded = true;
		hand.setTextureRect({ 121, 16, 4, 4 });
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

	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
	if (tex != nullptr)
	{
		hand.setTexture(*tex);
	}


}

void Enemy::Update(float dt)
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(hand);
}
