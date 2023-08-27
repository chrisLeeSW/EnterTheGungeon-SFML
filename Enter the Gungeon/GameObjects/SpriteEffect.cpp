#include "stdafx.h"
#include "SpriteEffect.h"
#include "SceneMgr.h"
#include "Utils.h"

SpriteEffect::SpriteEffect(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Effect/Aiming.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Effect/Dust.csv"));

	animation.SetTarget(&sprite);
}

void SpriteEffect::SetEffect(SpriteEffect::Effect effect)
{
	this->effect = effect;

	switch (effect)
	{
	case SpriteEffect::Effect::Aiming:
		animation.Play("Aiming");
		break;
	case SpriteEffect::Effect::Dust:
		animation.Play("Dust");
		break;
	default:
		return;
		break;
	}
}

void SpriteEffect::Init()
{
	
}

void SpriteEffect::Reset()
{
	SetOrigin(Origins::MC);
}

void SpriteEffect::Update(float dt)
{
	animation.Update(dt);
	SetOrigin(origin);

	if (animation.AnimationEnd())
	{
		if (action != nullptr)
		{
			action();
		}

		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		pool->Return(this);
	}
}
