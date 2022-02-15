#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "AniTestScene.h"
#include "ShootingEffect.h"

class SecondScene :public GameNode
{
private:
    Rocket* _player;
    EnemyManager* _em;

    AniTestScene* _aniTest;
    MissileEffect* _missileEffect;
    BeamEffect* _beamEffect;

    float _upX, _upY;
    float _downX, _downY;
    int _enemyAttCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
    void collision(void);
	SecondScene() {}
	~SecondScene(){}
};