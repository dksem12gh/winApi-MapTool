#pragma once
#include "gameNode.h"

class saveLoadTest : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void write(void);
	void read(void);

	saveLoadTest() {}
	~saveLoadTest() {}
};

