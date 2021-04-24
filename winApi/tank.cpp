#include "stdafx.h"
#include "tank.h"

HRESULT tank::init(void)
{
	//탱크 방향 초기화
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "TileMapTank.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	
	_speed = 100.0f;

	return S_OK;
}

void tank::release(void)
{
}

void tank::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		tankMove();
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void tank::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void tank::tankMove()
{
	RECT rcCollision;	//충돌 렉트
	int tileIndex[2];	//타일 인덱스
	int tileX, tileY;	//타일 x,y
	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		_image->setFrameX(1);
		_x -= moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

	case TANKDIRECTION_RIGHT:
		_image->setFrameX(2);
		_x += moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

	case TANKDIRECTION_UP:
		_image->setFrameX(3);
		_y -= moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

	case TANKDIRECTION_DOWN:
		_image->setFrameX(0);
		_y += moveSpeed;
		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}

	//탱크 렉트가 레프트 탑의 위치가 1, 40이면 1 / 32 = 0, 40/32 = 1;
	//현재 타일에서의 위치는 x = 0 , y = 1
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;
	
	//탱크가 타일 어디에 있는지 확인이 가능하니
	//탱크 방향에 따라서 그 앞의 타일 번호를 계산
	//인덱스 번호가 2개인 이유는 렉트의 레프트,탑 위치로 탱크의 위치를 구하고
	//그러면 렉트의 레프트, 탑이 타일번호에 걸쳐져 있을수도, 딱 맞게 있을수도 있기 때문에
	//걸쳐져 있을 경우 걸친 그 밑의 타일의 값(EX: 오른쪽 버튼일 경우 탱크 위치 밑에 있는 값 앞에 있는 타일)을 가져온다
	//그래서 정확하게 걸치지 않았을때 통과 할수 있도록

	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;				//탱크가 밟고있는 인덱스
		tileIndex[1] = tileX + (tileY + 1) * TILEX;			//탱크 밟고있는 인덱스 왼쪽
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;			//탱크가 밟고있는 인덱스
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;	//탱크 밟고있는 인덱스 오른쪽
		break;
	case TANKDIRECTION_UP:
		tileIndex[0] = tileX + tileY * TILEY;
		tileIndex[1] = tileX + 1 + tileY * TILEX;
		break;
	case TANKDIRECTION_DOWN:
		tileIndex[0] = (tileX + tileY * TILEY) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	}

	//어떤타일인지 검사
	//현재는 물일 경우 충돌했는지 검사
	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			IntersectRect(&rc, &_tankMap->getTiles()[tileIndex[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
				//움직이려 할때 갈수 없는 지역이면 탱크의 움직임을 고정시킴
				//EX: 탱크가 왼쪽으로 갈때 왼쪽지역이 갈수 없으면
			case TANKDIRECTION_LEFT:
				_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;				//왼쪽 타일의 라이트의 위치를 탱크의 래프트의 위치로 고정
				_rc.right = _rc.left + _image->getFrameWidth();						//탱크크기만큼
				_x = _rc.left + (_rc.right - _rc.left) / 2;							//탱크 x의 위치를 계산한 탱크 렉트의 위치값으로 설정(중앙으로)
				break;

			case TANKDIRECTION_RIGHT:
				_rc.right = _tankMap->getTiles()[tileIndex[i]].rc.left;
				_rc.left = _rc.right - _image->getFrameWidth();			
				_x = _rc.left + (_rc.right - _rc.left) / 2;				
				break;

			case TANKDIRECTION_UP:
				_rc.top = _tankMap->getTiles()[tileIndex[i]].rc.bottom;
				_rc.bottom = _rc.top + _image->getFrameHeight();		
				_y = _rc.top + (_rc.bottom - _rc.top) / 2;				
				break;

			case TANKDIRECTION_DOWN:
				_rc.bottom = _tankMap->getTiles()[tileIndex[i]].rc.top;
				_rc.top = _rc.bottom - _image->getFrameHeight();		
				_y = _rc.top + (_rc.bottom - _rc.top) / 2;				
				break;
			}
		}
	}

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_rc = rcCollision;
}

void tank::setTankPosition()
{
	_rc = _tankMap->getTiles()[_tankMap->getPosFirst()].rc;
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}