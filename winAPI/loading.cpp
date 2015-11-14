#include "StdAfx.h"
#include "loading.h"

////////////////////// 로드 아이템 //////////////////////

loadItem::loadItem(void)
{
}

loadItem::~loadItem(void)
{
}

//이미지 로드 아이템
HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOADING_KIND_IMAGE_00;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_IMAGE_01;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_IMAGE_02;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_FRAMEIMAGE_00;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	_kind = LOADING_KIND_FRAMEIMAGE_01;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}


////////////////////// 로딩 클래스 //////////////////////

loading::loading(void)
{
}

loading::~loading(void)
{
}

HRESULT loading::init(void)
{
	gameNode::init();

	//백그라운드
	_background = IMAGEMANAGER->addImage("bg_loading", "ImageResource/bg_loading.bmp", WINSIZEX, WINSIZEY, false);

	_loadingBar = new progressBar;
	_loadingBar->init("ui_state_spBar_top", "ui_state_hpbar_top", 180, 800, 1200, 30);
	_loadingBar->setGauge(0, 0);

	_current = 0;

	return S_OK;
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);
	_vLoadItem.push_back(item);
}

void loading::release(void)
{
	gameNode::release();
}

void loading::update(void)
{
	_loadingBar->update();
}

void loading::render(void)
{
	_background->render(getMemDC());
	_loadingBar->render(getMemDC());
}

BOOL loading::loadNext(void)
{
	//아이템 갯수가 벡터 사이즈 이상 넘어가면 펄쓰~~~
	if (static_cast<unsigned int>(_current) >= _vLoadItem.size())
	{
		return false;
	}

	//여기오면 로딩중~~
	loadItem* item = _vLoadItem[_current];
	switch (item->getLoadingKind())
	{
		case LOADING_KIND_IMAGE_00:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.width, imageResource.height);
		}
		break;

		case LOADING_KIND_IMAGE_01:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.fileName,
				(float)imageResource.x, (float)imageResource.y,
				imageResource.width, imageResource.height, imageResource.trans,
				imageResource.transColor);
		}
		break;
		
		case LOADING_KIND_IMAGE_02:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addImage(imageResource.keyName, imageResource.fileName,
				imageResource.width, imageResource.height, imageResource.trans,
				imageResource.transColor);
		}
		break;
		
		case LOADING_KIND_FRAMEIMAGE_00:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addFrameImage(imageResource.keyName, imageResource.fileName,
				(float)imageResource.x, (float)imageResource.y,
				imageResource.width, imageResource.height,
				imageResource.frameX, imageResource.frameY,
				imageResource.trans,
				imageResource.transColor);
		}
		break;

		case LOADING_KIND_FRAMEIMAGE_01:
		{
			tagImageResource imageResource = item->getImageResource();
			IMAGEMANAGER->addFrameImage(imageResource.keyName, imageResource.fileName,
				imageResource.width, imageResource.height,
				imageResource.frameX, imageResource.frameY,
				imageResource.trans,
				imageResource.transColor);
		}
		break;

		case LOADING_KIND_SOUND_00:
			break;
	}

	//로딩바 이미지 변경
	_loadingBar->setGauge((float)_current, (float)_vLoadItem.size());

	//카운트
	_current++;

	return true;
}
