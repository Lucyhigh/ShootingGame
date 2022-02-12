#include "Stdafx.h"
#include "Effect.h"

Effect::Effect(void) :_rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0), _currentFrameY(0),
_x(0.0f), _y(0.0f),
_rndTimeCount(0.0f), _worldTimeCount(0.0f)
{
}
HRESULT Effect::init(const char * imageName, POINT position)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y,
		_image->getFrameWidth(), _image->getFrameHeight());

	_x = position.x;
	_y = position.y;
	_isDone = false;
	return S_OK;
}

void Effect::release(void)
{
}

void Effect::update(void)
{
}

void Effect::render(void)
{
	draw();
	animation();
}

void Effect::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Effect::animation(void)
{
	cout << _isDone << endl;
	if (!_isDone)
	{
		if (_rndTimeCount + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;
			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_isDone = true;
			}
		}
	}
}

bool Effect::getIsDone(void)
{
	return _isDone;
}