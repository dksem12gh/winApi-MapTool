#include "stdafx.h"
#include "enemy.h"

enemy::enemy() : _currentFrameX(0),
				 _currentFrameY(0),
				 _x(0.0f),
				 _y(0.0f),
				 _rc(RectMake(0, 0, 0, 0)),
				 _worldTimeCount(0.0f),
				 _rndTimeCount(0.0f)
{
}


HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y,
		_image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	move();
}

void enemy::render(void)
{
	draw();
	animation();
}

//에너미마다 움직임이 틀리니 상속받아 자식에서 구현
void enemy::move(void)
{
}

void enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void enemy::animation(void)
{
	//if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	//{
	//	_worldTimeCount = GetTickCount();
	//	_currentFrameX++;
	//	if (_image->getMaxFrameX() < _currentFrameX)
	//	{
	//		_currentFrameX = 0;
	//	}
	//}

	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}

bool enemy::bulletCountFire(void)
{
	if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);
		return true;
	}
	return false;
}
