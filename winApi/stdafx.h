// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKver.h>

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN
// Windows ��� ����:
#include <Windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//======================================
//	## ���� ���� ��������� �̰��� �߰� ##
//======================================
#include "commonMacroFiunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"
#include "txtDataManager.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "cameraManager.h"
#include "levelCamera.h"
#include "beatManager.h"
#include "json/json.h"
#include "JsonSaveLoader.h"

using namespace MY_UTIL;

//================================
//	## �̱����� �̰��� �߰��Ѵ� ##
//================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTMANAGER txtDataManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define LEVELCAMERA levelCamera::getSingleton()
#define BEATMANAGER beatManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()

//================================
//	## ��ũ�� ## (������â �ʱ�ȭ)
//================================
#define WINNAME			(LPTSTR)(TEXT("CRYPT OF THE NECRODANCER - �Ѵ���Ʈ������ ����"))
#define WINSTARTX		400
#define WINSTARTY		100
//����ȭ�� + ����� + ������ Ÿ���̹���
#define WINSIZEX		620 +50+ 600
#define WINSIZEY		640
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## ��ũ�� �Լ� ## (Ŭ�������� �����Ҵ�� �κ� ����)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## �������� ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern BOOL			_leftButtonDown;

#define WINDOWSX 625
#define WINDOWSY 320