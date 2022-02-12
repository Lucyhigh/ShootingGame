#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"

#define ROCKET_SPEED 3.0f
#define ROCKET_BULLET 30
enum EWeapon
{
	MISSILE,
	SHOT,
	MINIROCKET,
	BEAM
};
class Rocket : public  GameNode
{
private :
	Image* _image;
	RECT _rc;
	Flame* _flame;
	MissileM1* _missile;
	MissileM2* _shotgun;
	MissileM3* _miniRocket;
	Beam* _beam;
	EWeapon _setWeapon;
	ProgressBar* _hpBar;

	float _x, _y;
	float _currentHp;
	float _maxHp;
	bool _beamIrradiation;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void removeMissile(int arrNum);

	MissileM1* getMissile(void) { return _missile; }
	Beam* getBeam(void) { return _beam; }
	//로켓이 맞는지 알려줄 렉트
	RECT getRect(void) { return _rc; }

	inline void hitDamage(float damage)
	{
		if (_currentHp <= 0)
		{
			_currentHp = 0;
			return;
		}
	}
public:
	Rocket() {}
	~Rocket() {}
};

