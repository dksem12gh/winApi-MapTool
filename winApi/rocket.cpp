#include "stdafx.h"
#include "rocket.h"
#include "enemyManager.h"

HRESULT rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("rocket", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY - 100;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
		
	_flame = new flame;
	_flame->init("flame.bmp", &_x, &_y);
	
	_missile = new missileM1;
	_missile->init(5, 700);

	_beam = new beam;
	_beam->init(1, 0.5);
	_beamIrradiation = false;

	_setWeapon = MISSILE;

	_currentHp = 10;
	_maxHp = 10;

	_hpBar = new progressBar;
	_hpBar->init(_x, _y, 52, 4);

	return S_OK;
}

void rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);

	_beam->release();
	SAFE_DELETE(_beam);

	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void rocket::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		char temp[32];
		vector<string> data;
		data.push_back(itoa((int)_x, temp, 10));
		data.push_back(itoa((int)_y, temp, 10));
		data.push_back(itoa((int)_currentHp, temp, 10));
		data.push_back(itoa((int)_maxHp, temp, 10));

		TXTMANAGER->save("肺南历厘.txt", data);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		vector<string> vData = TXTMANAGER->load("肺南历厘.txt");

		_x = atoi(vData[0].c_str());
		_y = atoi(vData[1].c_str());
		_currentHp = atoi(vData[2].c_str());
		_maxHp = atoi(vData[3].c_str());
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX && _beamIrradiation == false)
	{
		_x += ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _beamIrradiation == false)
	{
		_x -= ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKETSPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZEY)
	{
		_y += ROCKETSPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_setWeapon = MISSILE;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_setWeapon = BEAM;
	}

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_missile->fire(_x, _y - 60);
		}
		break;

	case BEAM:
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			_beamIrradiation = true;
			_beam->fire(_x, _y - 430);
		}
		else _beamIrradiation = false;
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_flame->update();
	_missile->update();
	_beam->update();
	//collision();

	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGauge(_currentHp, _maxHp);
}

void rocket::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_missile->render();
	_beam->render();
	_hpBar->render();
}

void rocket::removeMissile(int arrNum)
{
	_missile->removeBullet(arrNum);
}

void rocket::collision(void)
{
	for (int i = 0; i < _missile->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missile->getBullet()[i].rc,
				//&_em->getMinions()[j]->getRect()))
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_missile->removeBullet(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _beam->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_beam->getBullet()[i].rc,
				//&_em->getMinions()[j]->getRect()))
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
}

