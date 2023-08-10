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
	sf::Vector2f scaleFactor;
	sf::Vector2i size;
public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);
	void NoneFileLoad(int xSize, int ySize);
	void ClearTile();
	void ChangeTile(int x,int y, int tileIndex, sf::IntRect IntRect);
	std::vector<Tile> tiles;
};

