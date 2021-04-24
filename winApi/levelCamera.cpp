#include "stdafx.h"
#include "levelCamera.h"

HRESULT levelCamera::init(void)
{
	_camera1 = IMAGEMANAGER->findImage("camera1");
	_camera2 = IMAGEMANAGER->findImage("camera2");
	_camera3 = IMAGEMANAGER->findImage("camera3");
	_camera4 = IMAGEMANAGER->findImage("camera4");

	_camera = RectMakeCenter(WINDOWSX, WINDOWSY, IMAGEMANAGER->findImage("camera4")->getWidth(), IMAGEMANAGER->findImage("camera4")->getHeight());
	_level[0] = RectMakeCenter(WINDOWSX, WINDOWSY, IMAGEMANAGER->findImage("camera3")->getWidth(), IMAGEMANAGER->findImage("camera3")->getHeight());
	_level[1] = RectMakeCenter(WINDOWSX, WINDOWSY, IMAGEMANAGER->findImage("camera2")->getWidth(), IMAGEMANAGER->findImage("camera2")->getHeight());
	_level[2] = RectMakeCenter(WINDOWSX, WINDOWSY, IMAGEMANAGER->findImage("camera1")->getWidth(), IMAGEMANAGER->findImage("camera1")->getHeight());

	_sublight = 255.0f;

	cameraSet();

	return S_OK;
}

void levelCamera::release(void)
{

}

void levelCamera::update(void)
{
	cameraLevel(1);
}

void levelCamera::render(HDC getmemDC)
{
	_camera1->alphaRender(getmemDC, _level[2].left-1, _level[2].top, _Light[0]);
	_camera2->alphaRender(getmemDC, _level[1].left-1, _level[1].top, _Light[1]);
	_camera3->alphaRender(getmemDC, _level[0].left-1, _level[0].top, _Light[2]);
	_camera4->alphaRender(getmemDC, _camera.left-1, _camera.top, _Light[3]);
}

void levelCamera::cameraSet()
{
	_camera = RectMakeCenter(_cameraPt.x, _cameraPt.y, IMAGEMANAGER->findImage("camera4")->getWidth(), IMAGEMANAGER->findImage("camera4")->getHeight());

	_level[0] = RectMakeCenter(WINDOWSX + 36, WINDOWSY + 20, IMAGEMANAGER->findImage("camera3")->getWidth(), IMAGEMANAGER->findImage("camera3")->getHeight());
	_level[1] = RectMakeCenter(WINDOWSX + 36, WINDOWSY + 20, IMAGEMANAGER->findImage("camera2")->getWidth(), IMAGEMANAGER->findImage("camera2")->getHeight());
	_level[2] = RectMakeCenter(WINDOWSX + 36, WINDOWSY + 20, IMAGEMANAGER->findImage("camera1")->getWidth(), IMAGEMANAGER->findImage("camera1")->getHeight());
	_camera = RectMakeCenter(WINDOWSX + 36, WINDOWSY + 20, IMAGEMANAGER->findImage("camera4")->getWidth(), IMAGEMANAGER->findImage("camera4")->getHeight());
}

void levelCamera::cameraLevel(int light)
{
	switch (light)
	{
	case 1:
	{
		_Light[0] = _sublight - 155.0f;
		_Light[1] = _sublight - 75.0f;
		_Light[2] = _sublight - 35.0f;
		_Light[3] = _sublight - 15.0f;
	}
		break;

	case 2:
	{

	}
		break;

	case 3:
	{

	}
		break;

	case 4:
	{

	}
		break;
	default:
		break;
	}
}


