#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "TileMap.h"
#include "EnemyManager.h"

class MainGame : public GameNode
{
private:
	Rocket* _rocket;
	TileMap* _tileMap;
	EnemyManager* _em;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};
