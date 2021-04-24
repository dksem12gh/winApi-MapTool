#pragma once
#include "gameNode.h"
#include "gameCamera.h"

class Lobby :
	public gameNode
{
private:
	gameCamera* _playCamera;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Lobby(){}
	~Lobby(){}
};

