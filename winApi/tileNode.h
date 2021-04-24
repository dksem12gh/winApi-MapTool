#pragma once

//화면왼쪽 게임화면
#define TILESIZE 50						//왼쪽 화면 타일 사이즈
#define TILEX 41						//왼쪽화면 타일 사이즈 X
#define TILEY 41						//왼쪽화면 타일 사이즈 Y
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//오브젝트 오른쪽
#define OBJSIZE 50
#define OBJX 41
#define OBJY 41
#define OBJSIZEX OBJX * OBJSIZE
#define OBJSIZEY OBJY * OBJSIZE

//화면 오른쪽 이미지 타일 갯수
//타일
#define SAMPLETILEX 8
#define SAMPLETILEY 5
//오브젝트
#define OBJTILEX 8
#define OBJTILEY 3

//비트연산자
//지형속성 정의하기
//단위는 & and | or 
//||(OR), &&(AND)
//|(OR), &(AND)
//0001 | 0000 => 0001
//0001 & 0000 => 0000
#define ATTR_UNMOVE   0x00000001
#define ATTR_POSITION 0x00000002
#define ATTR_LEVEL1   0x00000003
#define ATTR_LEVEL2   0x00000004
#define ATTR_LEVEL3   0x00000005

//프레임 수

#define FPS 5
#define SPEED 1



enum CAMERA
{
	CAMERA_LEVEL1,
	CAMERA_LEVEL2,
	CAMERA_LEVEL3
};

//맵툴에서 사용할 컨트롤 이넘문
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

//지형
enum TERRAIN
{
	//로비 깜빡이
	TR_LOBYBEAT_R,
	TR_LOBYBEAT_L,
	TR_LOBYNIGHT_R,
	TR_LOBYNIGHT_L,
	//맵1 깜빡이
	TR_MAP1BEAT_R,
	TR_MAP1BEAT_L,
	TR_MAP1NIGHT_R,
	TR_MAP1NIGHT_L,
	//맵2 깜빡이
	TR_MAP2BEAT_R,
	TR_MAP2BEAT_L,
	TR_MAP2NIGHT_R,
	TR_MAP2NIGHT_L,
	//맵3 깜빡이
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

//오브젝트
enum OBJECT
{
	//프레임 X 한대
	OBJ_LEVEL1,
	OBJ_BROKENLEVEL1,
	//프레임 ㅇ 두대
	OBJ_LEVEL2,
	OBJ_BROKENLEVEL2,
	//무적 폭탄부술시 돈줌
	OBJ_LEVEL3,
	OBJ_BROKENLEVEL3,
	OBJ_NONE
};

//레이어
enum Layer
{
	//바닥,오브젝트,장식품
	LAY_TER,
	LAY_OBJ,
	LAY_MAK,
};

enum Body
{
	BODY_BASE,

};

//위치좌표
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

//타일구조체
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

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//현재 타일 구조체
struct tagCurrentTile
{
	int x;
	int y;
};
