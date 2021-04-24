#include "stdafx.h"
#include "tank.h"

HRESULT tank::init(void)
{
	//��ũ ���� �ʱ�ȭ
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
	RECT rcCollision;	//�浹 ��Ʈ
	int tileIndex[2];	//Ÿ�� �ε���
	int tileX, tileY;	//Ÿ�� x,y
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

	//��ũ ��Ʈ�� ����Ʈ ž�� ��ġ�� 1, 40�̸� 1 / 32 = 0, 40/32 = 1;
	//���� Ÿ�Ͽ����� ��ġ�� x = 0 , y = 1
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;
	
	//��ũ�� Ÿ�� ��� �ִ��� Ȯ���� �����ϴ�
	//��ũ ���⿡ ���� �� ���� Ÿ�� ��ȣ�� ���
	//�ε��� ��ȣ�� 2���� ������ ��Ʈ�� ����Ʈ,ž ��ġ�� ��ũ�� ��ġ�� ���ϰ�
	//�׷��� ��Ʈ�� ����Ʈ, ž�� Ÿ�Ϲ�ȣ�� ������ ��������, �� �°� �������� �ֱ� ������
	//������ ���� ��� ��ģ �� ���� Ÿ���� ��(EX: ������ ��ư�� ��� ��ũ ��ġ �ؿ� �ִ� �� �տ� �ִ� Ÿ��)�� �����´�
	//�׷��� ��Ȯ�ϰ� ��ġ�� �ʾ����� ��� �Ҽ� �ֵ���

	switch (_direction)
	{
	case TANKDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;				//��ũ�� ����ִ� �ε���
		tileIndex[1] = tileX + (tileY + 1) * TILEX;			//��ũ ����ִ� �ε��� ����
		break;
	case TANKDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX) + 1;			//��ũ�� ����ִ� �ε���
		tileIndex[1] = (tileX + (tileY + 1) * TILEX) + 1;	//��ũ ����ִ� �ε��� ������
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

	//�Ÿ������ �˻�
	//����� ���� ��� �浹�ߴ��� �˻�
	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			IntersectRect(&rc, &_tankMap->getTiles()[tileIndex[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
				//�����̷� �Ҷ� ���� ���� �����̸� ��ũ�� �������� ������Ŵ
				//EX: ��ũ�� �������� ���� ���������� ���� ������
			case TANKDIRECTION_LEFT:
				_rc.left = _tankMap->getTiles()[tileIndex[i]].rc.right;				//���� Ÿ���� ����Ʈ�� ��ġ�� ��ũ�� ����Ʈ�� ��ġ�� ����
				_rc.right = _rc.left + _image->getFrameWidth();						//��ũũ�⸸ŭ
				_x = _rc.left + (_rc.right - _rc.left) / 2;							//��ũ x�� ��ġ�� ����� ��ũ ��Ʈ�� ��ġ������ ����(�߾�����)
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