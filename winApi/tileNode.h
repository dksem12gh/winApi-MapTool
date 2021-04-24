#pragma once

//ȭ����� ����ȭ��
#define TILESIZE 50						//���� ȭ�� Ÿ�� ������
#define TILEX 41						//����ȭ�� Ÿ�� ������ X
#define TILEY 41						//����ȭ�� Ÿ�� ������ Y
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//������Ʈ ������
#define OBJSIZE 50
#define OBJX 41
#define OBJY 41
#define OBJSIZEX OBJX * OBJSIZE
#define OBJSIZEY OBJY * OBJSIZE

//ȭ�� ������ �̹��� Ÿ�� ����
//Ÿ��
#define SAMPLETILEX 8
#define SAMPLETILEY 5
//������Ʈ
#define OBJTILEX 8
#define OBJTILEY 3

//��Ʈ������
//�����Ӽ� �����ϱ�
//������ & and | or 
//||(OR), &&(AND)
//|(OR), &(AND)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
#define ATTR_UNMOVE   0x00000001
#define ATTR_POSITION 0x00000002
#define ATTR_LEVEL1   0x00000003
#define ATTR_LEVEL2   0x00000004
#define ATTR_LEVEL3   0x00000005

//������ ��

#define FPS 5
#define SPEED 1



enum CAMERA
{
	CAMERA_LEVEL1,
	CAMERA_LEVEL2,
	CAMERA_LEVEL3
};

//�������� ����� ��Ʈ�� �̳ѹ�
enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_DRAW,
	CTRL_ERASER,
	CTRL_TILE,
	CTRL_OBJ,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW
};

//����
enum TERRAIN
{
	//�κ� ������
	TR_LOBYBEAT_R,
	TR_LOBYBEAT_L,
	TR_LOBYNIGHT_R,
	TR_LOBYNIGHT_L,
	//��1 ������
	TR_MAP1BEAT_R,
	TR_MAP1BEAT_L,
	TR_MAP1NIGHT_R,
	TR_MAP1NIGHT_L,
	//��2 ������
	TR_MAP2BEAT_R,
	TR_MAP2BEAT_L,
	TR_MAP2NIGHT_R,
	TR_MAP2NIGHT_L,
	//��3 ������
	TR_MAP3BEAT_R,
	TR_MAP3BEAT_L,
	TR_MAP3NIGHT_R,
	TR_MAP3NIGHT_L,

	TR_ICE,
	TR_FIRE,
	TR_WATER,
	TR_GOAL,

	TR_END
};

//������Ʈ
enum OBJECT
{
	//������ X �Ѵ�
	OBJ_LEVEL1,
	OBJ_BROKENLEVEL1,
	//������ �� �δ�
	OBJ_LEVEL2,
	OBJ_BROKENLEVEL2,
	//���� ��ź�μ��� ����
	OBJ_LEVEL3,
	OBJ_BROKENLEVEL3,
	OBJ_NONE
};

//���̾�
enum Layer
{
	//�ٴ�,������Ʈ,���ǰ
	LAY_TER,
	LAY_OBJ,
	LAY_MAK,
};

enum Body
{
	BODY_BASE,

};

//��ġ��ǥ
enum POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

enum STAY
{
	PLAYER_ON,
	PLAYER_OFF
};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};
