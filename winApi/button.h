#pragma once
#include "gameNode.h"

typedef void(*CALLBACKFUNCTION)(void);

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;
	const char* _imageName;
	image* _image;

	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;
	POINT _btnCollisonFramePoint;

	CALLBACKFUNCTION _callbackFunction;	

public:
	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint);

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACKFUNCTION cbFunction);

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		POINT btnCollisonFramePoint, CALLBACKFUNCTION cbFunction);

	void release(void);
	void update(void);
	void render(void);

	button() : _callbackFunction(NULL) {};
	virtual ~button() {}
};