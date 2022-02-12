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

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	_rocket->release();
	_em->release();
	SAFE_DELETE(_rocket);
	SAFE_DELETE(_em);
}

void MainGame::update(void)
{
	GameNode::update();

	_rocket->update();
	_em->update();
	collision();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	IMAGEMANAGER->render("½´ÆÃ ¸Ê", getMemDC());
	_rocket->render();
	_em->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}

