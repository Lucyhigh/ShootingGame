#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"
#define ENEMYCOMING 7
class Rocket;

class EnemyManager : public GameNode
{
private:
    typedef vector<Enemy*> vEnemy;
    typedef vector<Enemy*>::iterator viEnemy;

    vEnemy _vMinion;
    viEnemy _viMinion;
    ProgressBar* _minionHpBar;
    Bullet* _bullet;
    Rocket* _player;
    float _worldTimeCount;
    float _x, _y;
    float _timer;
	int _spawnIndex;
	bool _isclear;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

    void setMinion(void);
    void removeMinion(int arrNum);

    void minionBulletFire(void);
    void collision(void);
	bool getClear() { return _isclear; }
    //������ ���� ���͸���
    //������ ��� ���� �������� �˼������� �˼�����
    vector<Enemy*> getMinion(void) { return _vMinion; }

    Bullet* getBullet(void) { return _bullet; }
    void setRocketMemoryAddress(Rocket* rk) { _player = rk; }
public:
    EnemyManager();
    ~EnemyManager() {}
};

