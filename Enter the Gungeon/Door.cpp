#include "stdafx.h"
#include "Door.h"

Door::Door(int type, const std::string& textureId, const std::string& n) :SpriteGo(textureId , n) ,open(false)
{
	this->type = static_cast<DoorDirectionLook>(type);
}

void Door::Init()
{
	std::string doorDirectionType;
	switch (type)
	{
	case Door::DoorDirectionLook::Up:
		doorDirectionType = "Up";
		sprite.setTextureRect({ 10,131,25,25 });
		break;
	case Door::DoorDirectionLook::Down:
		doorDirectionType = "Down";
		sprite.setTextureRect({ 8,83,25,25 });
		break;
	case Door::DoorDirectionLook::Left:
		doorDirectionType = "Left";
		sprite.setTextureRect({ 8,183,5,25 });
		break;
	case Door::DoorDirectionLook::Right:
		doorDirectionType = "Right";
		sprite.setTextureRect({ 8,213,5,25 });
		break;
	}

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Door/" + doorDirectionType + "/DoorClose.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Door/" + doorDirectionType + "/Doordle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Objects/Door/" + doorDirectionType + "/DoorOpen.csv"));

	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
}

void Door::Reset()
{
	SpriteGo::Reset();
	animation.Play("Idle");
}

void Door::Update(float dt)
{
	SpriteGo::Update(dt);
	animation.Update(dt);
}

void Door::Open()
{
	if (!open)
	{
	animation.Play("Open");
	open = true;
	}
}

void Door::Close()
{

	if (open)
	{
		animation.Play("Close");
		open = false;
	}
	
}

void Door::EnterRoom()
{
}

void Door::ExitRoom()
{
}
