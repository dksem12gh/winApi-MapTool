#pragma once
#include "gameNode.h"
#include "start.h"
class mainGame : public gameNode
{
private:
	start* st;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

