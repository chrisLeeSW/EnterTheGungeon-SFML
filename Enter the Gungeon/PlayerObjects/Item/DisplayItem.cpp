#include "stdafx.h"
#include "DisplayItem.h"

DisplayItem::DisplayItem(DisplayItem::Names item, const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n), item(item)
{
	
}

void DisplayItem::Init()
{
	SetOrigin(Origins::MC);
}

void DisplayItem::Reset()
{
	switch (item)
	{
	case DisplayItem::Names::None:
		return;
		break;
	case DisplayItem::Names::Heart:
		price = 20;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 13, 13, 13 });
		action = [this]()
		{
			// if 가격이 안되면 return;
			// player hp +1
		};
		break;
	case DisplayItem::Names::Hearts:
		price = 30;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 28, 15, 13 });
		action = [this]()
		{
			// if 가격이 안되면 return;
			// player hp +2
		};
		break;
	case DisplayItem::Names::Key:
		price = 25;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 43, 16, 14 });
		action = [this]()
		{
			// player key +1
		};
		break;
	case DisplayItem::Names::Blank:
		price = 20;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 61, 12, 12 });
		action = [this]()
		{
			// player blank +1
		};
		break;
	case DisplayItem::Names::Ammo:
		price = 30;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 77, 11, 14 });
		action = [this]()
		{
			// player ammo 증가 함수
		};
		break;
	case DisplayItem::Names::Count:
		break;
	default:
		break;
	}

	interaction = false;

	box.setSize({ 50.f, sprite.getLocalBounds().height });
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(1);
	box.setFillColor(sf::Color::Black);

	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	text.setFont(*RESOURCE_MGR.GetFont("fonts/AurulentSansMono-Regular.otf"));
	text.setString("test");

	SetOrigin(origin);

	player = PLAYER_MGR.GetPlayer();
}

void DisplayItem::Update(float dt)
{
	float distance = Utils::Distance(player->GetPosition(), position);
	if (distance <= 30.f)
	{
		interaction = true;
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::E)) // 상호작용
		{
			action();
		}
	}
	else
	{
		interaction = false;
	}
}

void DisplayItem::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	if (interaction)
	{
		window.draw(box);
		window.draw(text);
	}
}

void DisplayItem::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	sf::Vector2f diff = { sprite.getLocalBounds().width * 0.5f + 10.f, 0.f };
	box.setPosition(p + diff);
	text.setPosition(p + diff);
}

void DisplayItem::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	float diff = sprite.getLocalBounds().width * 0.5f + 10.f;
	box.setPosition(x + diff, y);
	text.setPosition(x + diff, y);
}

void DisplayItem::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
	Utils::SetOrigin(box, Origins::ML);
	Utils::SetOrigin(text, Origins::ML);
}
