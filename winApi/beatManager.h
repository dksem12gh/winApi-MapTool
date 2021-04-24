#pragma once

#include "singletonBase.h"
#include "animation.h"

#define BEATSPEED 5

//노트 구조 
struct beat
{
	//노트왼쪽렉트
	RECT _heartBeatRC;
	//각 노트당 알파값
	float _beatAlpha;
	//노트 좌표
	int _beatX;
};

class beatManager : public singletonBase<beatManager>
{
private:
	//심장이 뛴다
	image* _heart;
	image* _heartBeat;
	image* _redBeat;
	animation* _heartAni;
	animation* _heartBeatAni;
	animation* _redBeatAni;

	//심장 그리기 렉트
	RECT _heartRC;
	//심장 충돌용 렉트
	RECT _heartBOX;

	//임시 충돌용 렉트
	RECT _beatAttackRc;

	//노트보관용 벡터
	vector <beat> _beatVec;

	beat _beat[4];

private:

	float _worldTimer;
	float _timer;

	//플레이어 이동
	int _baseBeat;
	//몬스터용
	int _monsterBeat;
	//타일용
	int _tileBeat;
	//상점주인 노래
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

