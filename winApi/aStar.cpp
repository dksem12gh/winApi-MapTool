#include "stdafx.h"
#include "aStar.h"

HRESULT aStar::init()
{
	_aStarState = ASTAR_STATE_PREPARING;		//초기 aStar 알고리즘 상태 = 타일 배치 완료 전
	_mouseState = EMPTY;
	_selectedType = TILE_TYPE_EMPTY;			//배치할 타일 속성 = 빈 타일
	_selectedTypeColor = RGB(255, 255, 255);	//배치할 타일 색상 = 흰색

	_startPointSet = false;                     //시작지점 배치 여부 = false
	_endPointSet = false;                       //도착지점 배치 여부 = false

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++) 
		{
			_tile[i][j].type = TILE_TYPE_EMPTY;			//초기 타일 속성 = 빈 타일
			_tile[i][j].color = RGB(255, 255, 255);		//초기 타일 색상 = 흰색
			_tile[i][j].parent = NULL;                  //부모 타일 = NULL
			_tile[i][j].F = BIGNUM;                     //충분히 큰 F 할당
			_tile[i][j].G = 0.0f;						//F = G + H
			_tile[i][j].H = 0.0f;                       //H 계산 전이므로 0
			_tile[i][j].i = i;                          //i 인덱스
			_tile[i][j].j = j;                          //j 인덱스
			_tile[i][j].rc = RectMake(WINSIZEX - (TILE_X + 1)  * WIDTH + WIDTH * j, WINSIZEY / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT * i, WIDTH, HEIGHT); //렉트 할당
		}
	}
	return S_OK;
}

void aStar::release()
{
}

void aStar::update()
{
	//아직 배치가 끝나지 않았다면
	if (_aStarState == ASTAR_STATE_PREPARING)		   
	{
		//타일 배치
		tileComposition();							  		
	}

	//시작지점 도착지점 설치되어 있고, 스페이스 바를 누르면 타일 초기화
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _startPointSet && _endPointSet && _aStarState == ASTAR_STATE_PREPARING) { tileInitializing(); }

	//배치 중이거나, 발견 했거나, 길이 없다면 알고리즘을 실행 하지 않는다
	if (_aStarState == ASTAR_STATE_PREPARING || _aStarState == ASTAR_STATE_FOUND || _aStarState == ASTAR_STATE_NOWAY) return;

	addOpenList();          //오픈리스트에 추가 후 G값 계산
	calculateH();           //H계산
	calculateF();           //F계산
	addCloseList();         //클로즈리스트에 추가
	checkArrive();          //도착 여부 체크
}

void aStar::render()
{	
	TextOut(getMemDC(), 15, 15, "1: EMPTY", strlen("1: EMPTY"));
	TextOut(getMemDC(), 15, 35, "2: START", strlen("2: START"));
	TextOut(getMemDC(), 15, 55, "3: END",	strlen("3: END"));
	TextOut(getMemDC(), 15, 75, "4: WALL",  strlen("4: WALL"));

	char str[128];
	if (_aStarState == ASTAR_STATE_PREPARING)
		sprintf_s(str, "시작: 스페이스 바");
	else if (_aStarState == ASTAR_STATE_FOUND)
		sprintf_s(str, "길을 찾았다");
	else if (_aStarState == ASTAR_STATE_NOWAY)
		sprintf_s(str, "길이 없다");
	else if (_aStarState == ASTAR_STATE_SEARCHING)
		sprintf_s(str, "탐색중");

	TextOut(getMemDC(), 15, 120, str, strlen(str));

	switch (_mouseState)
	{
	case EMPTY:
		sprintf(str, "마우스상태: EMPTY");
		break;
	case START:
		sprintf(str, "마우스상태: START");
		break;
	case END:
		sprintf(str, "마우스상태: END");
		break;
	case WALL:
		sprintf(str, "마우스상태: WALL");
		break;
	}
	TextOut(getMemDC(), 15, 145, str, strlen(str));

	HBRUSH newBrush, oldBrush;
	HFONT newFont, oldFont;
	newFont = CreateFont(9, 0, 0, 0, FW_NORMAL, false, false, 0, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, "굴림");
	oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			newBrush = CreateSolidBrush(_tile[i][j].color);
			oldBrush = (HBRUSH)SelectObject(getMemDC(), newBrush);

			Rectangle(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].rc.right, _tile[i][j].rc.bottom);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(newBrush);

			//F가 BIGNUM보다 작을 때만 (F/G/H)를 화면에 표시
			if (_tile[i][j].F < BIGNUM)
			{
				SetBkMode(getMemDC(), TRANSPARENT);
				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].F);
				TextOut(getMemDC(), _tile[i][j].rc.left + 2, _tile[i][j].rc.top + 2, _tile[i][j].str, strlen(_tile[i][j].str));

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].G);
				TextOut(getMemDC(), _tile[i][j].rc.left + 2, _tile[i][j].rc.top + 22, _tile[i][j].str, strlen(_tile[i][j].str));

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].H);
				TextOut(getMemDC(), _tile[i][j].rc.left + 22, _tile[i][j].rc.top + 22, _tile[i][j].str, strlen(_tile[i][j].str));
			}

			if (_tile[i][j].parent == NULL) continue;

			int length = 15;

			MoveToEx(getMemDC(), (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2, (_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2, NULL);
			LineTo(getMemDC(), (_tile[i][j].parent->j - _tile[i][j].j) * length + (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2,
				(_tile[i][j].parent->i - _tile[i][j].i) * length + (_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2);
		}
	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);
}

//타일 배치
void aStar::tileComposition()
{
	//비어 있을때
	if (KEYMANAGER->isOnceKeyDown('1'))
	{ 
		_selectedType = TILE_TYPE_EMPTY;
		_selectedTypeColor = RGB(255, 255, 255);
		_mouseState = EMPTY;
	}
	//스타트 일때
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_selectedType = TILE_TYPE_START;	
		_selectedTypeColor = RGB(100, 255, 100);
		_mouseState = START;
	}
	//엔드 일때
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{ 
		_selectedType = TILE_TYPE_END;
		_selectedTypeColor = RGB(255, 100, 100);
		_mouseState = END;
	}

	//벽 일떄
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{ 
		_selectedType = TILE_TYPE_WALL;
		_selectedTypeColor = RGB(100, 100, 255);
		_mouseState = WALL;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				if (PtInRect(&_tile[i][j].rc, _ptMouse))
				{
					//시작지점 밑 끝지점 셋팅: false
					if (_tile[i][j].type == TILE_TYPE_START) _startPointSet = false;
					if (_tile[i][j].type == TILE_TYPE_END) _endPointSet = false;

					_tile[i][j].type = _selectedType;
					_tile[i][j].color = _selectedTypeColor;

					if (_selectedType == TILE_TYPE_START)
					{
						if (_startPointSet)
						{
							_tile[_startY][_startX].color = RGB(255, 255, 255);
							_tile[_startY][_startX].type = TILE_TYPE_EMPTY;
						}
						_startPointSet = true;
						_startX = j;
						_startY = i;
					}

					if (_selectedType == TILE_TYPE_END)
					{
						if (_endPointSet)
						{
							_tile[_endY][_endX].color = RGB(255, 255, 255);
							_tile[_endY][_endX].type = TILE_TYPE_EMPTY;
						}
						_endPointSet = true;
						_endX = j;
						_endY = i;
					}
				}
			}
		}
	}
}

//타일 배치 후 타일 속성에 맞게 타일 초기화
void aStar::tileInitializing()
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			if (_tile[i][j].type == TILE_TYPE_EMPTY)                     //일반 타일
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}

			else if (_tile[i][j].type == TILE_TYPE_WALL)                 //막힌 타일
			{
				_tile[i][j].walkable = false;
				_tile[i][j].listOn = false;
			}

			else if (_tile[i][j].type == TILE_TYPE_START)                //시작 지점
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = true;
				_closeList.push_back(&_tile[i][j]);
			}

			else if (_tile[i][j].type == TILE_TYPE_END)                  //도착 지점
			{
				_endX = j;
				_endY = i;
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
		}
	}
	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

//오픈리스트에 추가
void aStar::addOpenList()
{
	Ci = _closeList[_lastIndex]->i;                  //마지막으로 추가된 클로즈 리스트의 i
	Cj = _closeList[_lastIndex]->j;                  //마지막으로 추가된 클로즈 리스트의 j
	Cg = _closeList[_lastIndex]->G;                  //마지막으로 추가된 클로즈 리스트의 G

	if (Ci != 0)									 //0번째 줄이 아니라면 상단 라인 계산
	{
		if (_tile[Ci - 1][Cj].walkable)				 //상단 가운데 타일이 지나갈 수 있다면
		{											 
			if (!_tile[Ci - 1][Cj].listOn)			 //오픈리스트에 포함이 안 되어 있는 타일이라면
			{
				_tile[Ci - 1][Cj].listOn = true;						 //오픈리스트에 포함되었다
				_tile[Ci - 1][Cj].color = RGB(220, 255, 220);			 //색상 연녹색
				_tile[Ci - 1][Cj].G = Cg + 10;							 //타일의 G값을 클로즈 리스트의 누적 G + 10
				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];       //타일의 부모를 클로즈 리스트의 마지막으로 추가된 타일로 설정
				_openList.push_back(&_tile[Ci - 1][Cj]);				 //오픈리스트 벡터에 추가
			}
			else														 //오픈리스트에 포함이 되어 있던 타일이라면
			{
				if (Cg + 10 < _tile[Ci - 1][Cj].G)						 //기존 G값보다 새로 계산한 G값이 작다면
				{
					_tile[Ci - 1][Cj].G = Cg + 10;						 //G값 새롭게 계산
					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];   //타일의 부모를  클로즈 리스트의 마지막으로 추가된 타일로 재설정
				}
			}
		}
		//좌상단 : 0번째 열이 아니라면
		if (Cj != 0)														
		{
			//좌상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (_tile[Ci - 1][Cj - 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)  
			{
				if (!_tile[Ci - 1][Cj - 1].listOn)
				{
					_tile[Ci - 1][Cj - 1].listOn = true;
					_tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
					//대각선이므로 G + 14
					_tile[Ci - 1][Cj - 1].G = Cg + 14;						
					_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj - 1]);
				}

				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
					{
						_tile[Ci - 1][Cj - 1].G = Cg + 14;
						_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		//우상단 : 마지막 열이 아니라면
		if (Cj != TILE_X - 1)																				 
		{
			//우상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (_tile[Ci - 1][Cj + 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)  
			{
				if (!_tile[Ci - 1][Cj + 1].listOn)
				{
					_tile[Ci - 1][Cj + 1].listOn = true;
					_tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
					_tile[Ci - 1][Cj + 1].G = Cg + 14;
					_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
					{
						_tile[Ci - 1][Cj + 1].G = Cg + 14;
						_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}

	//좌측 : 0번째 열이 아니라면
	if (Cj != 0)					    
	{
		//좌측 타일이 이동가능하다면
		if (_tile[Ci][Cj - 1].walkable) 
		{
			if (!_tile[Ci][Cj - 1].listOn)
			{
				_tile[Ci][Cj - 1].listOn = true;
				_tile[Ci][Cj - 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj - 1].G = Cg + 10;
				_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj - 1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj - 1].G)
				{
					_tile[Ci][Cj - 1].G = Cg + 10;
					_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}

	//우측 : 마지막 열이 아니라면
	if (Cj != TILE_X - 1)				
	{
		//우측 타일이 이동가능하다면
		if (_tile[Ci][Cj + 1].walkable) 
		{
			if (!_tile[Ci][Cj + 1].listOn)
			{
				_tile[Ci][Cj + 1].listOn = true;
				_tile[Ci][Cj + 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj + 1].G = Cg + 10;
				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj + 1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj + 1].G)
				{
					_tile[Ci][Cj + 1].G = Cg + 10;
					_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}

	//마지막 행이 아니라면 하단 라인 계산
	if (Ci != TILE_Y - 1)				
	{
		//하단 가운데 타일이 이동가능하다면
		if (_tile[Ci + 1][Cj].walkable) 
		{
			if (!_tile[Ci + 1][Cj].listOn)
			{
				_tile[Ci + 1][Cj].listOn = true;
				_tile[Ci + 1][Cj].color = RGB(220, 255, 220);
				_tile[Ci + 1][Cj].G = Cg + 10;
				_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci + 1][Cj]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci + 1][Cj].G)
				{
					_tile[Ci + 1][Cj].G = Cg + 10;
					_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}
		//좌하단 : 0번째 열이 아니라면
		if (Cj != 0)																						 
		{
			//좌하단 타일의 오른쪽이나 위에 벽이 없다면
			if (_tile[Ci + 1][Cj - 1].walkable && _tile[Ci + 1][Cj].walkable &&_tile[Ci][Cj - 1].walkable)   
			{
				if (!_tile[Ci + 1][Cj - 1].listOn)
				{
					_tile[Ci + 1][Cj - 1].listOn = true;
					_tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
					_tile[Ci + 1][Cj - 1].G = Cg + 14;
					_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
					{
						_tile[Ci + 1][Cj - 1].G = Cg + 14;
						_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		//우하단 : 마지막 열이 아니라면
		if (Cj != TILE_X - 1)																			
		{
			//우하단 타일의 오른쪽이나 위가 이동가능하다면
			if (_tile[Ci + 1][Cj + 1].walkable && _tile[Ci + 1][Cj].walkable &&_tile[Ci][Cj + 1].walkable) 
			{
				if (!_tile[Ci + 1][Cj + 1].listOn)
				{
					_tile[Ci + 1][Cj + 1].listOn = true;
					_tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
					_tile[Ci + 1][Cj + 1].G = Cg + 14;
					_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
					{
						_tile[Ci + 1][Cj + 1].G = Cg + 14;
						_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
}

void aStar::calculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;     //가로 H값
		int horizontal = (_endY - _openList[i]->i) * 10;   //세로 H값

		if (vertical < 0) vertical *= -1;				   //방향이 반대이면 음수 부여(절대값)
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;		   //총 H값 = 가로H + 세로H
	}

}

void aStar::calculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		//F값 계산
		_openList[i]->F = _openList[i]->G + _openList[i]->H;               
	}

}

void aStar::addCloseList()
{
	if (_openList.size() == 0)								//검색했는데도 openlist의 사이즈가 0이라면 더이상 찾을 것이 없음
	{
		_aStarState = ASTAR_STATE_NOWAY;					//경로가 없다
		return;												//이하 작업 무시
	}

	int index = 0;											//오픈리스트 중 가장 F가 작은 타일의 인덱스
	int lowest = BIGNUM;									//오픈리스트 중 가장 작은 F값
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)						//오픈리스트의 F가 가장 작은거보다 더 작다면
		{
			lowest = _openList[i]->F;						//lowest를 그 F로
			index = i;										//index를 그 index로
		}
	}

	_openList[index]->color = RGB(180, 180, 255);			//클로즈에 추가된 타일의 색상: 연파랑

	_closeList.push_back(_openList[index]);					//클로즈리스트에 추가
	_openList.erase(_openList.begin() + index);				//클로즈리스트에 추가된 타일은 오픈리스트에서 제외

	_lastIndex++;											//가장 나중에 추가된 클로즈의 인덱스
}

//도착했는지 여부를 체크
void aStar::checkArrive()
{
	//클로즈리스트의 i j가 도착지점과 같다면
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX) 
	{
		_aStarState = ASTAR_STATE_FOUND;							//찾았다
		_closeList[_lastIndex]->color = RGB(255, 100, 100);			//도착지점 색상: 빨강
		showWay(_closeList[_lastIndex]);							//경로 보여준다
	}
}

//도착 후 시작지점과 도착지점을 잇는 경로를 보여주는 함수
void aStar::showWay(aStarTile * tile)
{
	if (!(tile->i == _endY && tile->j == _endX))	    //도착지점이 아니라면
		tile->color = RGB(255, 180, 180);				//색상 연분홍
	tile = tile->parent;								//타일의 부모를 참조해서 showWay()함수에 다시 넣는다

	if (tile->parent == NULL)							//타일의 부모가 시작지점이면 리턴
		return;
	else
		showWay(tile);									//showWay() 다시 호출
}