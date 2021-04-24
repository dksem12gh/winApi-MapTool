#include "stdafx.h"
#include "JsonTestScene.h"

HRESULT JsonTestScene::init(void)
{
	_Qs = new questSample;
	_Qs->init();

	return S_OK;
}

void JsonTestScene::release(void)
{
}

void JsonTestScene::update(void)
{
}

void JsonTestScene::render(void)
{
	questPopUp();
}

void JsonTestScene::questPopUp()
{
	char str[256];
	queue<quest*>* temp = _Qs->getQuest();
	quest* node = temp->front();

	sprintf(str, "%s", node->getName().c_str());
	TextOut(getMemDC(), 400, 200, str, strlen(str));
	sprintf(str, "����: %s", node->getDescription().c_str());
	TextOut(getMemDC(), 400, 250, str, strlen(str));
	sprintf(str, "���� �̸�: %s", node->getMonsterName().c_str());
	TextOut(getMemDC(), 400, 300, str, strlen(str));
	sprintf(str, "óġ�ؾ� �� ����: %d ����", node->getMonster());
	TextOut(getMemDC(), 400, 350, str, strlen(str));
	sprintf(str, "����Ʈ Ÿ��: %s", node->getQuesttype().c_str());
	TextOut(getMemDC(), 400, 400, str, strlen(str));
	sprintf(str, "���� ����ġ: %d exp", node->getExp());
	TextOut(getMemDC(), 400, 450, str, strlen(str));
	sprintf(str, "����Ʈ ���� ������: %s", node->getItem().c_str());
	TextOut(getMemDC(), 400, 500, str, strlen(str));
	sprintf(str, "����Ʈ ���� ���: %d Gold", node->getGold());
	TextOut(getMemDC(), 400, 550, str, strlen(str));
}

void JsonTestScene::currentQuest()
{
}