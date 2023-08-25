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

	GameMapTestScene, //이승우 테스트용
	TestRoom,// 이승우 테스트용 
	Count,
};

enum class MapObjectType
{
	None = -1,
	NormalWallTop,
	NorMalWallRight,
	NormalWallLeft,
	NoramlTile1,
	NormalTile2,

	LightWallTop,
	LightWallRight,
	LightWallLeft,
	LightWallTile1,
	LigtWallTile2,
	LightWallTile3,
	LightWallTile4,

	LibraryTop,
	LibraryLeft,
	LibraryRight,
	LibraryDown,
	LibraryTile1,

	StoreTop,
	StoreRight,
	StoreLeft,
	StoreTile1,
	StoreTile2,
	StoreTile3,

	TreasureRoomTile1,
	TreasureRoomTile2,
	TreasureRoomTile3,
	TreasureRoomTile4,

	BoosTile1,
	BoosTile2,
	BoosTile3,
	LobyTile1,
	LobyTile2,
	LobyTile3,
	LobyTile4,
	LobyTile5,
	LobyTile6,
	LobyTile7,
	LobyTile8,
	LobyTile9,
	LobyTile10,
	LobyTile11,
	LobyTile12,
	LobyTile13,
	LobyTile14,
	LobyTile15,
	LobyTile16,
	LobyTile17,

	Grass,
	QueenPicture,
	HeadObject,
	Stair,
	Flag1,
	Flag2,
	Flag3,

	StoreTable1,
	StoreTable2,
	StoreTable3,
	StoreTable4,
	StoreTable5,
	StoreTable6,
	StoreTableDisplay1,
	StoreTableDisplay2,

	TreasureRoomFlag,
	
	Armor,
	Chiar,

	TreasureAlter,
	TreasureObject,

	Pot,
	MonsterKin,
	MonsterKinKey,
	MonsterRed,
	MonsterBlue,
	Boss,
	StoreOner,

	MapObjectCount,
};

enum class RoomType
{
	None = -1,
	NormalStoneRoom,
	NormalLirbraryRoom,
	SpawnRoom, 
	BossRoom, 
	StoreRoom, 


	RoomTypeCount,
};

enum class WallType
{
	None = -1,
	Wall,
	WalloBlocker,
	FallingZone,
	TeleportZone,

};
struct WallTypeInfo
{
	WallType type;
	sf::RectangleShape  shape;
};

enum class TileType
{
	None = -1,
	TexIndex,
	ObjectTypes,
	Monster
};

#include "AnimationClip.h"