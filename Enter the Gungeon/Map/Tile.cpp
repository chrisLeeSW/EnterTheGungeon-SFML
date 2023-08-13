#include "stdafx.h"
#include "Tile.h"


Tile::Tile(const std::string& textureId, const std::string& n,std::string name):SpriteGo(textureId,n), fileName(name)
{
}

Tile::~Tile()
{
}

void Tile::Init()
{
	SpriteGo::Init();
	if (fileName == "")
	{
		std::cout << "NotFile";

		return;
	}
	else
	{
		
	}
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
