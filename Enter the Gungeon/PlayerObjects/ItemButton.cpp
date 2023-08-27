#include "stdafx.h"
#include "ItemButton.h"
#include "SceneMgr.h"
#include "StringTable.h"
#include "DataTableMgr.h"

ItemButton::ItemButton(const std::string& n)
	:GameObject(n)
{
}

ItemButton::~ItemButton()
{
}

void ItemButton::Init()
{
	sf::Font* font = RESOURCE_MGR.GetFont(fontId);
	if (font != nullptr)
	{
		manualtext.setFont(*font);
		nametext.setFont(*font);
	}

	StringTable* table = DATATABLE_MGR.Get<StringTable>(DataTable::Ids::String); // StringTable 사용

	std::wstring name;
	std::vector<std::wstring> names;

	for (int i = 0; i < manual.size(); ++i)
	{
		names.push_back(table->GetW(manual[i]));
	}


	manualtext.setString(names[0] + (std::wstring)L"\n" + names[1] + (std::wstring)L"\n" + names[2] + (std::wstring)L"\n" + names[3] + (std::wstring)L"\n" + names[4] + (std::wstring)L"\n" + names[5] + (std::wstring)L"\n" + names[6] + (std::wstring)L"\n" + names[7]);



	manualtext.setCharacterSize(textsize);
	manualtext.setPosition(manualpos);
	manualtext.setFillColor(sf::Color::White);

	name = table->GetW(itemname);
	nametext.setCharacterSize(namesize);
	nametext.setString(name);
	nametext.setPosition(namepos);
	nametext.setFillColor(sf::Color::Black);

	sf::Texture* tex = RESOURCE_MGR.GetTexture(textureId);
	if (tex != nullptr)
	{
		sprite.setTexture(*tex);
	}

	Utils::SetOrigin(sprite, Origins::MC);

	tex = RESOURCE_MGR.GetTexture(itemspriteId);
	if (tex != nullptr)
	{
		itemsprite.setTexture(*tex);
	}

	itemsprite.setPosition(375,120);

	Utils::SetOrigin(nametext,Origins::MC);
	Utils::SetOrigin(manualtext, Origins::MC);
	Utils::SetOrigin(itemsprite, Origins::MC); 

	nametext.setScale(0.3f,0.3f);
	manualtext.setScale(0.3f, 0.3f);

	isHover = false;
}

void ItemButton::Release()
{
	
}

void ItemButton::Reset()
{

}

void ItemButton::Update(float dt)
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
	
	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

	if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		book->SetCurrentClickButton(this);
		isClickButton = true;
	}
}

void ItemButton::Draw(sf::RenderWindow& window)
{
	//std::cout << "아이템 버튼 드로우" << std::endl;

		window.draw(itemsprite);
		window.draw(manualtext);
		window.draw(nametext);

}

void ItemButton::SetPosition(const sf::Vector2f& p)
{
	manualtext.setPosition(p);
	nametext.setPosition(p);
}

void ItemButton::SetPosition(float x, float y)
{

	manualtext.setPosition(x,y);
	nametext.setPosition(x,y);
}

void ItemButton::SetOrigin(Origins origin)
{
	Utils::SetOrigin(manualtext, origin);
	Utils::SetOrigin(nametext, origin);
}

void ItemButton::SetSpritePosition(float x, float y)
{
	spriteposition = sf::Vector2f({ x,y });
	sprite.setPosition(spriteposition);
}

void ItemButton::SetSpritePosition(float x)
{
	spriteposition.x -= x;
	sprite.setPosition(spriteposition);
}


sf::Vector2f ItemButton::GetSpritePosition()
{
	return spriteposition;
}
