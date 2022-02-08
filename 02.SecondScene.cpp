#include "Stdafx.h"
#include "02.SecondScene.h"

HRESULT SecondScene::init(void)
{

	// 사운드 - 수정 할 것 
	_tempSound = new TempSoundTest;
	_tempSound->init();

	// 배경  // 루프랜더는 이미지 사이즈 기재.
	IMAGEMANAGER->addImage("루프배경", "Resources/Images/2ndScene/map_1Barn.bmp ", 7150, 800);
	

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_tempSound);

}

void SecondScene::update(void)
{
	// 사운드 
	_tempSound->update();


}


//============================================================================================
//       렌더 
//============================================================================================

void SecondScene::render(void)
{

	

}




void SecondScene::checkCollision(RECT &player, RECT &hurdle)
{
	if (IntersectRect(&temp, &player, &hurdle))
	{
		_tHpIndex--;  _turnip->setInvinsibility(true); _tState = INVINCIBILITY;
		_turnip->setRcMoveLeft(5);  _turnip->setRcMoveUp(8);
	}
}

void SecondScene::checkHeartFruit(RECT &player, RECT &heartFruit)
{
	if (IntersectRect(&temp, &player, &heartFruit))
	{
		_tHpIndex++; 
	}
}
