#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SecondScene.h"

class MainGame : public GameNode
{
private:
    StartScene* _start;
    SecondScene* _second;
    GameNode* _currentScene;

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

public:
    MainGame() : _currentScene(nullptr) {}
    ~MainGame() {}
};
