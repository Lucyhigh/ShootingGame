#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"


#define ROCKET_SPEED 3.0f
#define ROCKET_BULLET 30
enum BULLETTYPE
{
	NORMAL,
	SHOT,
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
	MissileM2* _missile2;
	MissileM3* _missile3;

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

