#include "stdafx.h"
#include "DropItem.h"

DropItem::DropItem(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
	animation.SetTarget(&sprite);
}

void DropItem::Init()
{
	SetOrigin(Origins::MC);
}

void DropItem::Reset()
{

	switch (type)
	{
	case DropItem::Types::None:
		return;
		break;
	case DropItem::Types::Shell1:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Shell1.csv"));
		OnBump = [this]()
		{
			player->AddMoney(1);
		};
		break;
	case DropItem::Types::Shell2:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Shell2.csv"));
		OnBump = [this]()
		{
			player->AddMoney(5);
		};
		break;
	case DropItem::Types::Heart:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Heart.csv"));
		OnBump = [this]()
		{
			player->HealHp(1);
		};
		break;
	case DropItem::Types::Hearts:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Hearts.csv"));
		OnBump = [this]()
		{
			player->HealHp(2);
		};
		break;
	case DropItem::Types::Key:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Key.csv"));
		OnBump = [this]()
		{
			player->AddKey(1);
		};
		break;
	case DropItem::Types::Blank:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Blank.csv"));
		OnBump = [this]()
		{
			player->AddBlankBullet();
		};
		break;
	case DropItem::Types::HegemonyCredit:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/HegemonyCredit.csv"));
		OnBump = [this]()
		{
			// Á¶±İ °í¹Î
		};
		break;
	default:
		break;
	}

	player = PLAYER_MGR.GetPlayer();
	animation.Play("Idle");
}

void DropItem::Update(float dt)
{
	animation.Update(dt);

	if (sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
	{
		OnBump();
		// pool¿¡ return;
		Scene* scene = SCENE_MGR.GetCurrScene();
		scene->RemoveGo(this);
		pool->Return(this);
	}
}

void DropItem::SetType(DropItem::Types type)
{
	this->type = type;
}

void DropItem::SetPlayer(Player* player)
{
	this->player = player;
}
