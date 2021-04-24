#include "stdafx.h"
#include "saveLoadTest.h"

HRESULT saveLoadTest::init(void)
{
	return S_OK;
}

void saveLoadTest::release(void)
{
}

void saveLoadTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		write();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		read();
	}
}

void saveLoadTest::render(void)
{
}

void saveLoadTest::write(void)
{
	HANDLE file;
	char str[64] = "게임 잘 만들어 부자되라";
	DWORD write;

	file = CreateFile("너희가게임을아느냐.txt", GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

void saveLoadTest::read(void)
{
	HANDLE file;
	static char str[64];
	DWORD read;

	file = CreateFile("너희가게임을아느냐.txt", GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, str, strlen(str), &read, NULL);
	CloseHandle(file);

	MessageBox(_hWnd, str, "잘 읽어온다~!", MB_ABORTRETRYIGNORE);
}
