#include "stdafx.h"
#include "button.h"

HRESULT button::init(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint)
{
	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

HRESULT button::init(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACKFUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACKFUNCTION>(cbFunction);

	this->init(imageName, x, y, btnDownFramePoint,
		btnUpFramePoint);

	return S_OK;
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnCollisonFramePoint, CALLBACKFUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACKFUNCTION>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;
	_btnCollisonFramePoint = btnCollisonFramePoint;
	
	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void button::release(void)
{
}

void button::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (_leftButtonDown) _direction = BUTTONDIRECTION_DOWN;
				
		else if (!_leftButtonDown && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			if (_callbackFunction != NULL) _callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void button::render(void)
{
	switch (_direction)
	{
	case BUTTONDIRECTION_UP: case BUTTONDIRECTION_NULL:
		_image->frameRender(getMemDC(), _rc.left, _rc.top,
			_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;

	case BUTTONDIRECTION_DOWN:
		_image->frameRender(getMemDC(), _rc.left, _rc.top,
			_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	}
}