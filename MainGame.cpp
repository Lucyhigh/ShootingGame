#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	IMAGEMANAGER->addImage("½´ÆÃ ¸Ê", "Resources/Images/BackGround/ShootingBG.bmp", WINSIZE_X, WINSIZE_Y);

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();
	_efxm = new EffectManager;
	_efxm->init();
	_collision = new Collision;
	_collision->init(_rocket,_em,_efxm);
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	_rocket->release();
	SAFE_DELETE(_rocket);
	_em->release();
	SAFE_DELETE(_em);
	_efxm->release();
	SAFE_DELETE(_efxm);	
}

void MainGame::update(void)
{
	GameNode::update();
	_rocket->update();
	_em->update();
	_efxm->update();
	_collision->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	IMAGEMANAGER->render("½´ÆÃ ¸Ê", getMemDC());
	TIMEMANAGER->render(getMemDC());
	_rocket->render();
	_em->render();
	_efxm->render();
	this->getBackBuffer()->render(getHDC());
}

