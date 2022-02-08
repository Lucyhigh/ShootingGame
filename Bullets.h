#pragma once
#include "GameNode.h"

struct tagBullet
{
	Image* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
	int index;
};


// 베열처럼 미리 장전해두고 발사 
class Missile : public GameNode
{
private :
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	
	float _bulletTick;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);


	void fire(float x, float y);
	void move(void);
	void draw(void);

	Missile() {};
	~Missile() {};
};

// 발사 할 때마다 만들고 삭제 (메모리 이득)
class MissileM1 :public GameNode
{
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _bulletTick;
	int _bulletMax;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void move(void);
	void draw(void);

	MissileM1() {};
	~MissileM1() {};
};

class MissileM2 : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _bulletTick;
	int _bulletMax;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void move(void);
	void draw(void);

	MissileM2() {};
	~MissileM2() {};
};
