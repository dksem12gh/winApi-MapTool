#include "stdafx.h"
#include "maptool.h"

int _ctrSelect = 0;
int _curSelect = 0;

HRESULT maptool::init(void)
{
	gameNode::init(TRUE);

	_btSave = new button;
	_btLode = new button;
	_btDrawTr = new button;
	_btDrawObj = new button;
	_bterasertr = new button;
	_bteraserobj = new button;
	_bttLayerObj = new button;
	_btLayerTr = new button;
	

	_btSave->init("save", WINSIZEX - 1150, WINSIZEY - 50, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), saveCallBack);
	_btLode->init("load", WINSIZEX - 950, WINSIZEY - 50, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), loadCaalBack);
	_bttLayerObj->init("object", WINSIZEX - 100, WINSIZEY - 50, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), objectCallBack);
	_btLayerTr->init("terrain", WINSIZEX - 350, WINSIZEY - 50, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), tileCallBack);
	_btDrawObj->init("drawobj", WINSIZEX - 100, WINSIZEY - 90, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), objDrawCallBack);
	_btDrawTr->init("drawtr", WINSIZEX - 350, WINSIZEY - 90, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), trDrawCallBack);
	_bteraserobj->init("erasertr", WINSIZEX - 100, WINSIZEY - 130, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), trEraserCallBack);
	_bterasertr->init("eraserobj", WINSIZEX - 350, WINSIZEY - 130, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), objEraserCallBack);


	//���� �׸��� ��ư���� �ʱ�ȭ
	_ctrSelect = CTRL_TERRAINDRAW;

	maptoolSetup();
	objectSetup();

	//����Ÿ�� �ʱ�ȭ(����)
	_currentTile.x = 0;
	_currentTile.y = 0;

	_save = 0;
	return S_OK;
}

void maptool::release(void)
{
	gameNode::release();
}

void maptool::update()
{
	gameNode::update();

	_btSave->update();
	_btLode->update();
	_bttLayerObj->update();
	_btLayerTr->update();
	_btDrawObj->update();
	_btDrawTr->update();
	_bteraserobj->update();
	_bterasertr->update();
	CAMERAMANAGER->update();

	if (_ctrSelect == CTRL_SAVE)
	{
		Save("save/mapsave.map");
	}

	if (_ctrSelect == CTRL_LOAD)
	{
		Load("save/mapsave.map");
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		switch (_ctrSelect)
		{
		case CTRL_TILE:
		{
			setMap();
		}
		break;
		case CTRL_OBJ:
		{
			objSetMap();
		}
		break;
		default:
			break;
		}
	}
}

void maptool::render()
{
	IMAGEMANAGER->render("back", getMemDC());

	if (_ctrSelect == CTRL_TILE)
	{
		IMAGEMANAGER->render("tilemap", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth(), 0);
	}
	if (_ctrSelect == CTRL_OBJ)
	{
		IMAGEMANAGER->render("tilemap2", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tilemap2")->getWidth(), 0);
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//ȭ�鸸 ����ϱ����� �ӽ� ����Ʈ����
		POINT temp;

		temp.x = _tiles[i].rc.left - CAMERAMANAGER->getcameraPoint().x;
		temp.y = _tiles[i].rc.top - CAMERAMANAGER->getcameraPoint().y;

		//ī�޶� ��Ʈ�� ��ĥ���� ��������
		if (PtInRect(&CAMERAMANAGER->getcameraRc(), temp))
		{
			IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left - CAMERAMANAGER->getcameraPoint().x, _tiles[i].rc.top - CAMERAMANAGER->getcameraPoint().y, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//ȭ�鸸 ����ϱ����� �ӽ� ����Ʈ����
		POINT temp;

		temp.x = _objTiles[i].rc.left - CAMERAMANAGER->getcameraPoint().x;
		temp.y = _objTiles[i].rc.top - CAMERAMANAGER->getcameraPoint().y;

		if (_objTiles[i].obj == OBJ_NONE)continue;
		if (PtInRect(&CAMERAMANAGER->getcameraRc(), temp))
		{
			IMAGEMANAGER->frameRender("tilemap2", getMemDC(), _objTiles[i].rc.left - CAMERAMANAGER->getcameraPoint().x, _objTiles[i].rc.top - CAMERAMANAGER->getcameraPoint().y-16, _objTiles[i].objFrameX, _objTiles[i].objFrameY);
		}
	}
	//=============================================================
	_btSave->render();
	_btLode->render();
	_bttLayerObj->render();
	_btLayerTr->render();
	_btDrawObj->render();
	_btDrawTr->render();
	_bteraserobj->render();
	_bterasertr->render();
}

void maptool::maptoolSetup()
{
	//������ ���� �� ����
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("tilemap")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//���ʸ� ����
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//�⺻���� �򸮴� Ÿ�� ����
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (i % 2 == 0)
		{
			_tiles[i].terrainFrameX = 0;
			_tiles[i].terrainFrameY = 0;

			_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			_tiles[i].obj = OBJ_NONE;
		}
		else
		{
			_tiles[i].terrainFrameX = 2;
			_tiles[i].terrainFrameY = 0;

			_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			_tiles[i].obj = OBJ_NONE;
		}
	}
}

void maptool::objectSetup()
{
	//������ ���� �� ����
	for (int i = 0; i < OBJTILEY; i++)
	{
		for (int j = 0; j < OBJTILEX; j++)
		{
			_objectTiles[i * OBJTILEX + j].objFrameX = j;
			_objectTiles[i * OBJTILEX + j].objFrameY = i;

			SetRect(&_objectTiles[i * OBJTILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("tilemap2")->getWidth()) +j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("tilemap2")->getWidth())  +j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//���ʸ� ����
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_objTiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_objTiles[i].obj = OBJ_NONE;
	}
}

void maptool::setMap()
{
	//������ ����
	//������ ����Ÿ�� �� �̹��� �ε��� ��ȣ�� ��� ����
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}
	//���� ��

	if (_ptMouse.x > 0 && _ptMouse.x < 620 && _ptMouse.y > 0 && _ptMouse.y < WINSIZEY)
	{
		POINT cameraPt;
		cameraPt.x = _ptMouse.x + CAMERAMANAGER->getcameraPoint().x;
		cameraPt.y = _ptMouse.y + CAMERAMANAGER->getcameraPoint().y;

		for (int i = 0; i < TILEX * TILEY; i++)
		{

			POINT temp;

			temp.x = _tiles[i].rc.left - CAMERAMANAGER->getcameraPoint().x;
			temp.y = _tiles[i].rc.top - CAMERAMANAGER->getcameraPoint().y;

			if (PtInRect(&CAMERAMANAGER->getcameraRc(), temp) && PtInRect(&_objTiles[i].rc, cameraPt))
			{
				if (_curSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;

					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//���� ��ư�� ���찳�� üũ�Ǿ� ������
				else if (_curSelect == CTRL_ERASER)
				{
					_tiles[i].terrainFrameX = 2;
					_tiles[i].terrainFrameY = 0;

					_tiles[i].obj = OBJ_NONE;
					_tiles[i].terrain = TR_END;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
}
void maptool::objSetMap()
{
	//������ ����
	//������ ����Ÿ�� �� �̹��� �ε��� ��ȣ�� ��� ����
	for (int i = 0; i < OBJTILEX * OBJTILEY; i++)
	{
		if (PtInRect(&_objectTiles[i].rcTile, _ptMouse))
		{
			_objCurrentTile.x = _objectTiles[i].objFrameX;
			_objCurrentTile.y = _objectTiles[i].objFrameY;
			break;
		}
	}
	//���� ��

	if (_ptMouse.x > 0 && _ptMouse.x < 620 && _ptMouse.y > 0 && _ptMouse.y < WINSIZEY)
	{
		POINT cameraPt;
		cameraPt.x = _ptMouse.x + CAMERAMANAGER->getcameraPoint().x;
		cameraPt.y = _ptMouse.y + CAMERAMANAGER->getcameraPoint().y;

		for (int i = 0; i < OBJX * OBJY; i++)
		{

			POINT temp;

			temp.x = _objTiles[i].rc.left - CAMERAMANAGER->getcameraPoint().x;
			temp.y = _objTiles[i].rc.top - CAMERAMANAGER->getcameraPoint().y;

			if (PtInRect(&CAMERAMANAGER->getcameraRc(), temp) && PtInRect(&_objTiles[i].rc, cameraPt))
			{
				if (_curSelect == CTRL_OBJDRAW)
				{
					_objTiles[i].objFrameX = _objCurrentTile.x;
					_objTiles[i].objFrameY = _objCurrentTile.y;

					_objTiles[i].obj = objSelect(_objCurrentTile.x, _objCurrentTile.y);

				}
				//���� ��ư�� ���찳�� üũ�Ǿ� ������
				else if (_curSelect == CTRL_ERASER)
				{
					_objTiles[i].objFrameX = 2;
					_objTiles[i].objFrameY = 0;

					_objTiles[i].obj = OBJ_NONE;
					_objTiles[i].terrain = TR_END;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
}

//������������������������������������������������������������������������������
// �٦��� 08-09-10, ���̺� seth. ������
//������������������������������������������������������������������������������
void maptool::Save(char* szFileName)
{
	HANDLE  hFile;
	DWORD  dwRead;

	hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, _tiles, sizeof(tagTile) * TILEX * TILEY, &dwRead, NULL);
	WriteFile(hFile, _objTiles, sizeof(tagTile) * TILEX * TILEY, &dwRead, NULL);
	WriteFile(hFile, _pos, sizeof(int) * 2, &dwRead, NULL);
	CloseHandle(hFile);

}

//������������������������������������������������������������������������������
// �٦��� 08-09-10, �ε� seth. ������
//������������������������������������������������������������������������������
void maptool::Load(char* szFileName)
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

	//InvalidateRect(hwnd, NULL, false);

}
TERRAIN maptool::terrainSelect(int frameX, int frameY)
{
	//�κ� �ٴ� ������
	if (frameX == 0 && frameY == 0)
	{
		return TR_LOBYBEAT_L;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return TR_LOBYBEAT_R;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 4 && frameY == 0)
	{
		return TR_LOBYNIGHT_L;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 6 && frameY == 0)
	{
		return TR_LOBYNIGHT_R;
	}

	//�κ� �ٴ� ������
	else if (frameX == 0 && frameY == 1)
	{
		return TR_MAP1BEAT_L;
	}

	else if (frameX == 2 && frameY == 1)
	{
		return TR_MAP1BEAT_R;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 4 && frameY == 1)
	{
		return TR_MAP1NIGHT_L;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 6 && frameY == 1)
	{
		return TR_MAP1NIGHT_R;
	}

	//�κ� �ٴ� ������
	else if (frameX == 0 && frameY == 2)
	{
		return TR_MAP2BEAT_L;
	}

	else if (frameX == 2 && frameY == 2)
	{
		return TR_MAP2BEAT_R;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 4 && frameY == 2)
	{
		return TR_MAP2NIGHT_L;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 6 && frameY == 2)
	{
		return TR_MAP2NIGHT_R;
	}

	//�κ� �ٴ� ������
	else if (frameX == 0 && frameY == 3)
	{
		return TR_MAP3BEAT_L;
	}

	else if (frameX == 2 && frameY == 3)
	{
		return TR_MAP3BEAT_R;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 4 && frameY == 3)
	{
		return TR_MAP3NIGHT_L;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 6 && frameY == 3)
	{
		return TR_MAP3NIGHT_R;
	}

	//�κ� �ٴ� ������
	else if (frameX == 0 && frameY == 4)
	{
		return TR_ICE;
	}

	else if (frameX == 3 && frameY == 4)
	{
		return TR_FIRE;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 6 && frameY == 4)
	{
		return TR_WATER;
	}

	//�κ� ����Ʈ ������
	else if (frameX == 7 && frameY == 4)
	{
		return TR_GOAL;
	}
}

OBJECT maptool::objSelect(int frameX, int frameY)
{
	//������
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_LEVEL3;
	}

	//�μ��� ������
	else if (frameX == 1 && frameY == 0)
	{
		return OBJ_BROKENLEVEL3;
	}

	//���
	else if (frameX == 2 && frameY == 0)
	{
		return OBJ_LEVEL2;
	}

	//�μ��� ���
	else if (frameX == 3 && frameY == 0)
	{
		return OBJ_BROKENLEVEL2;
	}

	//��
	else if (frameX == 4 && frameY == 0)
	{
		return OBJ_LEVEL1;
	}

	//�μ��� ��
	else if (frameX == 5 && frameY == 0)
	{
		return OBJ_BROKENLEVEL1;
	}

	//�Ķ���
	else if (frameX == 6 && frameY == 0)
	{
		return OBJ_LEVEL1;
	}

	//�μ��� �Ķ���
	else if (frameX == 7 && frameY == 0)
	{
		return OBJ_BROKENLEVEL1;
	}

	//���ذ� ��
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_LEVEL3;
	}
	//�ذ�ΰ� ��
	else if (frameX == 1 && frameY == 1)
	{
		return OBJ_LEVEL3;
	}
	//�ڰ���
	else if (frameX == 2 && frameY == 1)
	{
		return OBJ_LEVEL2;
	}
	//�μ��� �ڰ���
	else if (frameX == 3 && frameY == 1)
	{
		return OBJ_BROKENLEVEL2;
	}
	//�̳���
	else if (frameX == 4 && frameY == 1)
	{
		return OBJ_LEVEL2;
	}
	//�μ��� �̳���
	else if (frameX == 5 && frameY == 1)
	{
		return OBJ_BROKENLEVEL2;
	}
	//���� ��
	else if (frameX == 6 && frameY == 1)
	{
		return OBJ_LEVEL1;
	}
	//�μ��� ������
	else if (frameX == 7 && frameY == 1)
	{
		return OBJ_BROKENLEVEL1;
	}
	//����
	else if (frameX == 0 && frameY == 2)
	{
		return OBJ_LEVEL2;
	}
	//�μ��� ����
	else if (frameX == 1 && frameY == 2)
	{
		return OBJ_BROKENLEVEL2;
	}
	//��
	else if (frameX == 2 && frameY == 2)
	{
		return OBJ_LEVEL2;
	}
	//�μ��� ��
	else if (frameX == 3 && frameY == 2)
	{
		return OBJ_BROKENLEVEL2;
	}
	//���� ��
	else if (frameX == 4 && frameY == 2)
	{
		return OBJ_LEVEL3;
	}
	//���󷹺���
	else if (frameX == 5 && frameY == 2)
	{
		return OBJ_LEVEL2;
	}
	//�μ��� ���󷹺���
	else if (frameX == 6 && frameY == 2)
	{
		return OBJ_BROKENLEVEL2;
	}
}

void saveCallBack()
{
	_ctrSelect = CTRL_SAVE;
}

void loadCaalBack()
{
	_ctrSelect = CTRL_LOAD;
}

void objectCallBack()
{
	_ctrSelect = CTRL_OBJ;
}

void tileCallBack()
{
	_ctrSelect = CTRL_TILE;
}

void objDrawCallBack()
{
	_curSelect = CTRL_OBJDRAW;
}

void trDrawCallBack()
{
	_curSelect = CTRL_TERRAINDRAW;
}

void trEraserCallBack()
{
	_curSelect = CTRL_ERASER;
}

void objEraserCallBack()
{
	_curSelect = CTRL_ERASER;
}
