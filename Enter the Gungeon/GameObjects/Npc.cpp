#include "stdafx.h"
#include "Npc.h"

Npc::Npc(Npc::NpcType type)
	:SpriteGo(), type(type)
{
	animation.SetTarget(&sprite);
}

void Npc::Init()
{
	switch (type)
	{
	case Npc::NpcType::None:
		return;
		break;
	case Npc::NpcType::ShowOwner:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/NPC/ShowOwnerIdle.csv"));

		break;
	case Npc::NpcType::Count:
		std::cout << "WARNING: Wrong NpcType (Npc Init())" << std::endl;
		return;
		break;
	default:
		break;
	}
}

void Npc::Reset()
{
	animation.Play("Idle");
	SetOrigin(Origins::BC);
}

void Npc::Update(float dt)
{
	animation.Update(dt);
}
