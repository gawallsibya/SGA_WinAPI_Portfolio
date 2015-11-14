#include "stdafx.h"
#include "image.h"

#pragma comment (lib, "msimg32.lib")

//��� �̴ϼ� ������� �ʱ�ȭ
image::image(void) :_imageInfo(NULL), _fileName(NULL), _trans(false), _transColor(RGB(0, 0, 0)), _blendFunc({}), _blendImage(NULL),
hFile(nullptr), lpbmi(nullptr), bmfh({}), dwRead(NULL), dwInfoLength(NULL), lpDIBits(NULL)
{
}

image::~image(void)
{
	release();
}

//�� ��Ʈ�� �̹��� �����
HRESULT	image::init(int width, int height)
{
	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC 
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_EMPTY;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	_fileName					= NULL;

	//���� �÷� ����
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//�ε�Ÿ��
	_blendImage->resID = 0;						//���ҽ� ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//��Ʈ���� ����ϱ� ���� �޸� DC�� ����� �ش�
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


//���ҽ��κ��� �о�´�
HRESULT	image::init(const DWORD resID, int width, 
	int height, BOOL trans, COLORREF transColor)
{
	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_RESOURCE;
	_imageInfo->resID			= resID;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	_fileName				= NULL;

	//���� �÷� ����
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	
	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//�ε�Ÿ��
	_blendImage->resID = 0;						//���ҽ� ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//��Ʈ���� ����ϱ� ���� �޸� DC�� ����� �ش�
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� ���� (���Ϸκ��� �о�´�)
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x				= x - (width / 2);
	_imageInfo->y				= y - (height / 2);
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//�ε�Ÿ��
	_blendImage->resID = 0;						//���ҽ� ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//��Ʈ���� ����ϱ� ���� �޸� DC�� ����� �ش�
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


HRESULT image::init(const char* fileName, int width, int height, 
BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hMemDC2			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hBit2			= getReversedBitmap(hdc, _imageInfo->hBit, width, height);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->hOBit2			= (HBITMAP)SelectObject(_imageInfo->hMemDC2, _imageInfo->hBit2);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width;
	_imageInfo->frameHeight		= height;
	_imageInfo->maxFrameX		= 0;
	_imageInfo->maxFrameY		= 0;

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//�ε�Ÿ��
	_blendImage->resID = 0;						//���ҽ� ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//��Ʈ���� ����ϱ� ���� �޸� DC�� ����� �ش�
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
//
//�̹��� + ������ ���� �ʱ�ȭ
HRESULT image::init(const char* fileName,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo					= new IMAGE_INFO;
	_imageInfo->loadType		= LOAD_FILE;
	_imageInfo->resID			= 0;
	_imageInfo->hMemDC			= CreateCompatibleDC(hdc);
	_imageInfo->hMemDC2			= CreateCompatibleDC(hdc);
	_imageInfo->hBit			= (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hBit2			= getReversedBitmap(hdc, _imageInfo->hBit, width, height);
	_imageInfo->hOBit			= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->hOBit2			= (HBITMAP)SelectObject(_imageInfo->hMemDC2, _imageInfo->hBit2);
	_imageInfo->x				= 0;
	_imageInfo->y				= 0;
	_imageInfo->currentFrameX	= 0;
	_imageInfo->currentFrameY	= 0;
	_imageInfo->width			= width;
	_imageInfo->height			= height;
	_imageInfo->frameWidth		= width / frameX;
	_imageInfo->frameHeight		= height / frameY;
	_imageInfo->maxFrameX		= frameX - 1;
	_imageInfo->maxFrameY		= frameY - 1;

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//�ε�Ÿ��
	_blendImage->resID = 0;						//���ҽ� ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//��Ʈ���� ����ϱ� ���� �޸� DC�� ����� �ش�
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


//�̹��� + ������ ���� �ʱ�ȭ
HRESULT image::init(const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����...
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ�� ���..
	if (_imageInfo != NULL) release();

	//�̹����� �ҷ��´�.////
	/*hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);	
	if (hFile == INVALID_HANDLE_VALUE) return E_FAIL;											
	ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);							
	dwInfoLength = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);									
	lpbmi = (LPBITMAPINFO)new BYTE[dwInfoLength];												
	ReadFile(hFile, lpbmi, dwInfoLength, &dwRead, NULL);*/
	/////

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hMemDC2 = CreateCompatibleDC(hdc);
	/*_imageInfo->hBit = CreateDIBSection(_imageInfo->hMemDC, lpbmi, DIB_RGB_COLORS, &lpDIBits, NULL, 0);
	ReadFile(hFile, lpDIBits, lpbmi->bmiHeader.biSizeImage, &dwRead, NULL);*/
	_imageInfo->hBit = (HBITMAP)LoadImageA(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hBit2 = getReversedBitmap(hdc, _imageInfo->hBit, width, height);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->hOBit2 = (HBITMAP)SelectObject(_imageInfo->hMemDC2, _imageInfo->hBit2);

	//���� ��� �̸� ����~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//�ε�Ÿ��
	_blendImage->resID = 0;						//���ҽ� ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//��Ʈ���� ����ϱ� ���� �޸� DC�� ����� �ش�
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ �����ϸ�...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}



//����
void image::release(void)
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		SelectObject(_imageInfo->hMemDC2, _imageInfo->hOBit2);
		DeleteObject(_imageInfo->hBit2);
		DeleteDC(_imageInfo->hMemDC2);

		//���� ���� ��� �̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		//���� �÷� �ʱ�ȭ
		_trans = false;
		_transColor = RGB(0, 0, 0);

		SAFE_DELETE(lpbmi);
		lpDIBits = nullptr;
	}
}


//���� Ű ����
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//����
void image::render(HDC hdc)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			(int)_imageInfo->x,	//����� ��ǥ ������ X
			(int)_imageInfo->y,	//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			0, 0,				//���� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			0, 0,				//���� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, destX, destY, 
			_imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, 
	int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			_imageInfo->hMemDC,			//������ DC,
			sourX,				//���� �������� x
			sourY,				//���� �������� y
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, destX, destY, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight, bool reverse)
{
	HDC hTempDC;
	if (reverse)
	{
		hTempDC = _imageInfo->hMemDC2;
	}
	else
	{
		hTempDC = _imageInfo->hMemDC;
	}
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			hTempDC,			//������ DC,
			sourX,				//���� �������� x
			sourY,				//���� �������� y
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			hTempDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//TransparentBlt�� �ִ�
		//
		GdiTransparentBlt(hdc,	//������ ����� DC
			(int)_imageInfo->x,	//����� ��ǥ ������ X
			(int)_imageInfo->y,	//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC,
			sourX,				//���� �������� x
			sourY,				//���� �������� y
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ������ ���� ����
	}
	else 
	{
		//BitBlt �� DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ��̴�.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//��������
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�ɼ� ���� ������ ��� ����
	if(offsetX < 0 ) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if(offsetY < 0 ) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� �ҽ��� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷����� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ����
	for(int y = 0 ; y < drawAreaH ; y += sourHeight)
	{
		//�ҽ� ���� ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�
		if(y + sourHeight > drawAreaH)
		{
			//�Ѿ �縸ŭ ���� ���� �ø���.
			rcSour.bottom -=  (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}	

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ����
		for(int x = 0 ; x < drawAreaW ; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left	= (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�
			if(x + sourWidth > drawAreaW)
			{
				//�Ѿ �� ��ŭ ����Ʈ ���� ��������..
				rcSour.right -=  (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			
			//�׷����� ����
			rcDest.left	= x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//�׸���.
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top );
			
		}
	}
}


//��������
void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, bool reverse, BYTE alpha, BOOL bAlphaFormat)
{
	//�ɼ� ���� ������ ��� ����
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� �ҽ��� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷����� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ���� ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �縸ŭ ���� ���� �ø���.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �� ��ŭ ����Ʈ ���� ��������..
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//�׸���.
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, reverse, alpha, bAlphaFormat);
		}
	}
}

//������ ����
void image::frameRender(HDC hdc, int destX, int destY)
{
	if(_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, 
			_imageInfo->frameHeight, _transColor);	
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY,
	int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if(_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, 
			_imageInfo->frameHeight, _transColor );	
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}


//���ķ���
void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//����ؾߵ�DC�� �׷����ִ� ������ Blend�� �׸���.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//BlendDC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha, BOOL bAlphaFormat)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (bAlphaFormat) _blendFunc.AlphaFormat = AC_SRC_ALPHA;
	if (_trans)
	{
		//����ؾߵ�DC�� �׷����ִ� ������ Blend�� �׸���.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//BlendDC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//����ؾߵ�DC�� �׷����ִ� ������ Blend�� �׸���.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, 0, 0, sourWidth, sourHeight, _transColor);

		//BlendDC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC,
			0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC,
			0, 0, sourWidth, sourHeight, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, BOOL bAlphaFormat)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (bAlphaFormat) _blendFunc.AlphaFormat = AC_SRC_ALPHA;
	if (_trans)
	{
		//����ؾߵ�DC�� �׷����ִ� ������ Blend�� �׸���.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//BlendDC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC,
			0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC,
			sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, bool reverse, BYTE alpha, BOOL bAlphaFormat)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (bAlphaFormat) _blendFunc.AlphaFormat = AC_SRC_ALPHA;

	HDC hTempDC;
	if (reverse)
	{
		hTempDC = _imageInfo->hMemDC2;
	}
	else
	{
		hTempDC = _imageInfo->hMemDC;
	}
	if (_trans)
	{
		//����ؾߵ�DC�� �׷����ִ� ������ Blend�� �׸���.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hTempDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//BlendDC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC,
			0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, hTempDC,
			sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani, bool reverse)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), reverse);
}

void image::aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, bool reverse, BYTE alpha, BOOL bAlphaFormat)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), reverse, alpha, bAlphaFormat);
}

//==== private
HBITMAP image::getReversedBitmap(HDC hdc, HBITMAP hBitmap, int sourWidth, int sourHeight)
{
	HDC sourDC = CreateCompatibleDC(hdc);
	HDC destDC = CreateCompatibleDC(hdc);
	HBITMAP hResultBit = CreateCompatibleBitmap(hdc, sourWidth, sourHeight);
	HBITMAP hOldSourBit = (HBITMAP)SelectObject(sourDC, hBitmap);
	HBITMAP hOldDestBit = (HBITMAP)SelectObject(destDC, hResultBit);

	StretchBlt(destDC, 
		sourWidth,				//����� ��ǥ ������ X
		0,						//����� ��ǥ ������ Y
		-sourWidth-1,			//����� ũ�� width
		sourHeight,				//����� ũ�� height
		sourDC,					//������ DC,
		0,						//���� �������� x
		0,						//���� �������� y
		sourWidth,				//����� �������� width
		sourHeight,
		SRCCOPY);

	SelectObject(sourDC, hOldSourBit);
	SelectObject(destDC, hOldDestBit);
	DeleteObject(sourDC);
	DeleteObject(destDC);

	return hResultBit;
}
