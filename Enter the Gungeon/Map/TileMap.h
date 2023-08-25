#pragma once
#include "VertexArrayGo.h"
#include "BspRoom.h"

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
	int objectTypes = 0;
	int monsterAndObject = 0;
};

class TileMap : public VertexArrayGo
{
public : 
protected:

	sf::Vector2i size;
	sf::Vector2f startPos;
	sf::Vector2f tileSize = { 25.f,25.f };
	std::vector<std::string> fileList;
	
	
public:
	BspRoom* bsp;
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath,bool textureIdIn = true);
	void LoadObject(const std::string& filePath,bool textureIdIn=true);
	void NoneFileLoad(int xSize, int ySize, bool textureIdI = true, bool testDraw = false);
	void ClearTile();
	virtual void Reset();
	void ChangeTile(int x,int y, int tileIndex, sf::IntRect IntRect, TileType type = TileType::TexIndex);
	void SetWallSize(sf::Vector2i wallSize) { this->size = wallSize; }
	void SetWallSize(int x, int y) { this->size = { x,y }; };
	sf::Vector2i GetWallSize() { return size; }

	void SetStartPos(sf::Vector2f startPos) { this->startPos = startPos; }
	void SetStartPos(float x, float y) 
	{ this->startPos = {x,y}; }
	sf::Vector2f GetStartPos() { return startPos; }
	sf::Vector2f GetTileSize() { return tileSize; }
	void MakeWall(const std::string& path);
	std::vector<WallTypeInfo>colliedShape;

	std::vector<Tile> tiles;
	
	sf::Vector2f TileMapSize(const std::string& path);
	int GetTexIndex(int x, int y);
	

	void Divide();
	void MakeRoom();
	void ConnectRoom();
	void ListFilesInDirectory(const std::string& folderPath);
};

