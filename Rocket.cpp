#include "Stdafx.h"
#include "Rocket.h"


HRESULT Rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp",
		52, 62, true, MGT);

	_x = CENTER_X;
	_y = WINSIZE_Y-100;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	_flame = new Flame;
	_flame->init("부스트", &_x, &_y);

	_missile = new MissileM1;
	_missile->init(ROCKET_BULLET, 700);
	BULLETTYPE _bulletType;
	_bulletType = NORMAL;
	//_missileM1 = new MissileM1;
	//_missileM1->init(1, 5.0f);

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	_missile->release();
	SAFE_DELETE(_flame);
	SAFE_DELETE(_missile);
}

void Rocket::update(void)
{
	_flame->update();
	_missile->update();

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
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

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		switch (_bulletType)
		{
			case 0:
				_missile->fire(_x, _y);
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))//일반
	{
		_bulletType = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))//산탄
	{
		_bulletType = 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))//미니로켓 생성
	{
		_bulletType = 2;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))//쉴드
	{
		_bulletType = 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))//유도 미사일
	{
		_bulletType = 4;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))//레이저
	{
		_bulletType = 5;
	}
}

void Rocket::render(void)
{
	cout << _bulletType << endl;
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_missile->render();
}