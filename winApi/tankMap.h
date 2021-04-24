#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tankMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		  //타일
	DWORD _attribute[TILEX * TILEY];	  //속성
	int _pos[2];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void save();
	void load();

	tagTile* getTiles() { return _tiles; }
	int getPosFirst() { return 0; }
	
	DWORD* getAttribute() { return _attribute; }

	tankMap() {}
	~tankMap() {}
};

