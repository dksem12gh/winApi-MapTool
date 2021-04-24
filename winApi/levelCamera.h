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

	//�� ���� (�������Ʈ)
	float _sublight;

	//����Ʈ��
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

