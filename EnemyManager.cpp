#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp",
        0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
	setMinion();

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
}

void EnemyManager::update(void)
{
	for(_viMinion = _vMinion.begin();_viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
}

void EnemyManager::render(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
}

vector<Enemy*>& EnemyManager::getEnemies()
{
	return _vMinion;
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion;
			jellyFish->init("해파리", PointMake(150 + j * 200, 100 + i * 100));
			_vMinion.push_back(jellyFish);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion2;
			jellyFish->init("해파리", PointMake(750 + j * 200, 500 + i * 100));

			_vMinion.push_back(jellyFish);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Enemy* jellyFish;
		jellyFish = new Minion3;

		jellyFish->init("해파리", i);

		_vMinion.push_back(jellyFish);
	}
}

void EnemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin()+arrNum);
}
