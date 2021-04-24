#include "stdafx.h"
#include "beatManager.h"

HRESULT beatManager::init(void)
{
	setUp();

	return S_OK;
}

void beatManager::release(void)
{

}

void beatManager::update(void)
{
	_worldTimer = TIMEMANAGER->getWorldTime();

	if (_worldTimer - _timer >= 0.5f)
	{
		_baseBeat++;
		_timer = TIMEMANAGER->getWorldTime();
	}

	//비트확인
	cout << _baseBeat << endl;

	_heartAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	beatLode();
	beatAlpha();

}

void beatManager::render(HDC getmemDC)
{
	Rectangle(getmemDC, _heartBOX.left, _heartBOX.top, _heartBOX.right, _heartBOX.bottom);

	_heart->aniRender(getmemDC, _heartRC.left, _heartRC.top, _heartAni);

	for (int i = 0; i < 4; i++)
	{
		_heartBeat->alphaRender(getmemDC, _beatVec[i]._heartBeatRC.left, _beatVec[i]._heartBeatRC.top, _beatVec[i]._beatAlpha);
	}
}

void beatManager::setUp()
{
	_worldTimer = 0;
	_timer = 0;
	_baseBeat = 0;

	_heart = IMAGEMANAGER->findImage("heart");
	_heartBeat = IMAGEMANAGER->findImage("heartBeat");
	_redBeat = IMAGEMANAGER->findImage("redBeat");
	
	_heartAni = new animation;
	_heartAni->init(285,100,95,100);
	_heartAni->setFPS(3);
	_heartAni->setPlayFrame(0, 2, false, true);
	_heartAni->start();

	_heartRC = RectMakeCenter(660, 550, 95, 100);
	_heartBOX = RectMakeCenter(620, 550, 60, 100);

	
	//비트노트 왼쪽 그리기,충돌처리 셋팅
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			_beat[i]._beatX = 0;
			_beat[i]._beatAlpha = 0;

			_beat[i]._heartBeatRC = RectMakeCenter(_beat[i]._beatX, 560, 16, 70);
			_beatVec.push_back(_beat[i]);
		}
		else if (i == 1)
		{
			_beat[i]._beatX = -200;
			_beat[i]._beatAlpha = 0;

			_beat[i]._heartBeatRC = RectMakeCenter(_beat[i]._beatX, 560, 16, 70);
			_beatVec.push_back(_beat[i]);
		}
		else if (i == 2)
		{
			_beat[i]._beatX = -400;
			_beat[i]._beatAlpha = 0;

			_beat[i]._heartBeatRC = RectMakeCenter(_beat[i]._beatX, 560, 16, 70);
			_beatVec.push_back(_beat[i]);
		}
		else if (i == 3)
		{
			_beat[i]._beatX = -600;
			_beat[i]._beatAlpha = 0;

			_beat[i]._heartBeatRC = RectMakeCenter(_beat[i]._beatX, 560, 16, 70);
			_beatVec.push_back(_beat[i]);
		}
	}
}

void beatManager::beatLode()
{
	for (int i = 0; i < _beatVec.size(); i++)
	{
		_beatVec[i]._beatX += BEATSPEED;
		_beatVec[i]._beatAlpha += 10;
		_beatVec[i]._heartBeatRC = RectMakeCenter(_beatVec[i]._beatX, 560, 16, 70);
		//_beat[i]._beatX += BEATSPEED;
		//_beat[i]._beatAlpha += 10;
		//_beat[i]._heartBeatRC = RectMakeCenter(_beat[i]._beatX, 560, 16, 70);

		if (IntersectRect(&_beatAttackRc, &_beat[i]._heartBeatRC, &_heartBOX))
		{
			_beat[i]._beatX = -200;
			_beat[i]._beatAlpha = 0;
		}
	}

	//for (int i = 0; i < _beatVec.size(); i++)
	//{
	//	if (_beatAlpha[i] >= 255)
	//	{
	//		_beatAlpha[i] = 255;
	//	}
	//}

	//for (int i = 0; i < _beatVec.size(); i++)
	//{
	//}
	//_beatAlpha[i] = 255;
}

void beatManager::beatAlpha()
{
	//for (int i = 0; i < _beatVec.size(); i++)
	//{
	//	if (_beatAlpha[i] >= 255)
	//	{
	//		_beatAlpha[i] = 255;
	//	}
	//}
}
