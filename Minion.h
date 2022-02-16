#pragma once
#include "Enemy.h"
#include "ProgressBar.h"
class Minion :public Enemy
{
private:
    int _reverse;
    int _speed;
public:
    virtual void move(void);
    Minion();
    virtual ~Minion();
};

class Minion2 :public Enemy
{
public:
    virtual void move(void);
    Minion2() {}
    virtual ~Minion2() {}
};

class Minion3 :public Enemy
{
public:
    virtual void move(void);
    Minion3() {}
    virtual ~Minion3() {}
};
class Minion4 :public Enemy
{
private:
	int _hp;
public:
    virtual void move(void);
    Minion4() : _hp(10) {}
    virtual ~Minion4() {}
	int GetHP() { return _hp; }
	void SetHP(int hp) { _hp = hp; }
};