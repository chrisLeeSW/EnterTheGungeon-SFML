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
	case MapObjectType::None:
		break;
	case MapObjectType::WallTop:
		break;
	case MapObjectType::WallRight:
		break;
	case MapObjectType::WallLeft:
		break;
	case MapObjectType::WallCornerRight:
		break;
	case MapObjectType::WallCornerLeft:
		break;
	case MapObjectType::WallDown:
		break;
	case MapObjectType::NormalFloor1:
		break;
	case MapObjectType::NormalFloor2:
		break;
	case MapObjectType::NormalFloor3:
		break;
	case MapObjectType::NormalFloor4:
		break;
	case MapObjectType::LibraryTop:
		break;
	case MapObjectType::LibraryLeft:
		break;
	case MapObjectType::LibraryRight:
		break;
	case MapObjectType::LibraryDown:
		break;
	case MapObjectType::LibraryCornerLeft:
		break;
	case MapObjectType::LibraryCornerRight:
		break;
	case MapObjectType::Pot:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Pot.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/PotBreak.csv"));
		break;
	case MapObjectType::Book1:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Book1.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Book1Break.csv"));
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

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		animation.Play("Break");
	}

}

void InteractionObject::PlayAnimation(MapObjectType type)
{
	animation.Play("Break");
}
