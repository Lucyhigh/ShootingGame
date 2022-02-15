#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"

HRESULT EnemyManager::init(void)
{
    IMAGEMANAGER->addFrameImage("에너미1", "Resources/Images/Object/Enemy2.bmp",
        0.0f, 0.0f, 1072, 276, 16,2,true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("에너미2", "Resources/Images/Object/Enemy3.bmp",
        0.0f, 0.0f, 763, 40, 16, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("에너미3", "Resources/Images/Object/Enemy4.bmp",
        0.0f, 0.0f, 763,41, 16, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("적 미사일", "Resources/Images/Object/Bullet.bmp", 7 * 2, 7 * 2,
        true, RGB(255, 0, 255));


    setMinion();
    _bullet = new Bullet;
    _bullet->init("적 미사일", 30, 1000);

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
    _viMinion = _vMinion.begin();
    for (; _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->render();
    }
    _bullet->render();
}

void EnemyManager::setMinion(void)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            Enemy* jellyFish;
            jellyFish = new Minion;
            jellyFish->init("에너미2", PointMake(150 + j * 200, 100 + i * 100));
            _vMinion.push_back(jellyFish);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            Enemy* jellyFish;
            jellyFish = new Minion2;
            jellyFish->init("에너미3", PointMake(750 + j * 200, 200 + i * 200));

            _vMinion.push_back(jellyFish);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        Enemy* jellyFish;
        jellyFish = new Minion3;

        jellyFish->init("에너미1", i);

        _vMinion.push_back(jellyFish);
    }
}

void EnemyManager::removeMinion(int arrNum)
{

    SAFE_DELETE(_vMinion[arrNum]);
    _vMinion.erase(_vMinion.begin() + arrNum);
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
