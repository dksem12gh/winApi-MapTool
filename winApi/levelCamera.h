#pragma once
#include "singletonBase.h"

class levelCamera : public singletonBase<levelCamera>
{
private:
	RECT _camera;
	RECT _level[3];

	image* _camera1;
	image* _camera2;
	image* _camera3;
	image* _camera4;

	image* _cameraWindow;

	float _cameraW;
	float _cameraH;

	//값 뺄때 (서브라이트)
	float _sublight;

	//라이트값
	float _Light[4];

	POINT _cameraPt;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC getmemDC);

	void cameraSet();
	void cameraLevel(int);

	void setCameraPt(POINT pt) { _cameraPt = pt; _cameraPt.x -= 635; _cameraPt.y -= 320; }
	void setCameraLight(float light) { _sublight = light; }

	RECT getGameCameraRc() { return _camera; }
	POINT getCameraPt() { return _cameraPt; }


	levelCamera(){}
	~levelCamera(){}
};

