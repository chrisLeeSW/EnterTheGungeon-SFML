#include "stdafx.h"
#include "Npc.h"

Npc::Npc(Npc::NpcType type)
	:SpriteGo(), type(type)
{
	animation.SetTarget(&sprite);

	box.setFillColor(sf::Color::Black);
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(2);

	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
}

void Npc::Init()
{
	switch (type)
	{
	case Npc::NpcType::None:
		return;
		break;
	case Npc::NpcType::ShopOwner:
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/NPC/ShopOwnerIdle.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/NPC/ShopOwnerTalk.csv"));

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

	text.setFont(*RESOURCE_MGR.GetFont("fonts/AurulentSansMono-Regular.otf"));

	SetOrigin(Origins::BC);

	player = PLAYER_MGR.GetPlayer();
	timer = duration;
}

void Npc::Update(float dt)
{
	animation.Update(dt);

	float distance = Utils::Distance(player->GetPosition(), position);

	if (timer <= duration)
	{
		timer += dt;
	}
	else if (distance <= 30.f)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::E)) // 상호작용
		{
			speech = "test";
			SetSpeech();
			animation.Play("Talk");
			animation.PlayQueue("Idle");

			timer = 0.f;
		}
	}
	
}

void Npc::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	if (timer < duration)
	{
		window.draw(box);
		window.draw(text);
	}
}

void Npc::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	box.setPosition(p + sf::Vector2f{ 0, -sprite.getLocalBounds().height * 2.f });
	text.setPosition(box.getPosition());
}

void Npc::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	box.setPosition(x, y - sprite.getLocalBounds().height * 2.f);
	text.setPosition(box.getPosition());
}

void Npc::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
	Utils::SetOrigin(box, Origins::TC);
	Utils::SetOrigin(text, Origins::TC);
}

void Npc::SetSpeech()
{
	box.setSize({ speech.size() * 7.f, 20.f });
	text.setString(speech);

	SetPosition(position);
	SetOrigin(origin);
}
