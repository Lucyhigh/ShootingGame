#pragma once
#include "GameNode.h"
class StartScene :public GameNode
{
private:
	float _alpha;
	float _bgAlpha;
    int _alphaA;
    int _alphaNum;
	bool _isAlphaIncrese;
    Image* _image;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	StartScene() {}
	~StartScene() {}
};

