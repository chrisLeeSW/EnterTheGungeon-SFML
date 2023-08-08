#pragma once
#include "VertexArrayGo.h"

class GridMap : public VertexArrayGo
{
protected:

public:
	GridMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~GridMap() override;

	bool makeLine(const int x, const int y);
};

