#include "Stdafx.h"
#include "AniTestScene.h"


HRESULT AniTestScene::init(void)
{
   _image = IMAGEMANAGER->addImage("È¸Àü¹®", "Resources/Images/Object/RotateDoor.bmp",
       723, 805, true, RGB(255, 91, 175));

    _animationA = new Animation;
    _animationA->init(_image->getWidth(), _image->getHeight(), 241, 161);
    _animationA->setDefPlayFrame(false, true);
	_animationA->AniStart();
    return S_OK;
}

void AniTestScene::release(void)
{
    _animationA->release();
    SAFE_DELETE(_animationA);
}

void AniTestScene::update(void)
{
    _animationA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniTestScene::render(void)
{
    _image->aniRender(getMemDC(), CENTER_X-120, CENTER_Y, _animationA);
}

AniTestScene::AniTestScene()
{
}


AniTestScene::~AniTestScene()
{
}
