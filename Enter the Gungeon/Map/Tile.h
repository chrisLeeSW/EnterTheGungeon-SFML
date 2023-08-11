#pragma once
#include "SpriteGo.h"

struct TileInfo
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
	int objectIndex = 0;
	float positionX;
	float positionY;
};

class Tile : public SpriteGo
{
protected:

public:
	Tile(const std::string& textureId = "", const std::string& n = "");
	virtual ~Tile() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

