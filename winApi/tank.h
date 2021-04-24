#pragma once
#include "gameNode.h"
#include "tankMap.h"

//탱크 4방향
enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_UP,
	TANKDIRECTION_DOWN
};

class tank : public gameNode
{
private:
	tankMap* _tankMap;
	image* _image;
	TANKDIRECTION _direction;
	RECT _rc;
	float _x, _y;
	float _speed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void tankMove();
	void setTankPosition();

	//타일맵 메모리 링크
	void setTankMapMemoryLink(tankMap* tm) { _tankMap = tm; }

	tank() {}
	~tank() {}
};

