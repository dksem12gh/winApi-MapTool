#include "stdafx.h"
#include "loadingScene.h"
#include "start.h"

HRESULT loadingScene::init(void)
{


	_loading = new loading;
	_loading->init();

	SCENEMANAGER->addScene("시작", new start);

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 완료되면 씬 변경
		SCENEMANAGER->changeScene("시작");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

//로딩이미지 함수
void loadingScene::loadingImage(void)
{
	for (int i = 0; i < 5; i++)
	{
		//_loading->loadImage()
		//_loading->loadFrameImage()

		//이미지
		//맵툴 배경
		_loading->loadImage("back", "image/back.bmp", WINSIZEX, WINSIZEY);

		//스타트씬 배경
		_loading->loadImage("bg1", "image/bg1.bmp", WINSIZEX, WINSIZEY);

		//프레임이미지
		//타일맵
		_loading->loadFrameImage("tilemap", "image/map11.bmp", 400, 250, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
		_loading->loadFrameImage("tilemap2", "image/map2.bmp", 400, 243, OBJTILEX, OBJTILEY, true, RGB(255, 0, 255));

		//맵툴 콜백 버튼 이미지
		_loading->loadFrameImage("save", "image/save.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("load", "image/lode.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("object", "image/object.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("terrain", "image/terrain.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("drawtr", "image/draw.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("drawobj", "image/draw.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("erasertr", "image/eraser.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("eraserobj", "image/eraser.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));

		//플레이어
		_loading->loadFrameImage("head", "image/head.bmp", 320, 35, 8, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("body", "image/body.bmp", 320, 240, 8, 6, true, RGB(255, 0, 255));
		//그림자
		_loading->loadImage("playerShadow", "image/shadow.bmp", 40, 13, true, RGB(255, 0, 255));

		//캔유빝마핱ㅌ비트
		_loading->loadFrameImage("heart", "image/heart.bmp", 285, 100,1, 3,true,RGB(255,0,255));
		_loading->loadFrameImage("heartBeat", "image/heartBeat.bmp", 16, 70, 1, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("redBeat", "image/redBeat.bmp", 16, 60, 1, 1, true, RGB(255, 0, 255));

		//카메라
		_loading->loadImage("camera1", "image/camera1.bmp", 350, 350, true, RGB(255, 0, 255));
		_loading->loadImage("camera2", "image/camera2.bmp", 550, 550, true, RGB(255, 0, 255));
		_loading->loadImage("camera3", "image/camera3.bmp", 750, 750, true, RGB(255, 0, 255));
		_loading->loadImage("camera4", "image/camera4.bmp", 950, 950, true, RGB(255, 0, 255));

		//몬스터 이미지

	} 
}

//로딩사운드 함수
void loadingScene::loadingSound(void)
{
}
