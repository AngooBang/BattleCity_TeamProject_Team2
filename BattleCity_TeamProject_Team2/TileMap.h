#pragma once
#include "GameObject.h"



#define TILE_MAP_START_POS_X 20
#define TILE_MAP_START_POS_Y 20
#define TILE_MAP_SIZE_X TILE_SIZE * TILE_COUNT_X
#define TILE_MAP_SIZE_Y TILE_SIZE * TILE_COUNT_Y

enum class Terrain { None, Wall, HardWall, Water, Grass, Base, DestroyBase, End };

#define TILE_SIZE 32
#define SMALL_TILE_SIZE 16
#define TILE_COUNT_X 26
#define TILE_COUNT_Y 26
#define INSIDE_TILE_COUNT_X 2
#define INSIDE_TILE_COUNT_Y 2
typedef struct InsideTile
{
	RECT rc;
	Terrain terrain;
} INSIDE_TILE_INFO;

typedef struct Tile
{
	RECT rc;
	Terrain terrain;
	int frameX, frameY;
	INSIDE_TILE_INFO inTile[INSIDE_TILE_COUNT_Y * INSIDE_TILE_COUNT_X];
} TILE_INFO, *LPTILE_INFO;

typedef TILE_INFO(*Temp)/*[TILE_COUNT_Y]*/[TILE_COUNT_X];


class Image;
class TileMap : public GameObject
{
private:
	TILE_INFO m_tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

	Image* m_backGround;
	Image* m_tileImage;		

	Image* m_smallTileImage;

	FILE* m_fp;
	int m_stageNum;

	int m_elapsedCount;

	int testY;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void SetTileFrame(TILE_INFO* tileInfo);

	void SetInTileType(TILE_INFO* tileInfo);

	void SetBaseData();

	inline LPTILE_INFO GetTileInfo() { return this->m_tileInfo; }

	inline Image* GetTileImage() { return this->m_tileImage; }

	void LoadMapData();

	//inline Temp GetMapTileInfo() { return this->m_tileInfo; }
	inline int GetStageNum() { return this->m_stageNum; }

	TileMap() {}
	~TileMap() {}
};

