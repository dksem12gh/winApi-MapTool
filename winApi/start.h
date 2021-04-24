#pragma once
#include "gameNode.h"

class start :
	public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update();
	void render();

	start(){}
	~start(){}
};

