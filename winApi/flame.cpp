#include "stdafx.h"
#include "flame.h"

HRESULT flame::init(const char * imageName, float * x, float * y)
{
	_image = IMAGEMANAGER->addFrameImage("flame", "flame.bmp", 0.0f, 0.0f, 432, 297, 9, 1, true, RGB(255, 0, 255));

	_x = x;
	_y = y;

	_rc = RectMakeCenter((int)_x, (int)_y, _image->getFrameWidth(), _image->getFrameHeight());

	_flameCount = 7.0f;

	return S_OK;
}

void flame::release(void)
{
}

void flame::update(void)
{
	if (FLAMECOUNT + _flameCount <= GetTickCount())
	{
		_flameCount = GetTickCount();
		_image->setFrameX(_image->getFrameX() + 1);
		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}

	_rc = RectMakeCenter(*_x, *_y + 180, _image->getFrameWidth(),
		_image->getFrameHeight());
}

void flame::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_image->getFrameX(), _image->getFrameY());
}
