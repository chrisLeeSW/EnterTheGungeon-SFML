#include "stdafx.h"
#include "PrisonerActive.h"



PrisonerActive::PrisonerActive(const std::string& textureId, const std::string& n) : Active(textureId, n)
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("playercsv/PilotIdleUp.csv"));

	animation.SetTarget(&sprite);
}

void PrisonerActive::Init()
{
	player = PLAYER_MGR.GetPlayer();
	dir, pos = player->GetDir();
	SpriteGo::Reset();
}

void PrisonerActive::Release()
{
}

void PrisonerActive::Reset()
{
}

void PrisonerActive::Update(float dt)
{
	animation.Update(dt);
}

void PrisonerActive::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
