#include "stdafx.h"
#include "InteractionObject.h"

InteractionObject::InteractionObject(MapObjectType type, const std::string& textureId, const std::string& n) :type(type), SpriteGo(textureId, n)
{
}

InteractionObject::~InteractionObject()
{
}

void InteractionObject::Init()
{
	switch (type)
	{
	case MapObjectType::Pot:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Pot.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/PotBreak.csv"));
		break;
	case MapObjectType::Armor:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Armor.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/ArmorBreak.csv"));
		break;
	case MapObjectType::Chiar:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Chair.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/ChairBreak.csv"));
		break;
	default:
		break;
	}

	animation.SetTarget(&sprite);
	SpriteGo::Init();
}

void InteractionObject::Reset()
{
	SpriteGo::Reset();
	animation.Play("Idle");
}

void InteractionObject::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1) && type== MapObjectType::Pot)
	//{
	//	animation.Play("Break");
	//}

}

void InteractionObject::PlayAnimation(MapObjectType type)
{
	if (!breakPlayAnimation)
	{
		animation.Play("Break");
		breakPlayAnimation = true;
	}

}
