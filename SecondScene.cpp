#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("필드 아래", "Resources/Images/BackGround/mapDown.bmp", WINSIZE_X, 5631 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("필드", "Resources/Images/BackGround/mapUp.bmp", WINSIZE_X, 5627 * 2, true, RGB(255, 91, 175));
	IMAGEMANAGER->addImage("게임 오버", "Resources/Images/Object/Gameover.bmp", 85 * 3, 18 * 3, true, RGB(255, 0, 255));
	_player = new Rocket;
	_player->init();
	_em = new EnemyManager;
	_em->init();

	_aniTest = new AniTestScene;
	_aniTest->init();

	_missileEffect = new MissileEffect;
	_missileEffect->init();

	_miniRocketEffect = new MiniRocketEffect;
	_miniRocketEffect->init();

	_beamEffect = new BeamEffect;
	_beamEffect->init();

	_em->setRocketMemoryAddress(_player);
	_player->setEnemyManagerMemoryAddress(_em);

	_upX = 0.0f;
	_upY = -800.0f;
	_downX = 0.0f;
	_downY = -800.0f;
	_timer = 0.0f;
	_score = 0;
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

	_miniRocketEffect->release();
	SAFE_DELETE(_miniRocketEffect);

	_beamEffect->release();
	SAFE_DELETE(_beamEffect);
}

void SecondScene::update(void)
{
	_player->update();
	_em->update();
	_aniTest->update();
	collision();
	_timer += TIMEMANAGER->getElapsedTime();

	if (_player->getLive())
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_downX < 30) _downX += 0.2f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_downX + 30 > 0) _downX -= 0.2f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_downY -= 0.2f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_downY += 0.2f;
		}
		if (!_em->getClear())
		{
			_upY -= 1.2f;
			_downY -= 1.2f;
		}
	}
}

void SecondScene::render(void)
{
	char timer[256];
	char score[256];
	char clear[256];

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	RECT rc2 = { 0,0, WINSIZE_X, WINSIZE_Y };

	IMAGEMANAGER->findImage("필드 아래")->loopRender(getMemDC(), &rc1, _downX, _downY);
	IMAGEMANAGER->findImage("필드")->loopRender(getMemDC(), &rc2, _upX, _upY);

	//2번째 씬 타이머
	sprintf_s(timer, "WorldTime : %f", _timer);
	TextOut(getMemDC(), 0, 20, timer, strlen(timer));

	//점수
	sprintf_s(score, "Score : %d", _score);
	TextOut(getMemDC(), 540, 0, score, strlen(score));
	if (!_em->getClear())
	{
		if (_player->getLive())
		{
			_em->render();
			_missileEffect->render();
			_miniRocketEffect->render();
			_beamEffect->render();
			_player->render();
		}
		else
		{
			sprintf_s(score, "Your Score : %d", _score);
			TextOut(getMemDC(), 270, 510, score, strlen(score));
			IMAGEMANAGER->render("게임 오버", getMemDC(), 200, 530);
		}
	}
	else
	{
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		sprintf_s(clear, "! Game Clear !");
		TextOut(getMemDC(), 280, 350, clear, strlen(clear));
		sprintf_s(score, "Your Score : %d", _score);
		TextOut(getMemDC(), 270, 380, score, strlen(score));
		_aniTest->render();
	}
}
