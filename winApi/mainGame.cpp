#include "stdafx.h"
#include "mainGame.h"
#include "start.h"
#include "maptool.h"
#include "gameCamera.h"
#include "JsonTestScene.h"
//=========================
//	## init(void) ## 초기화
//=========================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화
	SCENEMANAGER->addScene("로딩", new loadingScene);
	SCENEMANAGER->addScene("시작", new start);
	SCENEMANAGER->addScene("맵툴", new maptool);
	SCENEMANAGER->addScene("로비", new gameCamera);
	SCENEMANAGER->addScene("제이슨", new JsonTestScene);
	SCENEMANAGER->changeScene("로딩");

	//Json::Value a;
	//SCENEMANAGER->addScene("제이슨", new JsonTestScene);

	//SCENEMANAGER->changeScene("제이슨");

	//Json::Value a;
	//Json::Value b;

	//b["name"] = "adfs";

	//a["item"].append(b);


	//JSONDATAMANAGER->saveJsonFile("아이템.json", a);

	return S_OK;
}

//=====================
//	## release(void) ##
//=====================
void mainGame::release(void)
{
	gameNode::release();

	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용		
}

//=============================
//	## update(void) ## 업데이트
//=============================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("맵툴");
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		SCENEMANAGER->changeScene("시작");
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SCENEMANAGER->changeScene("로비");
	}


	SCENEMANAGER->update();

}

//============================
//	## render(HDC hdc) ## 렌더
//============================

void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}
