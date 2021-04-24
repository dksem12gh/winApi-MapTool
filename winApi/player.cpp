#include "stdafx.h"
#include "player.h"

HRESULT player::init(mapLode* mapLoad)
{
	i = 0;
	_playerPt.x = 0;
	_playerPt.y = 0;

	_mapLd = mapLoad;

	_playerHead = IMAGEMANAGER->findImage("head");
	_playerBody = IMAGEMANAGER->findImage("body");
	_playerShadow = IMAGEMANAGER->findImage("playerShadow");


	_direction = PLAYERDIRECTION_RIGHT;
	_playerUD = PLAYERDIRECTION_NONE;

	i = 391;

	_playerPt.x = _mapLd->getTiles()[i].rc.right - _mapLd->getTiles()[i].rc.left/2;
	_playerPt.y = _mapLd->getTiles()[i].rc.bottom - _mapLd->getTiles()[i].rc.top/2+30;

	dansingBase(_playerPt);
	setPlayerPosition();

	int tile = 10;

	return S_OK;
}

void player::release(void)
{

}

void player::update()
{

	//_bodyDansingRight->frameUpdate(GetTickCount());
	//_headBangingRight->frameUpdate(GetTickCount());
	//_bodyDansingLeft->frameUpdate(GetTickCount());
	//_headBangingLeft->frameUpdate(GetTickCount());

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_direction = PLAYERDIRECTION_RIGHT;
		dansingLR();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_direction = PLAYERDIRECTION_LEFT;
		dansingLR();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_playerUD = PLAYERDIRECTION_DOWN;
		dansingUD();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_playerUD = PLAYERDIRECTION_UP;
		dansingUD();
	}

	//аб
	_probe[0] = RectMakeCenter(_playerPt.x - 10, _playerPt.y + 20, 20, 20);
	//©Л
	_probe[1] = RectMakeCenter(_playerPt.x + 60, _playerPt.y + 20, 20, 20);
	//╩С
	_probe[2] = RectMakeCenter(_playerPt.x + 25, _playerPt.y - 16, 20, 20);
	//го
	_probe[3] = RectMakeCenter(_playerPt.x + 25, _playerPt.y + 55, 20, 20);

	_rcBody = RectMake(_playerPt.x, _playerPt.y, _playerBody->getFrameWidth(), _playerBody->getFrameHeight());
	_rcHead = RectMake(_playerPt.x, _playerPt.y - 29, _playerHead->getFrameWidth(), _playerHead->getFrameHeight());
	_rcShadow = RectMake(_playerPt.x, _playerPt.y + 26, _playerShadow->getWidth(), _playerShadow->getHeight());

	_bodyDansingRight->frameUpdate(TIMEMANAGER->getElapsedTime());
	_headBangingRight->frameUpdate(TIMEMANAGER->getElapsedTime());
	_bodyDansingLeft->frameUpdate(TIMEMANAGER->getElapsedTime());
	_headBangingLeft->frameUpdate(TIMEMANAGER->getElapsedTime());

	LEVELCAMERA->setCameraPt(_playerPt);
	LEVELCAMERA->update();
}

void player::render()
{
	switch (_direction)
	{
	case PLAYERDIRECTION_RIGHT:
	{
		if (_playerUD == PLAYERDIRECTION_NONE)
		{
			_playerShadow->render(getMemDC(), _rcShadow.left-LEVELCAMERA->getCameraPt().x, _rcShadow.top - LEVELCAMERA->getCameraPt().y);
			_playerBody->aniRender(getMemDC(), _rcBody.left - LEVELCAMERA->getCameraPt().x, _rcBody.top - LEVELCAMERA->getCameraPt().y,_bodyDansingRight);
			_playerHead->aniRender(getMemDC(), _rcHead.left - LEVELCAMERA->getCameraPt().x,_rcHead.top - LEVELCAMERA->getCameraPt().y, _headBangingRight);
		}
		else if (_playerUD == PLAYERDIRECTION_UP)
		{
			_playerShadow->render(getMemDC(), _rcShadow.left - LEVELCAMERA->getCameraPt().x, _rcShadow.top - LEVELCAMERA->getCameraPt().y);
			_playerBody->aniRender(getMemDC(), _rcBody.left - LEVELCAMERA->getCameraPt().x, _rcBody.top - LEVELCAMERA->getCameraPt().y, _bodyDansingRight);
			_playerHead->aniRender(getMemDC(), _rcHead.left - LEVELCAMERA->getCameraPt().x, _rcHead.top - LEVELCAMERA->getCameraPt().y, _headBangingRight);
		}
		else if (_playerUD == PLAYERDIRECTION_DOWN)
		{
			_playerShadow->render(getMemDC(), _rcShadow.left - LEVELCAMERA->getCameraPt().x, _rcShadow.top - LEVELCAMERA->getCameraPt().y);
			_playerBody->aniRender(getMemDC(), _rcBody.left - LEVELCAMERA->getCameraPt().x, _rcBody.top - LEVELCAMERA->getCameraPt().y, _bodyDansingRight);
			_playerHead->aniRender(getMemDC(), _rcHead.left - LEVELCAMERA->getCameraPt().x, _rcHead.top - LEVELCAMERA->getCameraPt().y, _headBangingRight);
		}
	}
		break;
	case PLAYERDIRECTION_LEFT:
	{
		if (_playerUD == PLAYERDIRECTION_NONE)
		{
			_playerShadow->render(getMemDC(), _rcShadow.left - LEVELCAMERA->getCameraPt().x, _rcShadow.top - LEVELCAMERA->getCameraPt().y);
			_playerBody->aniRender(getMemDC(), _rcBody.left - LEVELCAMERA->getCameraPt().x, _rcBody.top - LEVELCAMERA->getCameraPt().y, _bodyDansingLeft);
			_playerHead->aniRender(getMemDC(), _rcHead.left - LEVELCAMERA->getCameraPt().x, _rcHead.top - LEVELCAMERA->getCameraPt().y, _headBangingLeft);
		}
		else if (_playerUD == PLAYERDIRECTION_UP)
		{
			_playerShadow->render(getMemDC(), _rcShadow.left - LEVELCAMERA->getCameraPt().x, _rcShadow.top - LEVELCAMERA->getCameraPt().y);
			_playerBody->aniRender(getMemDC(), _rcBody.left - LEVELCAMERA->getCameraPt().x, _rcBody.top - LEVELCAMERA->getCameraPt().y, _bodyDansingLeft);
			_playerHead->aniRender(getMemDC(), _rcHead.left - LEVELCAMERA->getCameraPt().x, _rcHead.top - LEVELCAMERA->getCameraPt().y, _headBangingLeft);
		}
		else if (_playerUD == PLAYERDIRECTION_DOWN)
		{
			_playerShadow->render(getMemDC(), _rcShadow.left - LEVELCAMERA->getCameraPt().x, _rcShadow.top - LEVELCAMERA->getCameraPt().y);
			_playerBody->aniRender(getMemDC(), _rcBody.left - LEVELCAMERA->getCameraPt().x, _rcBody.top - LEVELCAMERA->getCameraPt().y, _bodyDansingLeft);
			_playerHead->aniRender(getMemDC(), _rcHead.left - LEVELCAMERA->getCameraPt().x, _rcHead.top - LEVELCAMERA->getCameraPt().y, _headBangingLeft);
		}
	}
		break;
	default:
		break;
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	Rectangle(getMemDC(), _probe[i].left, _probe[i].top, _probe[i].right, _probe[i].bottom);
	//}
}

void player::setPlayerPosition()
{
	//аб
	_probe[0] = RectMakeCenter(_playerPt.x - 10,_playerPt.y+ 20,20,20);
	//©Л
	_probe[1] = RectMakeCenter(_playerPt.x + 60, _playerPt.y + 20, 20, 20);
	//╩С
	_probe[2] = RectMakeCenter(_playerPt.x+25, _playerPt.y - 55, 40, 20);
	//го
	_probe[3] = RectMakeCenter(_playerPt.x + 25, _playerPt.y + 60, 20, 20);
}

void player::dansingLR()
{
	RECT tempRc;
	switch (_direction)
	{
	case PLAYERDIRECTION_RIGHT:
	{
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			if (IntersectRect(&tempRc, &_probe[1], &_mapLd->getObj()[i].rc))
			{
				if (_mapLd->getAttribute()[i] == ATTR_LEVEL1)
				{
					_playerPt.x = _playerPt.x;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL2)
				{
					_playerPt.x = _playerPt.x;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL3)
				{
					_playerPt.x = _playerPt.x;
				}
				else
				{
					_playerPt.x += 50;
				}
			}
		}
	}
	break;
	case PLAYERDIRECTION_LEFT:
	{
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			if (IntersectRect(&tempRc, &_probe[0], &_mapLd->getObj()[i].rc))
			{
				if (_mapLd->getAttribute()[i] == ATTR_LEVEL1)
				{
					_playerPt.x = _playerPt.x;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL2)
				{
					_playerPt.x = _playerPt.x;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL3)
				{
					_playerPt.x = _playerPt.x;
				}
				else
				{
					_playerPt.x -= 50;
				}
			}
		}
	}
		break;
		
	default:
		break;
	}

	_playerUD = PLAYERDIRECTION_NONE;
}

void player::dansingUD()
{
	RECT tempRc;
	switch (_playerUD)
	{
	case PLAYERDIRECTION_UP:
	{
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			if (IntersectRect(&tempRc, &_probe[2], &_mapLd->getObj()[i].rc))
			{
				if (_mapLd->getAttribute()[i] == ATTR_LEVEL1)
				{
					_playerPt.y = _playerPt.y;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL2)
				{
					_playerPt.y = _playerPt.y;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL3)
				{
					_playerPt.y = _playerPt.y;
				}
				else
				{
					_playerPt.y -= 50;
				}
			}
		}
	}
	break;
	case PLAYERDIRECTION_DOWN:
	{
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			if (IntersectRect(&tempRc, &_probe[3], &_mapLd->getObj()[i].rc))
			{
				if (_mapLd->getAttribute()[i] == ATTR_LEVEL1)
				{
					_playerPt.y = _playerPt.y;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL2)
				{
					_playerPt.y = _playerPt.y;
				}
				else if (_mapLd->getAttribute()[i] == ATTR_LEVEL3)
				{
					_playerPt.y = _playerPt.y;
				}
				else
				{
					_playerPt.y += 50;
				}
			}
		}
	}
	break;

	default:
		break;
	}
}

void player::dansingBase(POINT _pt)
{
	_rcBody = RectMake(_pt.x, _pt.y, _playerBody->getFrameWidth(), _playerBody->getFrameHeight());
	_rcHead = RectMake(_pt.x, _pt.y - 22, _playerHead->getFrameWidth(), _playerHead->getFrameHeight());
	_rcShadow = RectMake(_pt.x, _pt.y + 40, _playerShadow->getWidth(), _playerShadow->getHeight());

	_bodyDansingRight = new animation;
	_bodyDansingRight->init(320, 240, 40, 40);
	_bodyDansingRight->setFPS(FPS);
	_bodyDansingRight->setPlayFrame(0, 3, false, true);
	_bodyDansingRight->start();

	_bodyDansingLeft = new animation;
	_bodyDansingLeft->init(320, 240, 40, 40);
	_bodyDansingLeft->setFPS(FPS);
	_bodyDansingLeft->setPlayFrame(4, 7, false, true);
	_bodyDansingLeft->start();

	_headBangingRight = new animation;
	_headBangingRight->init(320, 35, 40, 35);
	_headBangingRight->setFPS(FPS);
	_headBangingRight->setPlayFrame(0, 3, false, true);
	_headBangingRight->start();

	_headBangingLeft = new animation;
	_headBangingLeft->init(320, 35, 40, 35);
	_headBangingLeft->setFPS(FPS);
	_headBangingLeft->setPlayFrame(4, 7, false, true);
	_headBangingLeft->start();

	speed = 0;
}

void player::blockOn()
{
	RECT temp;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//if(IntersectRect(&temp,))

	}

}
