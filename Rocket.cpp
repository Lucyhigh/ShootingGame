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
	_missile2 = new MissileM2;
	_missile2->init(8, 700);
	_missile3 = new MissileM3;
	_missile3->init(3, 700);
	BULLETTYPE _bulletType;
	_bulletType = NORMAL;

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	_missile->release();
	_missile2->release();
	_missile3->release();
	SAFE_DELETE(_flame);
	SAFE_DELETE(_missile);
	SAFE_DELETE(_missile2);
	SAFE_DELETE(_missile3);
}

void Rocket::update(void)
{
	_flame->update();
	_missile->update();
	_missile2->update();
	_missile3->update();
	
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
				_missile2->fire(_x, _y);
				break;
			case 2:
				_missile3->fire(_x, _y);
				break;
			case 3:
				_missile3->fire(_x, _y);
				break;
			case 4:
				_missile3->fire(_x, _y);
				break;
			case 5:
				_missile3->fire(_x, _y);
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
	_missile2->render();
	_missile3->render();
}