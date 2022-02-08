#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"


#define ROCKET_SPEED 3.0f
#define ROCKET_BULLET 30
enum BULLETTYPE
{
	NORMAL,
	SHOT,//클래스 무작정 늘리지말고 일단 변경해보고 클래스 만들기
	MINIROCKET,
	SHIELD,
	GUIDED,
	LASER
};
class Rocket : public  GameNode
{
private :
	Image* _image;
	RECT _rc;
	float _x, _y;
	int _bulletType;
	Flame* _flame;

	MissileM1* _missile;
	//Missile*  _missileM1;

public:
	Rocket() {}
	~Rocket() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getFlameX() 
	{ return IMAGEMANAGER->findImage("부스터")->getX(); }

	void setFlameX(float _x) 
	{
		IMAGEMANAGER->findImage("부스터")->setX(_x);
	}

	float getFlameY()
	{
		return IMAGEMANAGER->findImage("부스터")->getY();
	}

	void setFlameY(float _y)
	{
		IMAGEMANAGER->findImage("부스터")->setY(_y);
	}

};

