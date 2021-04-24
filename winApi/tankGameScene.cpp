#include "stdafx.h"
#include "tankGameScene.h"

HRESULT tankGameScene::init(void)
{
	_tankMap = new tankMap;
	_tankMap->init();

	_tank = new tank;
	_tank->init();
	_tank->setTankMapMemoryLink(_tankMap);
	_tank->setTankPosition();

	return S_OK;
}

void tankGameScene::release(void)
{
	SAFE_DELETE(_tankMap);
	SAFE_DELETE(_tank);
}

void tankGameScene::update(void)
{
	_tankMap->update();
	_tank->update();
}

void tankGameScene::render(void)
{
	_tankMap->render();
	_tank->render();
}