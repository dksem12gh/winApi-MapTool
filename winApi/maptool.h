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

	//���̺�, �ε�, ����, ������Ʈ, ���찳 ��ư
	button* _btSave;
	button* _btLode;
	button* _btDrawTr;
	button* _btDrawObj;
	button* _bterasertr;
	button* _bteraserobj;
	button* _bttLayerObj;
	button* _btLayerTr;
	

	//�� ���̾�, ������Ʈ ���̾�,���ǰ���̾�
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

	//���� ����
	void maptoolSetup();
	void setMap();
	void objSetMap();

	void objectSetup();

	void Save(char*);
	void Load(char*);

	//����, ������Ʈ
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	tagTile* getTile() { return _tiles; }



	maptool(){}
	~maptool(){}
};

