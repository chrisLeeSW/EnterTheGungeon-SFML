#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& textureId, const std::string& n) :VertexArrayGo(textureId,n)
{
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath)
{

    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    sf::Vector2i size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

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

void TileMap::SetVewScale(float scale)
{
    sf::Vector2f texSize = { 50.f, 50.f };

    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { texSize.x, 0.f },
        { texSize.x, texSize.y },
        { 0.f, texSize.y }
    };
    for (int i = 0; i < tiles.size(); ++i)
    {
        int tileIndex = i;
        int texIndex = tiles[tileIndex].texIndex;
        for (int k = 0; k < 4; ++k)
        {
            int vertexIndex = tileIndex * 4 + k;
            vertexArray[vertexIndex].position *= scale;
            vertexArray[vertexIndex].texCoords.y = texOffsets[k].y * scale + texSize.y * texIndex;
        }
    }
}

bool TileMap::CheckCollied(const sf::Vector2f& position)
{
    return false;
}