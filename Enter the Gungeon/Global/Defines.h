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
	WallDown,
	NormalFloor1,
	NormalFloor2,
	NormalFloor3,
	NormalFloor4,
};

#include "AnimationClip.h"