#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:
	float _alpha;
	char _text[64];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	startScene(){}
	~startScene(){}
};

