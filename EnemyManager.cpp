#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp",
        0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
	setMinion();
	//setMinion2();
	//setMinion3();
	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMiniom = _vMiniom.begin(); _viMiniom != _vMiniom.end(); ++_viMiniom)
	{
		(*_viMiniom)->release();
		SAFE_DELETE(*_viMiniom);
	}
}

void EnemyManager::update(void)
{
	_viMiniom = _vMiniom.begin();
	for(;_viMiniom != _vMiniom.end(); ++_viMiniom)
	{
		(*_viMiniom)->update();
	}
}

void EnemyManager::render(void)
{
	_viMiniom = _vMiniom.begin();
	for (; _viMiniom != _vMiniom.end(); ++_viMiniom)
	{
		(*_viMiniom)->render();
	}
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion;
			jellyFish->init("해파리", PointMake(RND->getFloat(200) + j * 200, RND->getFloat(300) + i * 100));
			_vMiniom.push_back(jellyFish);
		}
	}
}
void EnemyManager::setMinion2(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion2;
			jellyFish->init("해파리", PointMake(100 + j * 100, 300 + i * 100),3.0f);
			_vMiniom.push_back(jellyFish);
		}
	}
}
void EnemyManager::setMinion3(void)
{
	float x, y;

    for (int i = 0; i < 10; i++)
    {

		Enemy* jellyFish;
		jellyFish = new Minion3;

		x = cosf((i *36 - 90)*PI / 180.0f) * 200 + WINSIZE_X / 2;
		y = -sinf((i *36 - 90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;
		jellyFish->init("해파리", PointMake(x, y), i);
		_vMiniom.push_back(jellyFish);
        
    }
}
/*
 cosf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_X / 2;
 sinf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;


*/