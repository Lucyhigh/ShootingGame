#include "Stdafx.h"
#include "AniTestScene.h"


HRESULT AniTestScene::init(void)
{
    //프레임 이미지가 아닌 그냥 이미지를 받고있다
    //_image = IMAGEMANAGER->addImage("꼬끼리", "Resources/Images/Object/Elephant.bmp",
    _image = IMAGEMANAGER->addImage("에너미1", "Resources/Images/Object/Enemy2.bmp",
        1072,276, true, RGB(255, 0, 255));
    _animationA = new Animation;

    //x 6 y 4 프레임 16/4
    _animationA->init(_image->getWidth(), _image->getHeight(), 67, 69);
    //_image->getWidth() / 6, _image->getHeight() / 4);<<연산은 쓰면 안좋다..
    //확장성을 위해 상수보다 변수를 쓰라햇지만 리소스엔 예외임 특히 나누기 개안조음
    _animationA->setPlayFrame(33, 49, false, true); 
    _animationA->setFPS(12);
   //_image = IMAGEMANAGER->addImage("회전문", "Resources/Images/startS/RotateDoor.bmp",
   //    723, 805, true, RGB(255, 91, 175));

    //x: 6, y: 4
  // _animationA->init(_image->getWidth(), _image->getHeight(), 241, 161);
  // _animationA->setDefPlayFrame(false, true);
  // _animationA->setFPS(12);
    return S_OK;
}

void AniTestScene::release(void)
{
    _animationA->release();
    SAFE_DELETE(_animationA);
}

void AniTestScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('B'))
    {
        _animationA->AniStart();
    }
    _animationA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniTestScene::render(void)
{
    _image->aniRender(getMemDC(), CENTER_X - 50, CENTER_Y, _animationA);
}

AniTestScene::AniTestScene()
{
}


AniTestScene::~AniTestScene()
{
}
