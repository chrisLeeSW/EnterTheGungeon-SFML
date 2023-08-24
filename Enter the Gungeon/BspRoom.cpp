#include "stdafx.h"
#include "BspRoom.h"
#include "TileMap.h"



static int countLoof = 0;
BspRoom::BspRoom(sf::IntRect rect)
	:parent(nullptr), leftChild(nullptr), rightChild(nullptr), rect(rect)
{

}

void BspRoom::MakeRoom(TileMap* tile, std::vector<std::string>& fileList)
{

	//float chance = 0.05f;
	//float makeRoomValue = Utils::RandomRange(0.f, 1.f);
	////if (makeRoomValue <= chance) 
	//{
	//	//if (divided)
	//	{
	//		std::vector<TileIndexInfo>info;
	//		sf::Vector2i tileSize;
	//		int randFileIndex = Utils::RandomRange(0, fileList.size());
	//		LoadFile(fileList[randFileIndex], info, tileSize);
	//		int count = 0;
	//		std::cout << "left " << rect.left << "// top" << rect.top << std::endl;
	//		if (tileSize.y < rect.top + rect.height ||
	//			tileSize.x < rect.width + rect.left)
	//		{
	//			for (int y = rect.top;y < tileSize.y;++y)
	//			{
	//				for (int x = rect.left;x < tileSize.x;++x)
	//				{
	//					int texIndex = y * tile->GetWallSize().x + x;
	//				/*	if (tile->tiles[texIndex].texIndex == -2)
	//						continue;*/
	//					//else 
	//					tile->ChangeTile(x, y, info[count].texIndex, sf::IntRect{ 0, (50 * info[count].texIndex), 50, 50 });
	//					count++;
	//					countLoof++;
	//				}
	//			}
	//		}
	//		/*
	//		for (int y = rect.top+1; y < rect.top + rect.height; y++)
	//			{
	//				for (int x = rect.left+1; x < rect.left + rect.width; x++)
	//				{
	//					int texIndex = y * tile->GetWallSize().x + x;
	//					if (tile->tiles[texIndex].texIndex == -2)
	//						continue;
	//					else tile->ChangeTile(x, y, 0, sf::IntRect{ 0, 0, 50, 50 });
	//				}
	//			}
	//		*/
	//	}
	//}
	//std::cout << countLoof << std::endl;
	//if (leftChild)
	//{
	//	leftChild->MakeRoom(tile, fileList);
	//}
	//if (rightChild)
	//{
	//	rightChild->MakeRoom(tile, fileList);
	//}

	std::vector<TileIndexInfo>info;
	sf::Vector2i tileSize;
	int randFileIndex = Utils::RandomRange(0, fileList.size());
	LoadFile(fileList[randFileIndex], info, tileSize);
	int count = 0;
	//std::cout << "left " << rect.left << "// top" << rect.top << "// width" << rect.width << "// height" << rect.height << std::endl;
	//std::cout << "Tile Size" << tileSize.x << "\t" << tileSize.y << std::endl;
	if ((rect.width) > tileSize.x && (rect.height) > tileSize.y)
	{
		for (int y = 0;y < tileSize.y;++y)
		{
			for (int x = 0;x < tileSize.x;++x)
			{
				tile->ChangeTile(x + rect.left + 1, y + rect.top + 1, info[count].texIndex, sf::IntRect{ 0, (50 * info[count].texIndex), 50, 50 }, TileType::TexIndex);
				//tile->ChangeTile(x + rect.left + 1, y + rect.top + 1, info[count].objectTypes, sf::IntRect{ 0, (50 * info[count].objectTypes), 50, 50 }, TileType::ObjectTypes);
				//tile->ChangeTile(x + rect.left + 1, y + rect.top + 1, info[count].monset, sf::IntRect{ 0, (50 * info[count].monset), 50, 50 }, TileType::Monster);
				count++;
				countLoof++;
			}
		}
	}

}

bool BspRoom::isInRect(int x, int y, const sf::IntRect& r)
{
	return x >= r.left && x < r.left + r.width && y >= r.top && y < r.top + r.height;
}

void BspRoom::LoadFile(std::string& path, std::vector<TileIndexInfo>& info, sf::Vector2i& tileSize)
{
	rapidcsv::Document map(path, rapidcsv::LabelParams(-1, -1));
	int xSize = map.GetCell<int>(0, 1);
	int ySize = map.GetCell<int>(1, 1);
	for (int i = 0; i < ySize; ++i)
	{
		for (int j = 0; j < xSize; ++j)
		{
			TileIndexInfo tile;
			std::string fileInfo = map.GetCell<std::string>(j, i + 4);
			int texIndex = std::stoi(fileInfo);
			tile.texIndex = texIndex;
			size_t commaPos = fileInfo.find(',');
			if (commaPos != std::string::npos)
			{
				std::string numberPart = fileInfo.substr(commaPos + 1);
				int newTexIndex = std::stoi(numberPart);
				tile.objectTypes = newTexIndex;
			}
			info.push_back(tile);
		}
	}
	tileSize = { xSize,ySize };
}

BspRoom::~BspRoom()
{
	if (leftChild != nullptr)
	{
		delete leftChild;
		leftChild = nullptr;
	}

	if (rightChild != nullptr)
	{
		delete rightChild;
		rightChild = nullptr;
	}
}

void BspRoom::Divide(TileMap* tile, int depth, int tile_size, std::vector<std::string>& fileList)
{
	if (depth <= 0 || rect.width < 2 * tile_size || rect.height < 2 * tile_size)
	{
		MakeRoom(tile, fileList); // 조건에 따라 방을 만듭니다.
		return;
	}

	int hDivider = (rect.height / tile_size / 2) * tile_size;
	int wDivider = (rect.width / tile_size / 2) * tile_size;

	leftChild = new BspRoom();
	rightChild = new BspRoom();

	leftChild->level = this->level + 1;
	rightChild->level = this->level + 1;

	leftChild->parent = this;
	rightChild->parent = this;

	sf::IntRect r;

	if (rand() % 2 == 0)
	{
		// 수평 분할
		if (hDivider < 2 * tile_size) return;

		leftChild->rect = { rect.left, rect.top, rect.width, hDivider };
		rightChild->rect = { rect.left, rect.top + hDivider, rect.width, rect.height - hDivider };

		for (int i = rect.left; i < rect.left + rect.width; i++)
		{
			tile->ChangeTile(i, rect.top + hDivider, -2, r);
		}
	}
	else
	{
		// 수직 분할
		if (wDivider < 2 * tile_size) return;

		leftChild->rect = { rect.left, rect.top, wDivider, rect.height };
		rightChild->rect = { rect.left + wDivider, rect.top, rect.width - wDivider, rect.height };

		for (int i = rect.top; i < rect.top + rect.height; i++)
		{
			tile->ChangeTile(rect.left + wDivider, i, -2, r);
		}
	}

	leftChild->Divide(tile, depth - 1, tile_size, fileList);
	rightChild->Divide(tile, depth - 1, tile_size, fileList);
	//if (leftChild != nullptr && rightChild != nullptr)
	//{
	//	leftChild->Divide(tile);
	//	rightChild->Divide(tile);
	//	return;
	//}

	//TileMap* tileMap = tile;

	//int randRatio = Utils::RandomRange(4, 6);
	//if (rect.height > rect.width)
	//{
	//	while (GetCenter().y + 1 > (rect.height * randRatio) / 10 &&
	//		GetCenter().y - 1 < (rect.height * randRatio) / 10)
	//	{
	//		randRatio = Utils::RandomRange(4, 6);
	//	}
	//}
	//else
	//{
	//	while (GetCenter().x + 1 > (rect.width * randRatio) / 10 &&
	//		GetCenter().x - 1 < (rect.width * randRatio) / 10)
	//	{
	//		randRatio = Utils::RandomRange(4, 6);
	//	}
	//}
	//leftChild = new BspRoom();
	//rightChild = new BspRoom();

	//leftChild->level = this->level + 1;
	//rightChild->parent = this;

	//rightChild->level = this->level + 1;
	//rightChild->parent = this;

	//sf::IntRect r;
	//if (rect.height > rect.width) //가로로 자름
	//{
	//	leftChild->rect = rect;
	//	leftChild->rect.width = rect.width;
	//	leftChild->rect.height = (rect.height * randRatio) / 10;

	//	rightChild->rect = rect;
	//	rightChild->rect.top = rect.top + (rect.height * randRatio) / 10;
	//	rightChild->rect.height = rect.height - ((rect.height * randRatio) / 10);

	//	for (int i = rect.left; i < rect.left + rect.width; i++)
	//	{
	//		tileMap->ChangeTile(i, rect.top + leftChild->rect.height, -2, r);
	//	}
	//	return;
	//}
	//else //세로로 자름
	//{
	//	leftChild->rect = rect;
	//	leftChild->rect.left = rect.left;
	//	leftChild->rect.width = (rect.width * randRatio) / 10;

	//	rightChild->rect = rect;
	//	rightChild->rect.left = rect.left + (rect.width * randRatio) / 10;
	//	rightChild->rect.width = rect.width - ((rect.width * randRatio) / 10);

	//	for (int i = rect.top; i < rect.top + rect.height; i++)
	//	{
	//		tileMap->ChangeTile(rect.left + leftChild->rect.width, i, -2, r);
	//	}
	//	return;
	//}
}

void BspRoom::ConnectRoom(TileMap* tile)
{
	if (leftChild == nullptr || rightChild == nullptr) return;

	sf::Vector2i leftCenter = leftChild->GetCenter();
	sf::Vector2i rightCenter = rightChild->GetCenter();


	sf::IntRect r{ 0,50,50,50 };
	if (rect.height > rect.width)
	{
		for (int y = std::min(leftCenter.y, rightCenter.y); y <= std::max(leftCenter.y, rightCenter.y); y++)
		{
			tile->ChangeTile(leftCenter.x, y, 1, r);
		}
	}
	else
	{
		// Connect horizontally
		for (int x = std::min(leftCenter.x, rightCenter.x); x <= std::max(leftCenter.x, rightCenter.x); x++)
		{
			tile->ChangeTile(x, leftCenter.y, 1, r);
		}
	}
	leftChild->ConnectRoom(tile);
	rightChild->ConnectRoom(tile);
	return;
}

sf::Vector2i BspRoom::GetCenter()
{
	return sf::Vector2i{ (int)((rect.left) + (rect.width * 0.5f)),(int)((rect.top) + (rect.height * 0.5f)) };
}