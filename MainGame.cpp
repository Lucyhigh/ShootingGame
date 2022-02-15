#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
    GameNode::init(TRUE);
   
    _start = new StartScene;
    _start->init();

    _second = new SecondScene;
    _second->init();
    _currentScene = _start;
   // assert(_currentScene != nullptr);

    return S_OK;
}

void MainGame::release(void)
{
    GameNode::release();

    SAFE_DELETE(_start);
    SAFE_DELETE(_second);
}

void MainGame::update(void)
{
    GameNode::update();

    _currentScene->update();

   if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) _currentScene = _second;
   if (KEYMANAGER->isOnceKeyDown('W') ) _currentScene = _start;
}

void MainGame::render(void)
{
    PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
 
    _currentScene->render();
    TIMEMANAGER->render(getMemDC());

    this->getBackBuffer()->render(getHDC());
}

