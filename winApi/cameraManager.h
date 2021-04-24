#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	RECT _rc;

	POINT _cameraPoint;

	float _cameraW;
	float _cameraH;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void maptoolCamera();

	float getcameraW() { return _cameraW; }
	float getcameraH() { return _cameraH; }

	POINT getcameraPoint() { return _cameraPoint; }

	RECT getcameraRc() { return _rc; }

	cameraManager(){}
	~cameraManager(){}
};

