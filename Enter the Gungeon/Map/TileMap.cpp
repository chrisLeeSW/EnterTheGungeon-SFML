#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& textureId, const std::string& n) :VertexArrayGo(textureId,n), scaleFactor({0.f,0.f})
{
    //texture = RESOURCE_MGR.GetTexture(textureId); // txture -> Update동안에 한번에 동작을 안하는문제가 발생
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath)
{

    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };
    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tile.texIndex = map.GetCell<int>(j, i);
            tiles.push_back(tile);
        }
    }
    sf::Vector2f tileSize = { 50.f, 50.f };
    sf::Vector2f texSize = { 50.f, 50.f };
    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { texSize.x, 0.f },
        { texSize.x, texSize.y },
        { 0.f, texSize.y }
    };


    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 0, 0 };
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
                vertexArray[vertexIndex].texCoords = texOffsets[k];
                vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
            }
            currPos.x += tileSize.x;
        }
        currPos.x = startPos.x;
        currPos.y += tileSize.y;
    }
    return true;
}

void TileMap::NoneFileLoad(int xSize, int ySize)
{

    texture = RESOURCE_MGR.GetTexture(textureId);


    size = { xSize, ySize };

     for (int i = 0; i < size.y; ++i)
     {
         for (int j = 0; j < size.x; ++j)
         {
             Tile tile;
             tile.x = j;
             tile.y = i;
             tile.texIndex = static_cast<int>(MapObjectType::None);
             tiles.push_back(tile);
         }
     }

     sf::Vector2f tileSize = { 50.f, 50.f };
     sf::Vector2f texSize = { 50.f, 50.f };
     sf::Vector2f texOffsets[4] =
     {
         { 0.f, 0.f },
         { texSize.x, 0.f },
         { texSize.x, texSize.y },
         { 0.f, texSize.y }
     };
     vertexArray.setPrimitiveType(sf::Quads);
     vertexArray.resize(size.x * size.y * 4);
     sf::Vector2f startPos = { 0, 0 };
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
                 vertexArray[vertexIndex].texCoords = texOffsets[k];
                 vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
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

void TileMap::ChangeTile(int x, int y, int tileIndex, sf::IntRect IntRect)
{
    if (x < 0 || y < 0) return ;
    if (x >= size.x || y >= size.y) return ;

    int texIndex = y * size.x + x;
    tiles[texIndex].texIndex = tileIndex;

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
