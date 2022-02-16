#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"
EnemyManager::EnemyManager() :_worldTimeCount(0.0f), _timer(0.0f)
{
}
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("에너미1", "Resources/Images/Object/Enemy2.bmp",
		0.0f, 0.0f, 1072, 276, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미2", "Resources/Images/Object/Enemy3.bmp",
		0.0f, 0.0f, 763, 40, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미3", "Resources/Images/Object/Enemy4.bmp",
		0.0f, 0.0f, 763, 41, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스", "Resources/Images/Object/boss-idle.bmp",
		0.0f, 0.0f, 290 * 3, 127 * 3, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적 미사일", "Resources/Images/Object/Bullet.bmp", 7 * 2, 7 * 2,
		true, RGB(255, 0, 255));



	_bullet = new Bullet;
	_bullet->init("적 미사일", 30, 1000);
	_spawnIndex = 0;
	_isclear = false;
	return S_OK;
}

void EnemyManager::release(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
}

void EnemyManager::update(void)
{
	if (!this->getClear())_timer += TIMEMANAGER->getElapsedTime();
	if (_timer >= 10.0f)
	{
		_timer = 0.0f;
		_spawnIndex++;
		setMinion();
	}
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	minionBulletFire();
	_bullet->update();
}

void EnemyManager::render(void)
{
	//cout <<"월드"<< _worldTimeCount << endl;

	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
	cout << "시계는와치" << _timer << endl;
	cout << "스폰" << _spawnIndex << endl;

}

void EnemyManager::setMinion(void)
{
	if (_spawnIndex == 1 || _spawnIndex == 2 || _spawnIndex == 4|| _spawnIndex == 8 || _spawnIndex == 11 || _spawnIndex == 12)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Enemy* enemy = new Minion;
				enemy->init("에너미2", PointMake(150 + j * 200, 100 + i * 100));
				_vMinion.push_back(enemy);
			}
		}
	}
	else if (_spawnIndex % 3 == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Enemy* enemy2 = new Minion2;
				enemy2->init("에너미3", PointMake(750 + j * 200, 200 + i * 200));

				_vMinion.push_back(enemy2);
			}
		}
	}
	else if (_spawnIndex % 5 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			Enemy* enemy3 = new Minion3;

			enemy3->init("에너미1", i);

			_vMinion.push_back(enemy3);
		}
	}
	else if (_spawnIndex == 14)
	{
		Enemy* boss = new Minion4;
		boss->init("보스", PointMake(300, 200));
		_vMinion.push_back(boss);
	}
}

void EnemyManager::removeMinion(int arrNum)
{
	if (0 <= arrNum && arrNum < _vMinion.size())
	{
		Enemy* enemy = _vMinion[arrNum];
		Minion4* minion4 = dynamic_cast<Minion4*>(enemy);
		if (minion4 != nullptr)
		{
			if (minion4->GetHP() > 0)
				minion4->SetHP(minion4->GetHP() - 1);
			else
			{
				SAFE_DELETE(_vMinion[arrNum]);
				_vMinion.erase(_vMinion.begin() + arrNum);
				_isclear = true;
			}
		}
		else
		{
			SAFE_DELETE(_vMinion[arrNum]);
			_vMinion.erase(_vMinion.begin() + arrNum);
		}
	}
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2,
				_player->getPosition().x,
				_player->getPosition().y),
				RND->getFromFloatTo(2.0f, 4.0f));
		}
	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc, &_player->getRect()))
		{
			_bullet->removeBullet(i);
			_player->hitDamage(0.5f);
			break;
		}
	}
}