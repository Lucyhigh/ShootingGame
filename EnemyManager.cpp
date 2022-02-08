#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp",
        0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
	setMinion();
	setMinion2();
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
			//jellyFish->init("해파리", PointMake(200 + j * 200, 100 + i * 100));
			//_vMiniom.push_back(jellyFish);
		}
	}
}
void EnemyManager::setMinion2(void)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Enemy* jellyFish;
            jellyFish = new Minion;
            jellyFish->init("해파리", PointMake(200+cos(30*i* PI/180)+300, 200+-sin(30 * j* PI / 180)+100));
            _vMiniom.push_back(jellyFish);
        }
    }
}