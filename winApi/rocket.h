#pragma once
#include "gameNode.h"
#include "flame.h"
#include "bullets.h"
#include "progressBar.h"

#define ROCKETSPEED 2.0f

class enemyManager;

enum weapon
{
	MISSILE, BEAM
};

class rocket : public gameNode
{
private:
	image* _image;
	flame* _flame;
	missileM1* _missile;
	beam* _beam;
	progressBar* _hpBar;
	enemyManager* _em;

	weapon _setWeapon;
	RECT _rc;
	float _x, _y;
	float _currentHp;
	float _maxHp;
	bool _beamIrradiation;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void removeMissile(int arrNum);
	void collision(void);
	void setEnemyManagerMemoryAddress(enemyManager* em) { _em = em; }

	missileM1* getMissile(void) { return _missile; }
	beam* getBeam(void) { return _beam; }

	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }

	RECT getRect(void) { return _rc; }
	void hitDamage(float damage)
	{
		if (_currentHp < 0)
		{
			_currentHp = 0;
			return;
		}
		_currentHp -= damage;
	}

	rocket() {}
	~rocket() {}
};

