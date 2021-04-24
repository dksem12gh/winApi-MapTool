#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init(void)
{
	_playCamera = new gameCamera;
	_playCamera->init();

	return S_OK;
}

void Lobby::release(void)
{
	_playCamera->release();

}

void Lobby::update(void)
{
	_playCamera->update();

}

void Lobby::render(void)
{
	_playCamera->render();
}

