#include "stdafx.h"
#include "loadingScene.h"
#include "start.h"

HRESULT loadingScene::init(void)
{


	_loading = new loading;
	_loading->init();

	SCENEMANAGER->addScene("����", new start);

	//�̹��� �� ���� �ε�
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
		//�ε��� �Ϸ�Ǹ� �� ����
		SCENEMANAGER->changeScene("����");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

//�ε��̹��� �Լ�
void loadingScene::loadingImage(void)
{
	for (int i = 0; i < 5; i++)
	{
		//_loading->loadImage()
		//_loading->loadFrameImage()

		//�̹���
		//���� ���
		_loading->loadImage("back", "image/back.bmp", WINSIZEX, WINSIZEY);

		//��ŸƮ�� ���
		_loading->loadImage("bg1", "image/bg1.bmp", WINSIZEX, WINSIZEY);

		//�������̹���
		//Ÿ�ϸ�
		_loading->loadFrameImage("tilemap", "image/map11.bmp", 400, 250, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
		_loading->loadFrameImage("tilemap2", "image/map2.bmp", 400, 243, OBJTILEX, OBJTILEY, true, RGB(255, 0, 255));

		//���� �ݹ� ��ư �̹���
		_loading->loadFrameImage("save", "image/save.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("load", "image/lode.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("object", "image/object.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("terrain", "image/terrain.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("drawtr", "image/draw.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("drawobj", "image/draw.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("erasertr", "image/eraser.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("eraserobj", "image/eraser.bmp", 300, 30, 2, 1, true, RGB(255, 0, 255));

		//�÷��̾�
		_loading->loadFrameImage("head", "image/head.bmp", 320, 35, 8, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("body", "image/body.bmp", 320, 240, 8, 6, true, RGB(255, 0, 255));
		//�׸���
		_loading->loadImage("playerShadow", "image/shadow.bmp", 40, 13, true, RGB(255, 0, 255));

		//ĵ�������I����Ʈ
		_loading->loadFrameImage("heart", "image/heart.bmp", 285, 100,1, 3,true,RGB(255,0,255));
		_loading->loadFrameImage("heartBeat", "image/heartBeat.bmp", 16, 70, 1, 1, true, RGB(255, 0, 255));
		_loading->loadFrameImage("redBeat", "image/redBeat.bmp", 16, 60, 1, 1, true, RGB(255, 0, 255));

		//ī�޶�
		_loading->loadImage("camera1", "image/camera1.bmp", 350, 350, true, RGB(255, 0, 255));
		_loading->loadImage("camera2", "image/camera2.bmp", 550, 550, true, RGB(255, 0, 255));
		_loading->loadImage("camera3", "image/camera3.bmp", 750, 750, true, RGB(255, 0, 255));
		_loading->loadImage("camera4", "image/camera4.bmp", 950, 950, true, RGB(255, 0, 255));

		//���� �̹���

	} 
}

//�ε����� �Լ�
void loadingScene::loadingSound(void)
{
}
