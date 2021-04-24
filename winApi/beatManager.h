#pragma once

#include "singletonBase.h"
#include "animation.h"

#define BEATSPEED 5

//��Ʈ ���� 
struct beat
{
	//��Ʈ���ʷ�Ʈ
	RECT _heartBeatRC;
	//�� ��Ʈ�� ���İ�
	float _beatAlpha;
	//��Ʈ ��ǥ
	int _beatX;
};

class beatManager : public singletonBase<beatManager>
{
private:
	//������ �ڴ�
	image* _heart;
	image* _heartBeat;
	image* _redBeat;
	animation* _heartAni;
	animation* _heartBeatAni;
	animation* _redBeatAni;

	//���� �׸��� ��Ʈ
	RECT _heartRC;
	//���� �浹�� ��Ʈ
	RECT _heartBOX;

	//�ӽ� �浹�� ��Ʈ
	RECT _beatAttackRc;

	//��Ʈ������ ����
	vector <beat> _beatVec;

	beat _beat[4];

private:

	float _worldTimer;
	float _timer;

	//�÷��̾� �̵�
	int _baseBeat;
	//���Ϳ�
	int _monsterBeat;
	//Ÿ�Ͽ�
	int _tileBeat;
	//�������� �뷡
	int _shopBeat;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC);

	void setUp();

	void beatLode();
	void beatAlpha();

	beatManager(){}
	~beatManager(){}
};

