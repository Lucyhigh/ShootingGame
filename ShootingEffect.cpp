#include "Stdafx.h"
#include "ShootingEffect.h"

HRESULT MissileEffect::init(void) {
    return S_OK;
}

void MissileEffect::release(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        SAFE_DELETE(_viEffect->img);
    }
    _vEffect.clear();
}

void MissileEffect::update(void)
{
}

void MissileEffect::render(void)
{
    draw();
}

void MissileEffect::show(RECT rc)
{
    tagEffect effect;
    ZeroMemory(&effect, sizeof(tagEffect));

    effect.img = new Image;
    effect.img->init("Resources/Images/Object/ME3.bmp", 0.0f, 0.0f, 1644, 137, 12, 1, true, RGB(255,0,255));
  
    effect.x = rc.left + (rc.right - rc.left);
    effect.y = rc.top;
    effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());

    _vEffect.push_back(effect);
}

void MissileEffect::draw(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        _viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
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

void MissileEffect::removeEffect(int arrNum)
{
    SAFE_DELETE(_vEffect[arrNum].img);
    _vEffect.erase(_vEffect.begin());
}

HRESULT MiniRocketEffect::init(void) {
	return S_OK;
}

void MiniRocketEffect::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->img);
	}
	_vEffect.clear();
}

void MiniRocketEffect::update(void)
{
}

void MiniRocketEffect::render(void)
{
	draw();
}

void MiniRocketEffect::show(RECT rc)
{
	tagEffect effect;
	ZeroMemory(&effect, sizeof(tagEffect));

	effect.img = new Image;
	effect.img->init("Resources/Images/Object/MissileEffect.bmp", 0.0f, 0.0f, 390, 63, 6, 1, true, RGB(50, 150, 200));
	effect.x = rc.left + (rc.right - rc.left);
	effect.y = rc.top;
	effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());

	_vEffect.push_back(effect);
}

void MiniRocketEffect::draw(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
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

void MiniRocketEffect::removeEffect(int arrNum)
{
	SAFE_DELETE(_vEffect[arrNum].img);
	_vEffect.erase(_vEffect.begin());
}

HRESULT BeamEffect::init(void)
{
    return S_OK;
}

void BeamEffect::release(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        SAFE_DELETE(_viEffect->img);
    }
    _vEffect.clear();
}

void BeamEffect::update(void)
{
}

void BeamEffect::render(void)
{
    draw();
}
//???????? why rc? 
//?? ?????? ?????????? ?????? ???? 
void BeamEffect::show(RECT rc)
{
    tagEffect effect;
    ZeroMemory(&effect, sizeof(tagEffect));

    effect.img = new Image;
    effect.img->init("Resources/Images/Object/Slash.bmp", 0.0f, 0.0f, 320,100,4, 1, true, RGB(255, 0, 255));
    effect.x = rc.left + (rc.right - rc.left);
    effect.y = rc.top;
    effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());

    _vEffect.push_back(effect);
}

void BeamEffect::draw(void)
{
    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        _viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
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

void BeamEffect::removeEffect(int arrNum)
{
    SAFE_DELETE(_vEffect[arrNum].img);
    _vEffect.erase(_vEffect.begin());
}
