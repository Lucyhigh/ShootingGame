#pragma once
#include "GameNode.h"
#include "Effect.h"
class EffectManager : public GameNode
{
private:
	typedef vector<Effect*> vEffect;
	typedef vector<Effect*>::iterator viEffect;
	vEffect _vEffect;
	viEffect _viEffect;
	float _x, _y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void slashEffect(POINT point);
	void dustEffect(POINT point);
	void removeEffect(int index);
	EffectManager() {}
	~EffectManager() {}
};

