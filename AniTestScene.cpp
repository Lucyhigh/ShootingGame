#include "Stdafx.h"
#include "AniTestScene.h"


HRESULT AniTestScene::init(void)
{
    //������ �̹����� �ƴ� �׳� �̹����� �ް��ִ�
    //_image = IMAGEMANAGER->addImage("������", "Resources/Images/Object/Elephant.bmp",
    _image = IMAGEMANAGER->addImage("���ʹ�1", "Resources/Images/Object/Enemy2.bmp",
        1072,276, true, RGB(255, 0, 255));
    _animationA = new Animation;

    //x 6 y 4 ������ 16/4
    _animationA->init(_image->getWidth(), _image->getHeight(), 67, 69);
    //_image->getWidth() / 6, _image->getHeight() / 4);<<������ ���� ������..
    //Ȯ�强�� ���� ������� ������ ���������� ���ҽ��� ������ Ư�� ������ ��������
    _animationA->setPlayFrame(33, 49, false, true); 
    _animationA->setFPS(12);
   //_image = IMAGEMANAGER->addImage("ȸ����", "Resources/Images/startS/RotateDoor.bmp",
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
