#pragma once
#include "Rocket.h"
#include "EnemyManager.h"
#include "EffectManager.h"

class Collision
{
private:
	Rocket* _rocket;
	EnemyManager* _em;
	EffectManager* _efxm;
	RECT rc;
public:
	HRESULT init(Rocket* rocket,EnemyManager* em,EffectManager* efxm);
	void update(void);
public:
	Collision() {}
	~Collision() {}
};