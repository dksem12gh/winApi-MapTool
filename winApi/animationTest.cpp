#include "stdafx.h"
#include "animationTest.h"


HRESULT animationTest::init(void)
{
	gameNode::init();

	_image = IMAGEMANAGER->addImage("elephant", "elephant.bmp", 660, 268, true, RGB(255, 0, 255));

	_animation0 = new animation;
	_animation0->init(_image->getWidth(), _image->getHeight(), 110, 67);
	_animation0->setDefPlayFrame(false, true);
	_animation0->setFPS(12);

	int arrAni[] = { 5, 11, 1, 3, 9 };
	_animation1 = new animation;
	_animation1->init(_image->getWidth(), _image->getHeight(), 110, 67);
	_animation1->setPlayFrame(arrAni, 5, true);
	_animation1->setFPS(1);

	_animation2 = new animation;
	_animation2->init(_image->getWidth(), _image->getHeight(), 110, 67);
	_animation2->setPlayFrame(11, 5, true, true);
	_animation2->setFPS(4);

	return S_OK;
}

void animationTest::release(void)
{
	_animation0->release();
	SAFE_DELETE(_animation0);

	_animation1->release();
	SAFE_DELETE(_animation1);

	_animation2->release();
	SAFE_DELETE(_animation2);
}

void animationTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_animation0->start();
		_animation1->start();
		_animation2->start();
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_animation0->stop();
		_animation1->stop();
		_animation2->stop();
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_animation0->pause();
		_animation1->pause();
		_animation2->pause();
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_animation0->resume();
		_animation1->resume();
		_animation2->resume();
	}

	_animation0->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_animation1->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_animation2->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void animationTest::render(void)
{
	_image->aniRender(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2, _animation0);
	_image->aniRender(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, _animation1);
	_image->aniRender(getMemDC(), WINSIZEX / 2 + 100, WINSIZEY / 2, _animation2);
}

