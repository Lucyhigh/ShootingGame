#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void)
{
	IMAGEMANAGER->addFrameImage("슬래쉬", "Resources/Images/Object/Slash.bmp",
		0.0f, 0.0f, 320, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("먼지", "Resources/Images/Object/Dust.bmp",
		0.0f, 0.0f, 450, 40, 5, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void EffectManager::release(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); _viEffect++)
	{
		(*_viEffect)->release();
		SAFE_DELETE(*_viEffect);
	}
}

void EffectManager::update(void)
{
	vector<int> indexesToRemove;
	for(int i=0; i < _vEffect.size(); ++i)
	{
		_vEffect[i]->update();
		if (_vEffect[i]->getIsDone())
		{
			indexesToRemove.push_back(i);
		}
	}

	for (int i = 0; i < indexesToRemove.size(); ++i)
	{
		removeEffect(indexesToRemove[i]);
	}

	/*_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); _viEffect++)
	{
		(*_viEffect)->update();
		if ((*_viEffect)->getIsDone())
		{
			_vEffect.erase(_viEffect);
		}
	}*/
}

void EffectManager::render(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); _viEffect++)
	{
		(*_viEffect)->render();
	}
}

void EffectManager::slashEffect(POINT point)
{
	Effect* slash = new Effect;
	slash->init("슬래쉬", point);
	_vEffect.push_back(slash);
}

void EffectManager::dustEffect(POINT point)
{
	Effect* dust = new Effect;
	dust->init("먼지", point);
	_vEffect.push_back(dust);
}

void EffectManager::removeEffect(int arrNum)
{
	_vEffect[arrNum]->release();
	SAFE_DELETE(_vEffect[arrNum]);
	_vEffect.erase(_vEffect.begin() + arrNum);
}
