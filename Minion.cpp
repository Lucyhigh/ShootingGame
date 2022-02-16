#include "Stdafx.h"
#include "Minion.h"

Minion::Minion():_speed(0),_reverse(1)
{
}

Minion::~Minion() {
}

void Minion::move(void)
{

    _y += RND->getInt(4)* _reverse;
   _x -= RND->getInt(4) * _reverse;
   
    if (_x >= WINSIZE_X - 20 || _x <= 20) _reverse *= -1;
    if (_y >= WINSIZE_X - 20 || _y <= 20) _reverse *= -1;
    _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Minion2::move(void)
{
    _x += RND->getFloat(5.0f);
    if (_x > WINSIZE_X + 50) _x = 0;
    _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Minion3::move(void)
{
    _speed += 0.02f;
    _x = cosf((_speed * 36 - 90)* PI / 180) * 200 + WINSIZE_X / 2;// +RND->getInt(200);
    _y = -sinf((_speed * 36 - 90)*  PI / 180) * 200 + WINSIZE_Y / 2;// +RND->getInt(200);

    _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Minion4::move(void)
{
}
