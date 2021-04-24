#pragma once
#include "gameNode.h"
#include "questSample.h"

class JsonTestScene : public gameNode
{
private:
	questSample* _Qs;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void questPopUp();
	void currentQuest();
	
	JsonTestScene() {}
	~JsonTestScene() {}
};