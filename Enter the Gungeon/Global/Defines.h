#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	COUNT,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AimationClip,
};

enum class SceneId
{
	None = -1,
	Title,
	Lobby,
	Game,
	MapTool,
	BulletEditor,

	Count,
};

enum class MapObjectType
{
	None = -1,
	WallTop,
	WallRight,
	WallLeft,
	WallCornerRight,
	WallCornerLeft,
	WallDown,
	NormalFloor1,
	NormalFloor2,
	NormalFloor3,
	NormalFloor4,
	LibraryTop,
	LibraryLeft,
	LibraryRight,
	LibraryDown,
	LibraryCornerLeft,
	LibraryCornerRight,
	//아무것도 없는 벽 생각해야함
	MapObjectCount,
};

enum class InteractionObjectType
{
	None =-1,
	aa
};

#include "AnimationClip.h"