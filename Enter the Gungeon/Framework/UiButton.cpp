#include "stdafx.h"
#include "UiButton.h"
#include "SceneMgr.h"


UiButton::UiButton(const std::string& textureId, const std::string& fontId, const std::string& n)
	:SpriteGo(textureId,n), fontId(fontId)
{
}

UiButton::~UiButton()
{
}

void UiButton::Init()
{
	SpriteGo::Init();
}

void UiButton::Release()
{
	SpriteGo::Release();
}

void UiButton::Reset()
{
	SpriteGo::Reset();
	sf::Font* font = RESOURCE_MGR.GetFont(fontId);
	if (font != nullptr)
	{
		text.setFont(*font);
	}
	SetOrigin(origin);
	isHover = false;
}

void UiButton::Update(float dt)
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(uiMousePos);

	if (!prevHover && isHover)
	{
		if(OnEnter != nullptr)
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

void UiButton::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(text);
}

void UiButton::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	text.setPosition(p);
}

void UiButton::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	text.setPosition(x, y);
}

void UiButton::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
	Utils::SetOrigin(text, origin);
}