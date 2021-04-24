#pragma once
#include "gameNode.h"

#define TILE_X	20		    //���� Ÿ�� ��
#define TILE_Y	20		    //���� Ÿ�� ��
#define WIDTH	40		    //Ÿ�� ���� ����
#define HEIGHT	40		    //Ÿ�� ���� ����
#define BIGNUM	5000	    //����� ū F ��(�ʱⰪ)

//Ÿ�� �Ӽ�
enum TILE_TYPE
{
	TILE_TYPE_EMPTY,		//�� Ÿ��(�������� �ִ�)
	TILE_TYPE_START,		//���� ����
	TILE_TYPE_END,			//�� ����
	TILE_TYPE_WALL			//��
};

//���� ����
enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,	//�˻���
	ASTAR_STATE_FOUND,		//��� �߰�
	ASTAR_STATE_NOWAY,		//��ΰ� ����
	ASTAR_STATE_PREPARING	//Ÿ�� ��ġ �Ϸ� ��
};

//���콺 ����
enum MOUSE_STATE
{
	EMPTY,
	START,
	END,
	WALL
};

struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;		    //���� ���� �ִ��� ����
	bool listOn;		    //openList�� �߰� �Ǿ����� ����
	int i, j;			    //�迭 �ε��� i,j
	int F, G, H;			//F, G, H
	char str[128];
	aStarTile* parent;		//�θ� Ÿ�� �ּ�
	TILE_TYPE type;			//Ÿ�� �Ӽ�
};

class aStar : public gameNode
{
private:
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState;
	MOUSE_STATE _mouseState;

	TILE_TYPE _selectedType;			//Ÿ�� ��ġ�� �� ����� Ÿ�� �Ӽ�
	COLORREF _selectedTypeColor;		//Ÿ�� ��ġ�� �� ����� Ÿ�� ��

	int _startX, _startY;				//���������� i, j�ε�����
	int _endX, _endY;					//���������� i, j�ε�����
	int _lastIndex;						//���� ���߿� �߰��� Ŭ���� ����Ʈ�� �ε���

	bool _startPointSet;				//���������� ��ġ �Ǿ����� ����
	bool _endPointSet;					//���������� ��ġ �Ǿ����� ����

	int Ci;								//���������� �߰��� Ŭ���� ����Ʈ�� i
	int Cj;								//���������� �߰��� Ŭ���� ����Ʈ�� j
	int Cg;								//���������� �߰��� Ŭ���� ����Ʈ�� g

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void tileComposition();			    //Ÿ�� ��ġ
	void tileInitializing();	        //Ÿ�� ��ġ �� �Ӽ��� �°� Ÿ�� �ʱ�ȭ
	void addOpenList();				    //���� ����Ʈ�� �߰�
	void calculateH();				    //���� ����Ʈ �� Ÿ���� H�� ���
	void calculateF();				    //���� ����Ʈ �� Ÿ���� F�� ���
	void addCloseList();			    //���� ���� F ���� �� Ŭ���� ����Ʈ�� �߰�
	void checkArrive();				    //�����ߴ��� ���� üũ
	void showWay(aStarTile* tile);	    //���� �� ���������� ���������� �մ� ��� �����ִ� �Լ�

	aStar() {}
	~aStar() {}
};