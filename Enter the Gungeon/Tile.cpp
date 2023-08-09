#include "stdafx.h"
#include "Tile.h"

Tile::Tile(const std::string& textureId, const std::string& n):SpriteGo(textureId,n)
{
}

Tile::~Tile()
{
}

void Tile::Init()
{
	SpriteGo::Init();
}

void Tile::Release()
{
	SpriteGo::Release();
}

void Tile::Reset()
{
	SpriteGo::Reset();
}

void Tile::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Tile::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
