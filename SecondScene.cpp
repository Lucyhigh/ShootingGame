#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
    IMAGEMANAGER->addImage("필드 아래", "Resources/Images/BackGround/mapDown.bmp", WINSIZE_X, 5631 * 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("필드", "Resources/Images/BackGround/mapUp.bmp", WINSIZE_X, 5631 * 2, true, RGB(255, 91, 175));
    IMAGEMANAGER->addImage("게임 오버", "Resources/Images/Object/Gameover.bmp", 85 * 3, 18 * 3, true, RGB(255, 0, 255));
    _player = new Rocket;
    _player->init();
    _em = new EnemyManager;
    _em->init();

    _aniTest = new AniTestScene;
    _aniTest->init();

    _missileEffect = new MissileEffect;
    _missileEffect->init();

    _beamEffect = new BeamEffect;
    _beamEffect->init();

    _em->setRocketMemoryAddress(_player);
    _player->setEnemyManagerMemoryAddress(_em);

    _upX = 0.0f;
    _upY = -800.0f;
    _downX = 0.0f;
    _downY = -800.0f;
	return S_OK;
}

void SecondScene::release(void)
{
    _player->release();
    SAFE_DELETE(_player);
    _em->release();
    SAFE_DELETE(_em);

    _aniTest->release();
    SAFE_DELETE(_aniTest);
    _missileEffect->release();
    SAFE_DELETE(_missileEffect);
    _beamEffect->release();
    SAFE_DELETE(_beamEffect);
}

void SecondScene::update(void)
{
    _player->update();
    _em->update();
    collision();
    _aniTest->update();
    if (_player->getStatus())
    {
        if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        {
            if (_downX < 30) _downX += 0.25f;
        }

        if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        {
            if (_downX + 30 > 0) _downX -= 0.25f;
        }
        if (KEYMANAGER->isStayKeyDown(VK_UP))
        {
            _downY -= 0.2f;
        }

        if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        {
            _downY += 0.2f;
        }

        _upY -= 1.2f;
        _downY -= 1.2f;
    }

}

void SecondScene::render(void)
{
    RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
    RECT rc2 = { 0,0, WINSIZE_X, WINSIZE_Y };
    IMAGEMANAGER->findImage("필드 아래")->loopRender(getMemDC(), &rc1, _downX, _downY);
    IMAGEMANAGER->findImage("필드")->loopRender(getMemDC(), &rc2, _upX, _upY);
    if (_player->getStatus())
    {
    _em->render();
    _aniTest->render();
    _missileEffect->render();
    _beamEffect->render();
    _player->render();
    IMAGEMANAGER->render("게임오버", getMemDC(), 300, 530);
    }
    else
    {
        IMAGEMANAGER->render("게임오버", getMemDC(), 200, 730);
    }
}
