#include "Stdafx.h"
#include "Image.h" // �׷��ֱ� ���� ����, �߻�ȭ�� �����ϰ� ����� ���� ����. 

// ���� �����带 ����ϱ� ���� ���̺귯�� �߰� 
#pragma comment (lib,"msimg32.lib")

// �����Ҵ��� ���� ��ӹ��� Ŭ�������� ������ ȣ���Ҷ� 
// �̴ϼȶ����� �ʱ�ȭ�� ���� �ֿ켱������ �ʱ�ȭ�� �϶�� �ǹ� . 
Image::Image() : _imageInfo(NULL)
				,_fileName(NULL)
				,_isTrans(FALSE)
				,_transColor(RGB(0,0,0))
				,_blendImage(NULL)
				
{
}

// �̹��� �ʱ�ȭ
HRESULT Image::init(int width, int height)
{
	// �����͸� ����ϱ⶧���� if�� �ѹ� �� Ȯ���Ѵ�. 
	// ���ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ��������� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);//1
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);//2
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸�
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// ���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// ���ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ��������� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE; //
	_imageInfo->resID = resID; // ����� ���ҽ�ID
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance,MAKEINTRESOURCE(_imageInfo)); // _imageInfo res���� ����
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸� - ���ҽ� ������� ����. 
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// ���ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ��������� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // ���Ϸε� 
	_imageInfo->resID = 0; // ���ҽ� ���̵�� ����
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,IMAGE_BITMAP,
		width,height,LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸� - ����/���ڿ� Ȯ�� 
	// _fileName = fileName; ->const�� �״�� ����� �� ���⶧����, �Ʒ�ó�� ����.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // ���� ��� �� ���� 1ĭ �Ǽ� ������
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


// ������ �̹��� �ʱ�ȭ
HRESULT Image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{

	// ���ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ��������� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // ���Ϸε� 
	_imageInfo->resID = 0; // ���ҽ� ���̵�� ����
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸� - ����/���ڿ� Ȯ�� 
	// _fileName = fileName; ->const�� �״�� ����� �� ���⶧����, �Ʒ�ó�� ����.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // ���� ��� �� ���� 1ĭ �Ǽ� ������
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
	
}

HRESULT Image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// ���ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ��������� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // ���Ϸε� 
	_imageInfo->resID = 0; // ���ҽ� ���̵�� ����
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX-1;
	_imageInfo->maxFrameY = maxFrameY-1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// ���� �̸� - ����/���ڿ� Ȯ�� 
	// _fileName = fileName; ->const�� �״�� ����� �� ���⶧����, �Ʒ�ó�� ����.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // ���� ��� �� ���� 1ĭ �Ǽ� ������
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// ���ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ��������� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// DC ��������
	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // ���Ϸε� 
	_imageInfo->resID = 0; // ���ҽ� ���̵�� ����
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// ���� �̸� - ����/���ڿ� Ȯ�� 
	// _fileName = fileName; ->const�� �״�� ����� �� ���⶧����, �Ʒ�ó�� ����.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // ���� ��� �� ���� 1ĭ �Ǽ� ������
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// ���ĺ����� �ʱ�ȭ
HRESULT Image::initForAlphaBlend(void)
{

	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0; // ȥ�պ��� ������
	_blendFunc.AlphaFormat = 0; // �̹��� + �ҽ� ���� or �̹��� ���� ����
	_blendFunc.BlendOp = AC_SRC_OVER; // ��Ʈ�� �̹��� ��Ʈ �� 24 or 32 �����
	

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE; // ���Ϸε� 
	_blendImage->resID = 0; // ���ҽ� ���̵�� ����
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap	(hdc,_imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	
	// DC����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// ���� �÷�Ű ����
void Image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

// ���� 
void Image::release(void) // �����͸� ����Ѵٸ� ����(release)�� �Ű澲��.
{
	if (_imageInfo) // �̹����� ������
	{
		// �̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}


	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
	}
}

// ���� (0.0�� �׷���)
void Image::render(HDC hdc)
{
	if (_isTrans) // ���� ���� �͵�. �÷��̾�, ������Ʈ ���...
	{
		// ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ� 
		GdiTransparentBlt // ���������� �޸𸮿� ������.
		(
			hdc,					// ������ ����� DC(ȭ��DC(ȭ�鿡 ������))
			0, 0,					// ����� ��ǥ ���� : X, Y
			_imageInfo->width,		// ������ �̹��� ũ�� : ����, ����
			_imageInfo->height,
		//------------------------------------------------------------------
			_imageInfo->hMemDC,		// ����� ����� �޸�DC
			0,0,					// ���� ���� ���� : X, Y
			_imageInfo->width,		// ���� ���� ũ�� : ����, ���� 
			_imageInfo->height,
		//------------------------------------------------------------------
			_transColor				// ������ �� ������ ����
		);
	}

	// ����� ���� ��ǻ�� ����(�޸�)�� ���������� �����ϱ� ���� , else�� �����
	else // ��, ȭ�� ��ü������ ���� �̹��� �� ...
	{
		// DC���� �������� ���� ���Ӻ��� ���ִ� �Լ�
		// SRCCOPY : �ҽ� ������ ��󿵿��� �����Ѵ�.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

// ���� (���� ������ ��ǥ x,y �� �׷���)
void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) // ���� ���� �͵�. �÷��̾�, ������Ʈ ���...
	{
		// ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ� 
		GdiTransparentBlt // ���������� �޸𸮿� ������.
		(
			hdc,					// ������ ����� DC(ȭ��DC(ȭ�鿡 ������))
			destX, destY,			// ����� ��ǥ ���� : X, Y
			_imageInfo->width,		// ������ �̹��� ũ�� : ����, ����
			_imageInfo->height,
		//------------------------------------------------------------------
			_imageInfo->hMemDC,		// ����� ����� �޸�DC
			0, 0,					// ���� ���� ���� : X, Y
			_imageInfo->width,		// ���� ���� ũ�� : ����, ���� 
			_imageInfo->height,
		//------------------------------------------------------------------
			_transColor				// ������ �� ������ ����
		);
	}

	else // ��, ȭ�� ��ü������ ���� �̹��� �� ...
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//Ŭ���� ����
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) 
	{
		GdiTransparentBlt 
		(
			hdc,					// ������ ����� DC(ȭ��DC(ȭ�鿡 ������))
			destX, destY,			// ����� ��ǥ ���� : X, Y
			sourWidth,				// ������ �̹��� ũ�� : ����, ����
			sourHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// ����� ����� �޸�DC
			sourX, sourY,			// ���� ���� ���� : X, Y
			sourWidth,				// ���� ���� ũ�� : ����, ���� 
			sourHeight,
			//------------------------------------------------------------------
			_transColor				// ������ �� ������ ����
		);
	}

	else // ��, ȭ�� ��ü������ ���� �̹��� �� ...
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}


}

// ���ķ���(���)
void Image::alphaRender(HDC hdc, BYTE alpha)
{
	// ���ĺ����带 ó�� ����ϴ��� Ȯ��
	if (!_blendImage) initForAlphaBlend();
	
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1 ����ؾ��� DC�� �׷��� �ִ� ������ ������ �̹����� �׸���. 
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 0, 0, SRCCOPY);


		// 2 ���� �̹��� ����� ���� �� ������ �̹����� �׸���.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		// 3 ������ �̹����� ȭ�鿡 �׸��� 
		AlphaBlend
		(
		hdc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC, // ��������
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc // ��������
		);
	}
	else // ��, ȭ�� ��ü������ ���� �̹��� �� ...
	{
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC, // ��������
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc // ��������
		);
	}
}

// ���ķ���(�÷��̾�)
void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// ���ĺ����带 ó�� ����ϴ��� Ȯ��
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1 ����ؾ��� DC�� �׷��� �ִ� ������ ������ �̹����� �׸���. 
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 
			destX, destY, SRCCOPY
		);


		// 2 ���� �̹��� ����� ���� �� ������ �̹����� �׸���.
		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		// 3 ������ �̹����� ȭ�鿡 �׸��� 
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC, // ��������
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else{
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
	
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,						// ������ ����� DC(ȭ��DC(ȭ�鿡 ������))
			destX, destY,				// ����� ��ǥ ���� : X, Y
			_imageInfo->frameWidth,		// ������ �̹��� ũ�� : ����, ����
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,			// ����� ����� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// ���� ���� ���� : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		// ���� ���� ũ�� : ����, ���� 
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_transColor					// ������ �� ������ ����
		);
	}

	else // ��, ȭ�� ��ü������ ���� �̹��� �� ...
	{
		BitBlt(hdc, destX, destY, 
			_imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// �̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					// ������ ����� DC(ȭ��DC(ȭ�鿡 ������))
			destX, destY,			// ����� ��ǥ ���� : X, Y
			_imageInfo->frameWidth,				// ������ �̹��� ũ�� : ����, ����
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// ����� ����� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// ���� ���� ���� : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,				// ���� ���� ũ�� : ����, ���� 
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_transColor				// ������ �� ������ ����
		);
	}

	else // ��, ȭ�� ��ü������ ���� �̹��� �� ...
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY)
{
	//offset ���� ������ ��� ���� �Ѵ�.
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// �׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// �׷�����  DC ���� (ȭ��ũ��)
	RECT rcDest;

	// �׷��� �� ��ü ����
	int dramAreaX = dramArea->left;
	int dramAreaY = dramArea->top;
	int dramAreaW = dramArea->right - dramArea->left;
	int dramAreaH = dramArea->bottom - dramArea->top;

	// ���� ����
	for (int y = 0; y < dramAreaH; y += sourHeight)
	{
		// �ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > dramAreaH)
		{
			// �Ѿ �׸��� ����ŭ �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - dramAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// �׷����� ����
		rcDest.top = y + dramAreaY;
		rcDest.bottom = rcDest.top + sourHeight;


		// ���� ����
		for (int x = 0; x < dramAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > dramAreaW)
			{
				rcSour.right -= (x + sourWidth) - dramAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + dramAreaX;
			rcDest.right = rcDest.left + sourWidth;

			// Ŭ����

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				sourWidth, sourHeight);

		}//end of second
		
	}//end of for

}

void Image::loopAlphaRender(HDC hdc, const LPRECT dramaArea, int offsetX, int offsetY, BYTE alpha)
{



}
