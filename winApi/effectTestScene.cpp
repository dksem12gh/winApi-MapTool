#include "stdafx.h"
#include "effectTestScene.h"

HRESULT effectTestScene::init(void)
{
	IMAGEMANAGER->addImage("FFX", "FFX.bmp", WINSIZEX, WINSIZEY);
	
	EFFECTMANAGER->addEffect("effectSample", "effectSample.bmp", 1040, 80, 80, 80, 10, 100);
	EFFECTMANAGER->addEffect("explosion", "explosion.bmp", 4355, 135, 335, 135, 8, 100);

	return S_OK;
}

void effectTestScene::release(void)
{
}

void effectTestScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		EFFECTMANAGER->play("effectSample", _ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("explosion", _ptMouse.x, _ptMouse.y);
	}

	EFFECTMANAGER->update();
}

void effectTestScene::render(void)
{
	IMAGEMANAGER->render("FFX", getMemDC());
	EFFECTMANAGER->render();
}
