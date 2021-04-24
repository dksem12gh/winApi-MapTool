#include "stdafx.h"
#include "gameCamera.h"

HRESULT gameCamera::init(void)
{
	BEATMANAGER->init();

	_mapLode = new mapLode;
	_mapLode->init();

	_player = new player;
	_player->init(_mapLode);

	return S_OK;
}

void gameCamera::release(void)
{
	SAFE_DELETE(_mapLode);
	SAFE_DELETE(_player);
}

void gameCamera::update(void)
{
	BEATMANAGER->update();

	_mapLode->update();
	_player->update();

}

void gameCamera::render(void)
{
	_mapLode->render();
	_player->render();

	_mapLode->render(_player->getPlayerRc(), _player->getPlayerPt());

	BEATMANAGER->render(getMemDC());
}

void gameCamera::gameCamerabase(POINT playerPt)
{
}
