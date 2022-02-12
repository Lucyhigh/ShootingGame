#pragma once
#include "GameNode.h"
#include "Enemy.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	vEnemy _vMinion;
	viEnemy _viMinion;
	ProgressBar* _minionHpBar;
	float _x, _y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setMinion(void);
	void removeMinion(int arrNum);

	//참조를 통해 벡터만듬
	//로켓이 어떠한 대상과 만나는지 알수없으면 알수없음
	vector<Enemy*> getMinion(void) { return _vMinion; }
public:
	EnemyManager() {}
	~EnemyManager() {}
};

