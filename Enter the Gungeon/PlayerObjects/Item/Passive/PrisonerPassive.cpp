#include "stdafx.h"
#include "PrisonerPassive.h"


PrisonerPassive::PrisonerPassive(const std::string& textureId, const std::string& n) : Passive(textureId, n)
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerPassive.csv"));
	animation.SetTarget(&sprite);
}

void PrisonerPassive::Init()
{
	SpriteGo::Reset();


	player = PLAYER_MGR.GetPlayer();
}

void PrisonerPassive::Release()
{
}

void PrisonerPassive::Reset()
{
}

void PrisonerPassive::Update(float dt)
{
	if (player->IsHit() || isPassiveOn)
	{
		isPassiveOn = true;
		animation.Update(dt);
		SetPosition(player->GetPosition().x, player->sprite.getGlobalBounds().top - sprite.getLocalBounds().height);
		SetOrigin(Origins::MC);
		if (onePlay)
		{
			animation.Play("PrisonerPassive");
			onePlay = false;
			player->GetCurrenWeapon()->RequestReload();
		}
		if (animation.AnimationEnd())
		{
			onePlay = true;
			isPassiveOn = false;
		}
	}
}

void PrisonerPassive::Draw(sf::RenderWindow& window)
{
	if(isPassiveOn)
	SpriteGo::Draw(window);
}
