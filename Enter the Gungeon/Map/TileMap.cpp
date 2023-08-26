#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& textureId, const std::string& n) :VertexArrayGo(textureId, n), bsp(nullptr)
{
	startPos = { 0, 0 };
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath, bool textureIdIn)
{

	if (!textureIdIn) texture = RESOURCE_MGR.GetTexture(textureId);

	rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
	//size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };
	size.x = map.GetCell<int>(0, 1);
	size.y = map.GetCell<int>(1, 1);
	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			Tile tile;
			tile.x = j;
			tile.y = i;
			std::string fileInfo = map.GetCell<std::string>(j, i + 4);
			int texIndex = std::stoi(fileInfo);
			tile.texIndex = texIndex;

			size_t firstCommaPos = fileInfo.find(',');
			if (firstCommaPos != std::string::npos)
			{
				size_t secondCommaPos = fileInfo.find(',', firstCommaPos + 1);
				if (secondCommaPos != std::string::npos)
				{
					std::string firstNumberPart = fileInfo.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
					std::string secondNumberPart = fileInfo.substr(secondCommaPos + 1);

					tile.objectTypes = std::stoi(firstNumberPart);
					tile.monsterAndObject = std::stoi(secondNumberPart);
				}
			}
			/*size_t commaPos = fileInfo.find(',');
			if (commaPos != std::string::npos)
			{
				std::string numberPart = fileInfo.substr(commaPos + 1);
				int newTexIndex = std::stoi(numberPart);
				tile.objectTypes = newTexIndex;
			}*/

			tiles.push_back(tile);
		}
	}
	sf::Vector2f tileSize = { 25.f, 25.f };
	sf::Vector2f texSize = { 50.f, 50.f };
	sf::Vector2f texOffsets[4] =
	{
		{ 0.f, 0.f },
		{ texSize.x, 0.f },
		{ texSize.x, texSize.y },
		{ 0.f, texSize.y }
	};

	sf::Vector2f texNonOffset[4] =
	{
		{ texSize.x, 0.f },
		{ texSize.x * 2, 0.f },
		{ texSize.x * 2, texSize.y },
		{ texSize.x, texSize.y }
	};

	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(size.x * size.y * 4);
	sf::Vector2f currPos = startPos;

	sf::Vector2f offsets[4] =
	{
		{ 0.f, 0.f },
		{ tileSize.x, 0.f },
		{ tileSize.x, tileSize.y },
		{ 0.f, tileSize.y }
	};

	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			int tileIndex = size.x * i + j;
			int texIndex = tiles[tileIndex].texIndex;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = tileIndex * 4 + k;
				vertexArray[vertexIndex].position = currPos + offsets[k];
				if (tiles[tileIndex].texIndex == -1)
				{
					vertexArray[vertexIndex].texCoords = texNonOffset[k];
					vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
				}
				else
				{
					vertexArray[vertexIndex].texCoords = texOffsets[k];
					vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
				}
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
	return true;
}

void TileMap::LoadObject(const std::string& filePath, bool textureIdIn, int Laye)
{
	if (!textureIdIn) texture = RESOURCE_MGR.GetTexture(textureId);

	rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
	size.x = map.GetCell<int>(0, 1);
	size.y = map.GetCell<int>(1, 1);
	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			Tile tile;
			tile.x = j;
			tile.y = i;
			std::string fileInfo = map.GetCell<std::string>(j, i + 4);

			size_t firstCommaPos = fileInfo.find(',');
			if (firstCommaPos != std::string::npos)
			{
				size_t secondCommaPos = fileInfo.find(',', firstCommaPos + 1);
				if (secondCommaPos != std::string::npos)
				{
					std::string firstNumberPart = fileInfo.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
					std::string secondNumberPart = fileInfo.substr(secondCommaPos + 1);

					if (Laye == 0)
						tile.texIndex = std::stoi(firstNumberPart);
					else if (Laye == 1)
						tile.texIndex = std::stoi(secondNumberPart);
				}
			}
			/*size_t commaPos = fileInfo.find(',');
			if (commaPos != std::string::npos)
			{
				std::string numberPart = fileInfo.substr(commaPos + 1);
				int newTexIndex = std::stoi(numberPart);
				tile.texIndex  = newTexIndex;
			}*/
			tiles.push_back(tile);
		}
	}
	sf::Vector2f tileSize = { 25.f, 25.f };
	sf::Vector2f texSize = { 50.f, 50.f };
	sf::Vector2f texOffsets[4] =
	{
		{ 0.f, 0.f },
		{ texSize.x, 0.f },
		{ texSize.x, texSize.y },
		{ 0.f, texSize.y }
	};

	sf::Vector2f texNonOffset[4] =
	{
		{ texSize.x, 0.f },
		{ texSize.x * 2, 0.f },
		{ texSize.x * 2, texSize.y },
		{ texSize.x, texSize.y }
	};

	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(size.x * size.y * 4);
	sf::Vector2f currPos = startPos;

	sf::Vector2f offsets[4] =
	{
		{ 0.f, 0.f },
		{ tileSize.x, 0.f },
		{ tileSize.x, tileSize.y },
		{ 0.f, tileSize.y }
	};



	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			int tileIndex = size.x * i + j;
			int texIndex = tiles[tileIndex].texIndex;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = tileIndex * 4 + k;
				vertexArray[vertexIndex].position = currPos + offsets[k];
				if (tiles[tileIndex].texIndex == -1)
				{
					vertexArray[vertexIndex].texCoords = texNonOffset[k];
					vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
				}
				else
				{
					vertexArray[vertexIndex].texCoords = texOffsets[k];
					vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
				}
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
}

void TileMap::NoneFileLoad(int xSize, int ySize, bool textureIdI, bool testDraw)
{

	if (!textureIdI) texture = RESOURCE_MGR.GetTexture(textureId);


	size = { xSize, ySize };

	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			Tile tile;
			tile.x = j;
			tile.y = i;
			if (testDraw) tile.texIndex = static_cast<int>(MapObjectType::Pot);
			else tile.texIndex = static_cast<int>(MapObjectType::None);
			tiles.push_back(tile);
		}
	}

	sf::Vector2f tileSize = { 25.f, 25.f };
	sf::Vector2f texSize = { 50.f, 50.f };
	sf::Vector2f texOffsets[4] =
	{
		{ 0.f, 0.f },
		{ texSize.x, 0.f },
		{ texSize.x, texSize.y },
		{ 0.f, texSize.y }
	};
	sf::Vector2f texNonOffset[4] =
	{
		{ texSize.x, 0.f },
		{ texSize.x * 2, 0.f },
		{ texSize.x * 2, texSize.y },
		{ texSize.x, texSize.y }
	};
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(size.x * size.y * 4);
	sf::Vector2f currPos = startPos;

	sf::Vector2f offsets[4] =
	{
		{ 0.f, 0.f },
		{ tileSize.x, 0.f },
		{ tileSize.x, tileSize.y },
		{ 0.f, tileSize.y }
	};


	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			int tileIndex = size.x * i + j;
			int texIndex = tiles[tileIndex].texIndex;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = tileIndex * 4 + k;
				vertexArray[vertexIndex].position = currPos + offsets[k];
				if (tiles[tileIndex].texIndex == -1)
				{
					vertexArray[vertexIndex].texCoords = texNonOffset[k];
					vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
				}
				else
				{
					vertexArray[vertexIndex].texCoords = texOffsets[k];
					vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
				}
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}
}

void TileMap::ClearTile()
{
	if (!tiles.empty())
	{
		tiles.clear();
	}
}

void TileMap::Reset()
{
	VertexArrayGo::Reset();
}

void TileMap::ChangeTile(int x, int y, int tileIndex, sf::IntRect IntRect, TileType type)
{
	if (x < 0 || y < 0) return;
	else if (x >= size.x || y >= size.y) return;

	int texIndex = y * size.x + x;
	switch (type)
	{
	case TileType::TexIndex:
		tiles[texIndex].texIndex = tileIndex;
		break;
	case TileType::ObjectTypes:
		tiles[texIndex].objectTypes = tileIndex;
		break;
	case TileType::Monster:
		tiles[texIndex].monsterAndObject = tileIndex;
		break;
	}


	sf::FloatRect rect = (sf::FloatRect)IntRect;
	sf::Vector2f texOffsets[4] =
	{
		{ rect.left, rect.top },
		{ rect.left + rect.width, rect.top },
		{ rect.left + rect.width, rect.top + rect.height },
		{ rect.left, rect.top + rect.height }
	};

	for (int k = 0; k < 4; ++k)
	{
		int vertexIndex = texIndex * 4 + k;
		vertexArray[vertexIndex].texCoords = texOffsets[k];
	}
}

void TileMap::MakeWall(const std::string& path)
{
	rapidcsv::Document map(path, rapidcsv::LabelParams(-1, -1));
	int newHeight = map.GetCell<int>(1, 1) + 4 + 2 + 1;
	int size = map.GetCell<int>(1, newHeight - 2);
	for (int i = 0; i < size; ++i)
	{
		WallType type = static_cast<WallType>(map.GetCell<int>(0, newHeight));
		sf::RectangleShape shape;
		shape.setPosition({ map.GetCell<float>(1, newHeight) ,map.GetCell<float>(2, newHeight) });
		shape.setSize({ map.GetCell<float>(3, newHeight) ,map.GetCell<float>(4, newHeight) });
		shape.setOutlineThickness(2);
		switch (static_cast<int>(type))
		{
		case 0:
			shape.setOutlineColor(sf::Color::Red);
			break;
		case 1:
			shape.setOutlineColor(sf::Color::Green);
			break;
		case 2:
			shape.setOutlineColor(sf::Color::Yellow);
			break;
		case 3:
			shape.setOutlineColor(sf::Color::Blue);
			break;
		}
		shape.setFillColor(sf::Color::Transparent);
		colliedShape.push_back({ type,shape });
		newHeight++;
	}
}

sf::Vector2f TileMap::TileMapSize(const std::string& path)
{
	rapidcsv::Document map(path, rapidcsv::LabelParams(-1, -1));
	float width = map.GetCell<int>(0, 1);
	float height = map.GetCell<int>(1, 1);

	width *= tileSize.x;
	height *= tileSize.y;

	return sf::Vector2f{ width,height };
}

int TileMap::GetTexIndex(int x, int y)
{
	int tileIndex = size.x * y + x;
	return tiles[tileIndex].texIndex;

}

void TileMap::Divide()
{
	if (bsp == nullptr)
	{
		bsp = new BspRoom(sf::IntRect{ 0, 0, size.x, size.y });
		ListFilesInDirectory("Room/TileMapFile/");
	}
	bsp->Divide(this, 5, 3, fileList);
}

void TileMap::MakeRoom()
{
	ListFilesInDirectory("Room/TileMapFile/");
	bsp->MakeRoom(this, fileList);
}

void TileMap::ConnectRoom()
{

	if (bsp != nullptr)
	{
		bsp->ConnectRoom(this);
	}

}


void TileMap::ListFilesInDirectory(const std::string& folderPath)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((folderPath + "\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cerr << "Error finding files in directory." << std::endl;
		return;
	}

	int fileCount = 0;

	do {
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			//std::cout << "파일 이름: " << findFileData.cFileName << std::endl;
			std::string filePath = folderPath + findFileData.cFileName;
			fileList.push_back(filePath);
			++fileCount;
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);
}