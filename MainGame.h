#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

#include "Collision.h"
class MainGame : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;
	EffectManager* _efxm;
	Collision* _collision;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	MainGame() {}
	~MainGame() {}
};
