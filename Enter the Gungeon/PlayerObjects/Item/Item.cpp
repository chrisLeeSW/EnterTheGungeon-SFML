#include "stdafx.h"
#include "Item.h"


Item::Item(const std::string& textureId, const std::string& n) : SpriteGo(textureId,n)
{
}

void Item::Init()
{
}

void Item::Release()
{
}

void Item::Reset()
{
}

void Item::Update(float dt)
{
}

void Item::Draw(sf::RenderWindow& window)
{
}

Item::Types Item::GetItemType()
{
	return Item::Types::None;
}

Item::WAP Item::GetItemWAP()
{
	return Item::WAP::None;
}
