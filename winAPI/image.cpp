#include "stdafx.h"
#include "image.h"

#pragma comment (lib, "msimg32.lib")

//멤버 이니셜 라이즈로 초기화
image::image(void) :_imageInfo(NULL), _fileName(NULL), _trans(false), _transColor(RGB(0, 0, 0)), _blendFunc({}), _blendImage(NULL),
hFile(nullptr), lpbmi(nullptr), bmfh({}), dwRead(NULL), dwInfoLength(NULL), lpDIBits(NULL)
{
}

image::~image(void)
{
	release();
}

//빈 비트맵 이미지 만든다
HRESULT	image::init(int width, int height)
{
	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//CreateCompatibleDC 
	//비트맵을 출력하기 위해서 메모리 DC를 만들어 준다

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성

	//이미지 정보 생성
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

	//투명 컬러 셋팅
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//로드타입
	_blendImage->resID = 0;						//리소스 ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//비트맵을 출력하기 위해 메모리 DC를 만들어 준다
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


//리소스로부터 읽어온다
HRESULT	image::init(const DWORD resID, int width, 
	int height, BOOL trans, COLORREF transColor)
{
	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
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

	//투명 컬러 셋팅
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	
	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//로드타입
	_blendImage->resID = 0;						//리소스 ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//비트맵을 출력하기 위해 메모리 DC를 만들어 준다
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//이미지 설정 (파일로부터 읽어온다)
HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
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

	//파일 경로 이름 복사~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//로드타입
	_blendImage->resID = 0;						//리소스 ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//비트맵을 출력하기 위해 메모리 DC를 만들어 준다
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//리소스 얻기에 실패하면...
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
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
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

	//파일 경로 이름 복사~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//로드타입
	_blendImage->resID = 0;						//리소스 ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//비트맵을 출력하기 위해 메모리 DC를 만들어 준다
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
//
//이미지 + 프레임 파일 초기화
HRESULT image::init(const char* fileName,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
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

	//파일 경로 이름 복사~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//로드타입
	_blendImage->resID = 0;						//리소스 ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//비트맵을 출력하기 위해 메모리 DC를 만들어 준다
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}


//이미지 + 프레임 파일 초기화
HRESULT image::init(const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면...
	if (fileName == NULL) return E_FAIL;

	//재초기화에 대비..
	if (_imageInfo != NULL) release();

	//이미지를 불러온다.////
	/*hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);	
	if (hFile == INVALID_HANDLE_VALUE) return E_FAIL;											
	ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);							
	dwInfoLength = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);									
	lpbmi = (LPBITMAPINFO)new BYTE[dwInfoLength];												
	ReadFile(hFile, lpbmi, dwInfoLength, &dwRead, NULL);*/
	/////

	//DC 얻는다
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 생성
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

	//파일 경로 이름 복사~~
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;				//로드타입
	_blendImage->resID = 0;						//리소스 ID
	_blendImage->hMemDC = CreateCompatibleDC(hdc);	//비트맵을 출력하기 위해 메모리 DC를 만들어 준다
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//얻은 DC 해제
	ReleaseDC(_hWnd, hdc);

	//리소스 얻기에 실패하면...
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}



//삭제
void image::release(void)
{
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		SelectObject(_imageInfo->hMemDC2, _imageInfo->hOBit2);
		DeleteObject(_imageInfo->hBit2);
		DeleteDC(_imageInfo->hMemDC2);

		//알파 블렌드 사용 이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		//투명 컬러 초기화
		_trans = false;
		_transColor = RGB(0, 0, 0);

		SAFE_DELETE(lpbmi);
		lpDIBits = nullptr;
	}
}


//투명 키 셋팅
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//렌더
void image::render(HDC hdc)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			(int)_imageInfo->x,	//복사될 좌표 시작점 X
			(int)_imageInfo->y,	//복사될 좌표 시작점 Y
			_imageInfo->width,	//복사될 크기 width
			_imageInfo->height,	//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			0, 0,				//복사 시작지점
			_imageInfo->width,	//복사될 영역지정 width
			_imageInfo->height,	//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			_imageInfo->width,	//복사될 크기 width
			_imageInfo->height,	//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			0, 0,				//복사 시작지점
			_imageInfo->width,	//복사될 영역지정 width
			_imageInfo->height,	//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
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
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			sourWidth,			//복사될 크기 width
			sourHeight,			//복사될 크기 height
			_imageInfo->hMemDC,			//복사대상 DC,
			sourX,				//복사 시작지점 x
			sourY,				//복사 시작지점 y
			sourWidth,			//복사될 영역지정 width
			sourHeight,			//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
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
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			sourWidth,			//복사될 크기 width
			sourHeight,			//복사될 크기 height
			hTempDC,			//복사대상 DC,
			sourX,				//복사 시작지점 x
			sourY,				//복사 시작지점 y
			sourWidth,			//복사될 영역지정 width
			sourHeight,			//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			hTempDC, sourX, sourY, SRCCOPY);
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//TransparentBlt도 있다
		//
		GdiTransparentBlt(hdc,	//복사할 장소의 DC
			(int)_imageInfo->x,	//복사될 좌표 시작점 X
			(int)_imageInfo->y,	//복사될 좌표 시작점 Y
			sourWidth,			//복사될 크기 width
			sourHeight,			//복사될 크기 height
			_imageInfo->hMemDC,	//복사대상 DC,
			sourX,				//복사 시작지점 x
			sourY,				//복사 시작지점 y
			sourWidth,			//복사될 영역지정 width
			sourHeight,			//복사될 영역지정 height
			_transColor);		//복사에서 제외할 색상 지정
	}
	else 
	{
		//BitBlt 는 DC간의 영역끼리 서로 고속복사를 해주는 함수이다.
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			sourWidth, sourHeight, 
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//루프렌더
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//옵셋 값이 음수인 경우 보정
	if(offsetX < 0 ) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if(offsetY < 0 ) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 소스의 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역
	RECT rcDest;

	//그려야할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프
	for(int y = 0 ; y < drawAreaH ; y += sourHeight)
	{
		//소스 영역 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스의 영역이 그리기 화면을 넘어갔다면
		if(y + sourHeight > drawAreaH)
		{
			//넘어간 양만큼 바텀 값을 올린다.
			rcSour.bottom -=  (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}	

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프
		for(int x = 0 ; x < drawAreaW ; x += sourWidth)
		{
			//소스의 영역 가로 계산
			rcSour.left	= (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스의 영역이 그리기 화면을 넘어갔다면
			if(x + sourWidth > drawAreaW)
			{
				//넘어간 양 만큼 라이트 값을 왼쪽으로..
				rcSour.right -=  (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			
			//그려지는 영역
			rcDest.left	= x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//그린다.
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top );
			
		}
	}
}


//루프렌더
void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, bool reverse, BYTE alpha, BOOL bAlphaFormat)
{
	//옵셋 값이 음수인 경우 보정
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 소스의 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역
	RECT rcDest;

	//그려야할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스의 영역이 그리기 화면을 넘어갔다면
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 양만큼 바텀 값을 올린다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스의 영역 가로 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스의 영역이 그리기 화면을 넘어갔다면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양 만큼 라이트 값을 왼쪽으로..
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//그린다.
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, reverse, alpha, bAlphaFormat);
		}
	}
}

//프레임 렌더
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


//알파렌더
void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//출력해야될DC에 그려져있는 내용을 Blend에 그린다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		//출력해야될 이미지를 Blend에 그린다.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//BlendDC를 출력해야 될 DC에 그린다.
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
		//출력해야될DC에 그려져있는 내용을 Blend에 그린다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//출력해야될 이미지를 Blend에 그린다.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//BlendDC를 출력해야 될 DC에 그린다.
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
		//출력해야될DC에 그려져있는 내용을 Blend에 그린다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//출력해야될 이미지를 Blend에 그린다.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, 0, 0, sourWidth, sourHeight, _transColor);

		//BlendDC를 출력해야 될 DC에 그린다.
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
		//출력해야될DC에 그려져있는 내용을 Blend에 그린다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//출력해야될 이미지를 Blend에 그린다.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//BlendDC를 출력해야 될 DC에 그린다.
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
		//출력해야될DC에 그려져있는 내용을 Blend에 그린다.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//출력해야될 이미지를 Blend에 그린다.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hTempDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//BlendDC를 출력해야 될 DC에 그린다.
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
		sourWidth,				//복사될 좌표 시작점 X
		0,						//복사될 좌표 시작점 Y
		-sourWidth-1,			//복사될 크기 width
		sourHeight,				//복사될 크기 height
		sourDC,					//복사대상 DC,
		0,						//복사 시작지점 x
		0,						//복사 시작지점 y
		sourWidth,				//복사될 영역지정 width
		sourHeight,
		SRCCOPY);

	SelectObject(sourDC, hOldSourBit);
	SelectObject(destDC, hOldDestBit);
	DeleteObject(sourDC);
	DeleteObject(destDC);

	return hResultBit;
}
