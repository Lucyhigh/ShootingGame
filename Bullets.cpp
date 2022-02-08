#include "Stdafx.h"
#include "Bullets.h"

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		// 메모리를 0으로 초기화(메모리 주소, 메모리 블럭 사이즈) : 메모리 블럭 수 만큼, 메모리 주소의 메모리를 0으로 초기화
		ZeroMemory(&bullet, sizeof(tagBullet));

		bullet.img = new Image;
		bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
			416, 64, 13, 1, true, MGT);
		bullet.fire = false;
		bullet.speed = 5.0f;
		_vBullet.push_back(bullet);
	}
	_bulletTick = 7.0f;

	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Missile::update(void)
{
	move();
}

void Missile::render(void)
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x - 15;
		_viBullet->y = _viBullet->fireY = y - 90;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void Missile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire)continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
	}
}

void Missile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		// 프레임 돌리기 
		if (_bulletTick <= GetTickCount())
		{
			_bulletTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
		}

		// 위치 옮기기
		_viBullet->y -= _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}
// 미사일 M1 ------------------------------------------------------------------------------
HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();
}

void MissileM1::render(void)
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new Image;
	bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));

	bullet.fire = false;
	bullet.speed = 4.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y - 70;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		// 위치 옮기기
		_viBullet->y -= _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void MissileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

// 미사일 M2 ------------------------------------------------------------------------------
HRESULT MissileM2::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	_bulletIndex = 0;
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));

		bullet.img = new Image;
		bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
			416, 64, 13, 1, true, MGT);
		bullet.fire = false;
		bullet.speed = 5.0f;
		bullet.index = i;
		_vBullet.push_back(bullet);
	}
	_bulletTick = 7.0f;
	return S_OK;
}

void MissileM2::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void MissileM2::update(void)
{
	move();
}

void MissileM2::render(void)
{
	draw();
}

void MissileM2::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x - 15;
		_viBullet->y = _viBullet->fireY = y - 90;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
	}
}

void MissileM2::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		// 프레임 돌리기 
		if (_bulletTick <= GetTickCount())
		{
			_bulletTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
		}

		_viBullet->x = cosf((_viBullet->index *(120 / _bulletMax) + 35)*PI / 180.0f) * _viBullet->speed + _viBullet->x;
		_viBullet->y = -sinf((_viBullet->index*(120 / _bulletMax) + 35)*PI / 180.0f) * _viBullet->speed + _viBullet->y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		//사거리 밖으로 나갔음
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

void MissileM2::draw(void)
{
	cout << _vBullet.size() << endl;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire)continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
	}
}
//============================================================================================mini
HRESULT MissileM3::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	_bulletIndex = 0;
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));

		bullet.img = new Image;
		bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
			416/2, 64/2, 13, 1, true, MGT);
		bullet.fire = false;
		bullet.speed = 10.0f;
		bullet.index = i;
		_vBullet.push_back(bullet);
	}
	_bulletTick = 7.0f;
	return S_OK;
}

void MissileM3::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void MissileM3::update(void)
{
	move();
}

void MissileM3::render(void)
{
	draw();
}

void MissileM3::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x+15 - 25*_viBullet->index;
		_viBullet->y = _viBullet->fireY = y - 90;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
	}
}

void MissileM3::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		if (_bulletTick <= GetTickCount())
		{
			_bulletTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
		}

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

void MissileM3::draw(void)
{
	cout << _vBullet.size() << endl;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire)continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
	}
}
//============================================================================================

HRESULT MissileM4::init(int count, float range)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new Image;
	bullet.img->init = IMAGEMANAGER->addImage("부스터", "Resources/Images/Object/Rocket.bmp",52*2, 62*2, true, RGB(255, 0, 255));


	_bulletTick = 7.0f;
	//_count = _index = 0;
	return S_OK;
}

void MissileM4::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void MissileM4::update(void)
{

}

void MissileM4::render(void)
{
	draw();

}

void MissileM4::shield(float x, float y)
{

	_x = x;
	_y = y;

	_rc = RectMakeCenter((int)_x, (int)_y, _img->getFrameWidth(), _img->getFrameHeight());
}

void MissileM4::draw(void)
{
	/*if (_bulletTick <= GetTickCount())
	{
		_bulletTick = GetTickCount();
		_img->setFrameX(_img->getFrameX() + 1);
		if (_img->getFrameX() >= _img->getMaxFrameX())
		{
			_img->setFrameX(0);
		}
	}
	_rc = RectMakeCenter(*_x, *_y + 180, _img->getFrameWidth(), _img->getFrameHeight());
	IMAGEMANAGER->frameRender("부스터", getMemDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());*/
}
