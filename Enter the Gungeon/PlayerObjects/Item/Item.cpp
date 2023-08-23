#include "stdafx.h"
#include "Item.h"


Item::Item(const std::string& textureId, const std::string& n) : SpriteGo(textureId,n)
{
}

void Item::Init()
{
}

void Item::Reset()
{
}

void Item::Update(float dt)
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
