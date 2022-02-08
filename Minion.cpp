#include "Stdafx.h"
#include "Minion.h"

void Minion::move(void)
{
	_x -= _speed+RND->getInt(2);
	_y += _speed+RND->getInt(2);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

Minion::Minion()
{

}

Minion::~Minion(){
}

void Minion2::move(void)
{
	_x += _speed * _reverse;
	if (_x >= WINSIZE_X -20 || _x <= 20) _reverse *= -1;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

Minion2::Minion2()
{
	_reverse = 1;
}

Minion2::~Minion2()
{
}

void Minion3::move(void)
{
	_speed += 0.02f;
	_x = cosf((_speed * 36 - 90)*PI / 180.0f) * 200 + WINSIZE_X / 2;
	_y = -sinf((_speed * 36 - 90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

Minion3::Minion3()
{

}

Minion3::~Minion3()
{
}
