#include "stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    IMAGEMANAGER->addImage("시작화면", "Resources/Images/BackGround/BG_loop.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("타이틀비행기","Resources/Images/BackGround/BG_Up.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("타이틀", "Resources/Images/BackGround/BG_title.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("시작버튼", "Resources/Images/BackGround/start.bmp", 85*3,18*3, true, RGB(255, 0, 255));
    _bgAlpha = 0;
    _alpha = 0;
    _isAlphaIncrese = false;
    return S_OK;
}

void StartScene::release(void){
}

void StartScene::update(void)
{
    _bgAlpha += 1.5f;

    if (_bgAlpha >= 225) _bgAlpha = 255;

    if (_bgAlpha == 255)
    {
        if (_alpha == 0 || _alpha == 255) _isAlphaIncrese = !_isAlphaIncrese;
        if (_isAlphaIncrese)_alpha += 1.0f; else _alpha -= 1.5f;
    }
}

void StartScene::render(void)
{
    IMAGEMANAGER->render("시작화면", getMemDC());
    IMAGEMANAGER->alphaRender("타이틀", getMemDC(), _bgAlpha);
    IMAGEMANAGER->render("타이틀비행기", getMemDC());
    IMAGEMANAGER->alphaRender("시작버튼", getMemDC(),200, 730, _alpha);
}
