#pragma once
#include "GameNode.h"
#include "TempSoundTest.h"


class SecondScene : public GameNode
{
private:
	TempSoundTest* _tempSound;

	

public:
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	
	// 충돌함수 
	void checkCollision(RECT &player, RECT &hurdle);

	void checkHeartFruit(RECT &player, RECT &heartFruit);



};

