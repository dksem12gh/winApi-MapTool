#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "animation.h"
#include "loadingScene.h"

class mapLode :
	public gameNode
{
private:
	tagTile _objTiles[TILEX * TILEY];
	tagTile _tiles[TILEX * TILEY];		  //타일
	DWORD _attribute[TILEX * TILEY];	  //속성
	int _pos[2];
	
	animation* _lobyLightR;
	animation* _lobyLightL;

	image* _lobyLR;
	image* _lobyLL;

	vector <tagTile> _objVec;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void render(RECT playerRc,POINT playerPos);

	void tilesOption();

	void load(char*);

	void comboLight();


	tagTile* getTiles() { return _tiles; }
	tagTile* getObj() { return _objTiles; }

	int getPosFirst() { return 0; }

	DWORD* getAttribute() { return _attribute; }

	mapLode(){}
	~mapLode(){}
};

