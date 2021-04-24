#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _image;
	float _x, _y;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _rndTimeCount;
	float _worldTimeCount;

	float _rndFireCount;
	float _bulletFireCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);
	bool bulletCountFire(void);

	RECT getRect(void) { return _rc; }

	enemy(void);
	~enemy(void){}
};

