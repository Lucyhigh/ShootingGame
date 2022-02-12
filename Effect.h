#pragma once
#include "GameNode.h"
class Effect : public GameNode
{
private:
	Image* _image;
	RECT _rc;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;
	int _currentFrameX;
	int _currentFrameY;
	bool _isDone;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void animation(void);
	bool getIsDone(void);
public:
	Effect(void);
	~Effect(void) {}
};

