#pragma once
#include "gameNode.h"
#include "button.h"

class buttonTestScene : public gameNode
{
private:
	button* _button;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	static void buttonDown(void);

	buttonTestScene() {};
	~buttonTestScene() {};
};