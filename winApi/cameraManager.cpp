#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init(void)
{
	this->maptoolCamera();
	return S_OK;
}

void cameraManager::release(void)
{

}

void cameraManager::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cameraPoint.y+=4;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraPoint.x+= 4;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cameraPoint.x-= 4;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cameraPoint.y-=4;
	}
}

void cameraManager::render(void)
{
	
}

void cameraManager::maptoolCamera()
{
	_cameraPoint.x = 0;
	_cameraPoint.y = 0;

	_cameraW = 600;
	_cameraH = 620;



	_rc = RectMake(_cameraPoint.x, _cameraPoint.y, _cameraW, _cameraH);
}

