#include "Stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("비행기", "Resources/Images/Object/AirCrafts-idle.bmp",
        48, 44, true, RGB(255, 91, 175));
	_x = CENTER_X;
	_y = WINSIZE_Y-100;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	_flame = new Flame;
	_flame->init("부스트", &_x, &_y);

	_missile = new MissileM1;
	_missile->init(ROCKET_BULLET, 700);
	_shotgun = new MissileM2;
	_shotgun->init(8, 700);
	_miniRocket = new MissileM3;
	_miniRocket->init(3, 700);
	_beam = new Beam;
	_beam->init(1, 1.0f);

	_setWeapon = MISSILE;
	_currentHp = 10;
	_maxHp = 10;
	_hpBar = new ProgressBar;
	_hpBar->init(_x,_y,52,4);
	_beamIrradiation = false;
    _islive = true;
	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);

	_shotgun->release();
	SAFE_DELETE(_shotgun);

	_miniRocket->release();
	SAFE_DELETE(_miniRocket);

	_beam->release();
	SAFE_DELETE(_beam);

	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void Rocket::update(void)
{
	_flame->update();
	_missile->update();
	_shotgun->update();
	_miniRocket->update();
	_beam->update();
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGauge(_currentHp, _maxHp);

	if (KEYMANAGER->isOnceKeyDown('1')) hitDamage(1.0f);
	if (KEYMANAGER->isOnceKeyDown('2')) hitDamage(-1.0f);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X && _beamIrradiation ==false)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _beamIrradiation == false)
	{
		_x -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_F1))//일반
	{
		_setWeapon = MISSILE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))//산탄
	{
		_setWeapon = SHOT;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))//미니로켓 생성
	{
		_setWeapon = MINIROCKET;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))//레이저
	{
		_setWeapon = BEAM;
	}

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_missile->fire(_x, _y);
		}
		break;
	case SHOT:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_shotgun->fire(_x, _y);
		}
		break;
	case MINIROCKET:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_miniRocket->fire(_x, _y);
		}
		break;
	case BEAM:
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			_beamIrradiation = true;
			_beam->fire(_x, _y);
		}
		else _beamIrradiation = false;
		break;
	}	
}

void Rocket::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);

	_flame->render();
	_missile->render();
	_shotgun->render();
	_miniRocket->render();
	_beam->render();
	_hpBar->render();
}

void Rocket::removeMissile(int arrNum)
{
	switch (_setWeapon)
	{
	case MISSILE:
		_missile->removeBullet(arrNum);
		break;
	case SHOT:
		_shotgun->removeBullet(arrNum);
		break;
	case MINIROCKET:
		_miniRocket->removeBullet(arrNum);
		break;
	}
}

bool Rocket::getLive(void)
{
    return _islive;
}
