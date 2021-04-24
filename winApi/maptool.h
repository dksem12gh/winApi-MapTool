#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"

static void saveCallBack();
static void loadCaalBack();
static void objectCallBack();
static void tileCallBack();
static void objDrawCallBack();
static void trDrawCallBack();
static void trEraserCallBack();
static void objEraserCallBack();

class maptool : public gameNode
{
private:

	//세이브, 로드, 지형, 오브젝트, 지우개 버튼
	button* _btSave;
	button* _btLode;
	button* _btDrawTr;
	button* _btDrawObj;
	button* _bterasertr;
	button* _bteraserobj;
	button* _bttLayerObj;
	button* _btLayerTr;
	

	//땅 레이어, 오브젝트 레이어,장식품레이어
	HWND _btLayerTile;
	HWND _btLayerObj;
	HWND _btLayerMak;

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];

	tagCurrentTile _objCurrentTile;
	tagTile _objTiles[TILEX*TILEY];
	tagSampleTile _objectTiles[OBJTILEX*OBJTILEY];

	int _pos[2];
	int _save;

	RECT blackRc;

public:
	HRESULT init(void);
	void release(void);
	void update();
	void render();

	//맵툴 셋팅
	void maptoolSetup();
	void setMap();
	void objSetMap();

	void objectSetup();

	void Save(char*);
	void Load(char*);

	//지형, 오브젝트
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	tagTile* getTile() { return _tiles; }



	maptool(){}
	~maptool(){}
};

