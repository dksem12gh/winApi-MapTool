#pragma once
#include "gameNode.h"

struct tagEffect
{
	image* img;
	RECT rc;
	float x;
	float y;
	int count;
};

class missileEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	missileEffect() {}
	~missileEffect() {}
};


class beamEffect : public gameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	beamEffect() {}
	~beamEffect() {}
};

