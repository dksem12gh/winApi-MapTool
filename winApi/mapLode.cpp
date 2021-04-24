#include "stdafx.h"
#include "mapLode.h"


HRESULT mapLode::init(void)
{

	LEVELCAMERA->init();

	this->load("save/mapsave.map");

	_lobyLL = IMAGEMANAGER->findImage("tilemap");
	_lobyLR = IMAGEMANAGER->findImage("tilemap");

	this->tilesOption();

	return S_OK;
}

void mapLode::release(void)
{
}

void mapLode::update(void)
{

	LEVELCAMERA->update();

	_lobyLightL->frameUpdate(TIMEMANAGER->getElapsedTime());
	_lobyLightR->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void mapLode::render(void)
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		POINT temp;
		temp.x = _tiles[i].rc.left - LEVELCAMERA->getCameraPt().x+45;
		temp.y = _tiles[i].rc.top - LEVELCAMERA->getCameraPt().y;

		if (PtInRect(&LEVELCAMERA->getGameCameraRc(), temp))
		{
			IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left-LEVELCAMERA->getCameraPt().x, _tiles[i].rc.top - LEVELCAMERA->getCameraPt().y, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].terrain == TR_LOBYBEAT_L)
			{
				_lobyLL->aniRender(getMemDC(), _tiles[i].rc.left - LEVELCAMERA->getCameraPt().x, _tiles[i].rc.top - LEVELCAMERA->getCameraPt().y, _lobyLightL);
			}
			else if (_tiles[i].terrain == TR_LOBYBEAT_R)
			{
				_lobyLR->aniRender(getMemDC(), _tiles[i].rc.left - LEVELCAMERA->getCameraPt().x, _tiles[i].rc.top - LEVELCAMERA->getCameraPt().y, _lobyLightR);
			}
		}
	}

	for (int i = 0; i < _objVec.size(); i++)
	{
		POINT temp;
		temp.x = _objVec[i].rc.left - LEVELCAMERA->getCameraPt().x+45;
		temp.y = _objVec[i].rc.top - LEVELCAMERA->getCameraPt().y;

		if (PtInRect(&LEVELCAMERA->getGameCameraRc(), temp))
		{
			IMAGEMANAGER->frameRender("tilemap2", getMemDC(), _objVec[i].rc.left - LEVELCAMERA->getCameraPt().x, _objVec[i].rc.top - 30 - LEVELCAMERA->getCameraPt().y, _objVec[i].objFrameX, _objVec[i].objFrameY);
		}
	}
}

void mapLode::render(RECT playerRc, POINT playerPos)
{
	RECT tempRc;

	for (int i = 0; i < _objVec.size(); i++)
	{
		POINT temp;

		temp.x = _objVec[i].rc.left - LEVELCAMERA->getCameraPt().x+45;
		temp.y = _objVec[i].rc.top - LEVELCAMERA->getCameraPt().y;

		if (PtInRect(&LEVELCAMERA->getGameCameraRc(), temp))
		{
			if (!IntersectRect(&tempRc, &playerRc, &_objVec[i].rc) && playerRc.bottom > _objVec[i].rc.top)continue;

			IMAGEMANAGER->frameRender("tilemap2", getMemDC(), _objVec[i].rc.left - LEVELCAMERA->getCameraPt().x, _objVec[i].rc.top - 30 - LEVELCAMERA->getCameraPt().y, _objVec[i].objFrameX, _objVec[i].objFrameY);
		}
	}
	LEVELCAMERA->render(getMemDC());
}

void mapLode::tilesOption()
{
	_lobyLightL = new animation;
	_lobyLightL->init(400,250, 50, 50);
	_lobyLightL->setFPS(0.5);
	_lobyLightL->setPlayFrame(0, 1, false, true);
	_lobyLightL->start();


	_lobyLightR = new animation;
	_lobyLightR->init(400, 250, 50, 50);
	_lobyLightR->setFPS(0.5);
	_lobyLightR->setPlayFrame(2, 3, false, true);
	_lobyLightR->start();
}

void mapLode::load(char* szFileName)
{
	HANDLE  hFile;
	DWORD  dwRead;
	HWND hwnd;

	hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, _tiles, sizeof(tagTile) * TILEX * TILEX, &dwRead, NULL);
	ReadFile(hFile, _objTiles, sizeof(tagTile) * TILEX * TILEY, &dwRead, NULL);
	ReadFile(hFile, _pos, sizeof(int) * 2, &dwRead, NULL);
	CloseHandle(hFile);

	//타일 정의
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		
	}

	////오브젝트 정의
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (_tiles[i].obj == OBJ_TANK1 || _tiles[i].obj == OBJ_TANK2)
	//	{
	//		_tiles[i].obj = OBJ_NONE;
	//	}
	//}


	//맵 속성 정의
	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_objTiles[i].obj == OBJ_LEVEL1)
		{
			_attribute[i] = ATTR_LEVEL1;
			_objVec.push_back(_objTiles[i]);
		}

		if (_objTiles[i].obj == OBJ_LEVEL2)
		{
			_attribute[i] = ATTR_LEVEL2;
			_objVec.push_back(_objTiles[i]);
		}
		if (_objTiles[i].obj == OBJ_LEVEL3)
		{
			_attribute[i] = ATTR_LEVEL3;
			_objVec.push_back(_objTiles[i]);
		}
		if (_objTiles[i].obj == OBJ_BROKENLEVEL1)
		{
			_attribute[i] = ATTR_LEVEL1;
			_objVec.push_back(_objTiles[i]);
		}
		if (_objTiles[i].obj == OBJ_BROKENLEVEL2)
		{
			_attribute[i] = ATTR_LEVEL2;
			_objVec.push_back(_objTiles[i]);
		}
		if (_objTiles[i].obj == OBJ_BROKENLEVEL3)
		{
			_attribute[i] = ATTR_LEVEL3;
			_objVec.push_back(_objTiles[i]);
		}
	}
}

void mapLode::comboLight()
{
}
