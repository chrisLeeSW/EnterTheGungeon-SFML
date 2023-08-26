#pragma once
#include "VertexArrayGo.h"

class TileMap;

struct TileIndexInfo
{
	int texIndex = 0;
	int objectTypes = 0;
	int monset = 0;
};
struct BspRoom
{
	sf::IntRect rect;
	VertexArrayGo rectangle;

	int level = 0;

	BspRoom* parent;
	BspRoom* leftChild ;
	BspRoom* rightChild ;
	
	BspRoom(sf::IntRect rect = { 0, 0, 0, 0 });
	~BspRoom();

	void Divide(TileMap* tile, int depth, int tile_size, std::vector<std::string>& fileList);
	void MakeRoom(TileMap* tile,std::vector<std::string>& fileList);
	void ConnectRoom(TileMap* tile);
	sf::Vector2i GetCenter();

	bool isInRect(int x, int y, const sf::IntRect& r);
	void LoadFile(std::string& path,  std::vector<TileIndexInfo>& info, sf::Vector2i& tileSize);

};

