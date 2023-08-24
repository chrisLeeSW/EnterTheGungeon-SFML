#include "stdafx.h"
#include "DisplayItem.h"
#include "DataTableMgr.h"
#include "StringTable.h"

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
	StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String); // StringTable 사용
	std::string itemname;

	switch (item)
	{
	case DisplayItem::Names::None:
		price = 0;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 256, 78, 19, 14 });
		text.setString("");

		action = []()
		{

		};
		break;
	case DisplayItem::Names::Heart:
		price = 20;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 13, 13, 13 });
		itemname = table->Get("HEART") + ": " + std::to_string(price);
		text.setString(itemname);

		action = [this]()
		{
			player->HealHp(1);

			item = DisplayItem::Names::None;
			Reset();
		};
		break;
	case DisplayItem::Names::Hearts:
		price = 30;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 28, 15, 13 });
		itemname = table->Get("HEARTS") + ": " + std::to_string(price);
		text.setString(itemname);

		action = [this]()
		{
			player->HealHp(2);

			item = DisplayItem::Names::None;
			Reset();
		};
		break;
	case DisplayItem::Names::Key:
		price = 25;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 43, 16, 14 });
		itemname = table->Get("KEY") + ": " + std::to_string(price);
		text.setString(itemname);

		action = [this]()
		{
			player->AddKey(1);

			item = DisplayItem::Names::None;
			Reset();
		};
		break;
	case DisplayItem::Names::Blank:
		price = 20;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 61, 12, 12 });
		itemname = table->Get("BLANK") + ": " + std::to_string(price);
		text.setString(itemname);

		action = [this]()
		{
			player->AddBlankBullet();

			item = DisplayItem::Names::None;
			Reset();
		};
		break;
	case DisplayItem::Names::Ammo:
		price = 30;
		sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Items.png"));
		sprite.setTextureRect({ 1, 77, 11, 14 });
		itemname = table->Get("AMMO") + ": " + std::to_string(price);
		text.setString(itemname);

		action = [this]()
		{
			// player ammo 증가 함수

			item = DisplayItem::Names::None;
			Reset();
		};
		break;
	case DisplayItem::Names::Count:
		break;
	default:
		std::cerr << "ERROR: Not Exist DisplayItem Names" << std::endl;
		SetActive(false);
		return;
		break;
	}

	interaction = false;

	box.setSize({ itemname.size() * 7.f, sprite.getLocalBounds().height });
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(1);
	box.setFillColor(sf::Color::Black);

	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	text.setFont(*RESOURCE_MGR.GetFont("fonts/AurulentSansMono-Regular.otf"));

	SetOrigin(origin);

	player = PLAYER_MGR.GetPlayer();
}

void DisplayItem::Update(float dt)
{
	if (item == DisplayItem::Names::None) return;

	float distance = Utils::Distance(player->GetPosition(), position);
	if (distance <= 30.f)
	{
		interaction = true;
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::E)) // 상호작용
		{
			if (player->GetMoney() < price) return;

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
