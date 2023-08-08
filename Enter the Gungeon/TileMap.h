#pragma once
#include "VertexArrayGo.h"
#include "VertexArrayGo.h"
struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};

class TileMap : public VertexArrayGo
{
protected:

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);
	void SetVewScale(float scale);
	bool CheckCollied(const sf::Vector2f& position);

	std::vector<Tile> tiles;
};

