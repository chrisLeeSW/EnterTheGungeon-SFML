#include "stdafx.h"
#include "PrisonerActive.h"



PrisonerActive::PrisonerActive(const std::string& textureId, const std::string& n) : Active(textureId, n)
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerBottle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("weapon/PrisonerBottleBreak.csv"));
	animation.SetTarget(&sprite);
}

void PrisonerActive::Init()
{
	SpriteGo::Reset();
	player = PLAYER_MGR.GetPlayer();
	


	//SetPosition(pos);
}

void PrisonerActive::Release()
{
}

void PrisonerActive::Reset()
{
}

void PrisonerActive::Update(float dt)
{
	if(isUsingActiveSkill)
	{
		animation.Update(dt);
		SetOrigin(Origins::MC);
		breaktime -= dt;

		if(breaktime >= 0.f)
		{
			mousePos = INPUT_MGR.GetMousePos();
			sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);

			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
			{
				if (isone)
				{
					animation.Play("Bottle");
					position = player->GetPosition();
					look = Utils::Normalize(mouseWorldPos - position);
					isone = false;
				}
			}
			position += look * speed * dt;
			SetPosition(position);
			tick -= dt;
			if (tick <= 0.f)
			{
				angle45 += 45;
				sprite.setRotation(angle45);
				tick = 0.3f;
			}
		}
		else
		{
			if (animation.GetCurrentClipId() != "Break")
			{
				animation.Play("Break");
				sprite.setRotation(0);
			}

			if (animation.AnimationEnd())
			{
				isUsingActiveSkill = false;
			}
		}


	}
}

void PrisonerActive::Draw(sf::RenderWindow& window)
{
	if(isUsingActiveSkill)
	SpriteGo::Draw(window);
}
