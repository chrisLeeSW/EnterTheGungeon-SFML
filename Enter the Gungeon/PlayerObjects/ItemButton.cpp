#include "stdafx.h"
#include "ItemButton.h"
#include "SceneMgr.h"

ItemButton::ItemButton(const std::string& textureId, const std::string& fontId, const std::string& n)
	:SpriteGo(textureId, n), fontId(fontId)
{
}

ItemButton::~ItemButton()
{
}

void ItemButton::Init()
{
	SpriteGo::Init();
}

void ItemButton::Release()
{
	SpriteGo::Release();
}

void ItemButton::Reset()
{
	sf::Font* font = RESOURCE_MGR.GetFont(fontId);
	if (font != nullptr)
	{
		text.setFont(*font);
	}
	SpriteGo::Reset();


	sprite.setPosition(0,0);

	sortLayer = 11;
	SetScale(5,5);
	isHover = false;
}

void ItemButton::Update(float dt)
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
	sprite.setPosition(0, 0);
	
	std::cout << sprite.getPosition().x << std::endl;

	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

	if (!prevHover && isHover)
	{
		if (OnEnter != nullptr)
			OnEnter();
	}
	if (prevHover && !isHover)
	{
		if (OnExit != nullptr)
			OnExit();
	}
	if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		if (OnClick != nullptr)
			OnClick();
	}
}

void ItemButton::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(text);
}

void ItemButton::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	text.setPosition(p);
}

void ItemButton::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	text.setPosition(x, y);
}

void ItemButton::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
	Utils::SetOrigin(text, origin);
}