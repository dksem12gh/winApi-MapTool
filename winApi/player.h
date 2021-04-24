#pragma once
#include "gameNode.h"
#include "mapLode.h"
#include "animation.h"

//≈ ≈© 4πÊ«‚
enum PLAYERDIRECTION
{
	PLAYERDIRECTION_LEFT,
	PLAYERDIRECTION_RIGHT,
	PLAYERDIRECTION_UP,
	PLAYERDIRECTION_DOWN,
	PLAYERDIRECTION_NONE
};

class player : public gameNode
{
private:
	tagTile* _Tile;
	mapLode* _mapLd;

	image* _playerBody;
	image* _playerHead;
	image* _playerShadow;

	PLAYERDIRECTION _direction;
	PLAYERDIRECTION _playerUD;

	animation* _bodyDansingRight;
	animation* _headBangingRight;
	animation* _bodyDansingLeft;
	animation* _headBangingLeft;

private:

	RECT _rcBody;
	RECT _rcHead;
	RECT _rcShadow;

	RECT _probe[4];

	int speed;

	POINT _playerPt;
	float _oneBlock;
	int i;

public:
	HRESULT init(mapLode* mapLoad);
	void release(void);
	void update();
	void render();

	void setPlayerPosition();
	void dansingLR();
	void dansingUD();

	void dansingBase(POINT pt);
	void blockOn();

	RECT getPlayerRc() { return _rcBody; }
	POINT getPlayerPt() { return _playerPt; }

	void setPlayerMapMemoryLink(mapLode* tm) { _mapLd = tm; }

	player(){}
	~player(){}
};

