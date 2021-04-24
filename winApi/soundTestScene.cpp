#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init(void)
{
	IMAGEMANAGER->addImage("FFX", "FFX.bmp", WINSIZEX, WINSIZEY);
	SOUNDMANAGER->addSound("Serah", "star.mp3", true, true);

	return S_OK;
}

void soundTestScene::release(void)
{
}

void soundTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("Serah", 0.2f);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("Serah");
	}
	 
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		SOUNDMANAGER->pause("Serah");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->resume("Serah");
	}

	SOUNDMANAGER->update();
}

void soundTestScene::render(void)
{
	IMAGEMANAGER->render("FFX", getMemDC());
}
