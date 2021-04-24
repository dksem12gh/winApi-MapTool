#include "stdafx.h"
#include "shootingEffect.h"

HRESULT missileEffect::init(void)
{
	return S_OK;
}

void missileEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void missileEffect::update(void)
{
}

void missileEffect::render(void)
{
	draw();
}

void missileEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void missileEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("missileeffect.bmp", 0.0f, 0.0f,
		390, 63, 6, 1, true, RGB(50, 150, 200));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}

void missileEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin());
}

HRESULT beamEffect::init(void)
{
	return S_OK;
}

void beamEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}

	_vEffect.clear();
}

void beamEffect::update(void)
{
}

void beamEffect::render(void)
{
	draw();
}

void beamEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left,
			_viEffect->rc.top);

		_viEffect->count++;
		if (_viEffect->count % 4 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				removeEffect(0);
				break;
			}
		}
	}
}

void beamEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));
	effect.img = new image;
	effect.img->init("beameffect.bmp", 0.0f, 0.0f,
		96, 128, 4, 1, true, RGB(255, 0, 255));
	effect.x = rc.left + (rc.right - rc.left) / 2;
	effect.y = rc.top;
	effect.rc = RectMakeCenter(effect.x, effect.y,
		effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
}
void beamEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);

	_vEffect.erase(_vEffect.begin());
}