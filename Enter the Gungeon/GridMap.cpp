#include "stdafx.h"
#include "GridMap.h"

GridMap::GridMap(const std::string& textureId, const std::string& n) : VertexArrayGo(textureId, n)
{
}

GridMap::~GridMap()
{
}

bool GridMap::makeLine(const int x, const int y)
{
    return true;
}
