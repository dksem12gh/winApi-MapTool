#include "stdafx.h"
#include "buttonTestScene.h"

HRESULT buttonTestScene::init(void)
{
	IMAGEMANAGER->addFrameImage("Button", "Button.bmp", 348, 43, 2, 1);

	_button = new button;
	_button->init("Button", WINSIZEX / 2 - 350, WINSIZEY / 2,
		PointMake(1, 0), PointMake(0, 0), buttonDown);

	return S_OK;
}

void buttonTestScene::release(void)
{
	_button->release();
}

void buttonTestScene::update(void)
{
	_button->update();
}

void buttonTestScene::render(void)
{
	_button->render();
}

void buttonTestScene::buttonDown(void)
{
}