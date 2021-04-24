#pragma once
#include "gameNode.h"
#include "mapLode.h"
#include "player.h"

class gameCamera :
	public gameNode
{
private:
	image* camera;
	image* _incamera;

	mapLode * _mapLode;
	player* _player;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void gameCamerabase(POINT playerPt);

	gameCamera(){}
	~gameCamera(){}

};

