#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

class MainGame : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	virtual void collision(void);
public:
	MainGame() {}
	~MainGame() {}
};
