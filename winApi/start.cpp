#include "stdafx.h"
#include "start.h"

HRESULT start::init(void)
{
	return S_OK;
}

void start::release(void)
{
}

void start::update()
{

}

void start::render()
{
	IMAGEMANAGER->render("bg1", getMemDC());
}
