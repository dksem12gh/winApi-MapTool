#include "stdafx.h"
#include "mainGame.h"
#include "start.h"
#include "maptool.h"
#include "gameCamera.h"
#include "JsonTestScene.h"
//=========================
//	## init(void) ## �ʱ�ȭ
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ
	SCENEMANAGER->addScene("�ε�", new loadingScene);
	SCENEMANAGER->addScene("����", new start);
	SCENEMANAGER->addScene("����", new maptool);
	SCENEMANAGER->addScene("�κ�", new gameCamera);
	SCENEMANAGER->addScene("���̽�", new JsonTestScene);
	SCENEMANAGER->changeScene("�ε�");

	//Json::Value a;
	//SCENEMANAGER->addScene("���̽�", new JsonTestScene);

	//SCENEMANAGER->changeScene("���̽�");

	//Json::Value a;
	//Json::Value b;

	//b["name"] = "adfs";

	//a["item"].append(b);


	//JSONDATAMANAGER->saveJsonFile("������.json", a);

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();

	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���		
}

//=============================
//	## update(void) ## ������Ʈ
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("����");
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("����");
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SCENEMANAGER->changeScene("�κ�");
	}


	SCENEMANAGER->update();

}

//============================
//	## render(HDC hdc) ## ����
//============================

void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}
