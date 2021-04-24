#pragma once
#include "gameNode.h"

#define FLAMECOUNT 9.0f

class flame : public gameNode
{
private:
	image* _image;
	float* _x;
	float* _y;
	RECT _rc;
	float _flameCount;

public:
	HRESULT init(const char* imageName, float* x, float* y);
	void release(void);
	void update(void);
	void render(void);

	flame(){}
	~flame(){}
};

