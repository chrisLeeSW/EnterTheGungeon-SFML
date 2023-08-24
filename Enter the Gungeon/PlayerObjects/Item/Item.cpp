#include "stdafx.h"
#include "Item.h"


Item::Item(const std::string& textureId, const std::string& n) : SpriteGo(textureId,n)
{
}

Item::Types Item::GetItemType()
{
	return type;
}

Item::WAP Item::GetItemWAP()
{
	return wap;
}
