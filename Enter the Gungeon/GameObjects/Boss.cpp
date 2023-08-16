#include "stdafx.h"
#include "Boss.h"

Boss::Boss(EnemyTypes type, const std::string& textureId, const std::string& n)
	:Enemy(type, textureId, n)
{
	way.push_back({ 0.f, -1.f }); // Up
	way.push_back(Utils::Normalize({ 1.f, -1.f })); // LeftUp
	way.push_back({ 1.f, 0.f }); // Left
	way.push_back(Utils::Normalize({ 1.f, 1.f })); // LeftDown
	way.push_back({ 0.f, 1.f }); // Down
}

Boss::~Boss()
{
}
