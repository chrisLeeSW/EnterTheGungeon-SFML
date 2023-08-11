#pragma once

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
	sf::Vector2f startPos;
public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath,bool textureIdIn = true);
	void LoadObject(const std::string& filePath,bool textureIdIn=true);
	void NoneFileLoad(int xSize, int ySize);
	void ClearTile();

	void ChangeTile(int x,int y, int tileIndex, sf::IntRect IntRect);
	void SetWallSize(sf::Vector2i wallSize) { this->size = wallSize; }
	void SetWallSize(int x, int y) { this->size = { x,y }; };
	sf::Vector2i GetWallSize() { return size; }

	void SetStartPos(sf::Vector2f startPos) { this->startPos = startPos; }
	void SetStartPos(float x, float y) 
	{ this->startPos = {x,y}; }
	sf::Vector2f GetStartPos() { return startPos; }

	std::vector<Tile> tiles;
};

