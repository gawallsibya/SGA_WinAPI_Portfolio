#include "stdafx.h"
#include "imageManager.h"

imageManager::imageManager(void)
{
}

imageManager::~imageManager(void)
{
}

//�¾�
HRESULT imageManager::init(void)
{
	return S_OK;
}

//����
void imageManager::release(void)
{
	deleteAll();
}

//Ű�� �����ؼ� �ʱ�ȭ
image* imageManager::addImage(std::string strKey, int width, int height)
{
	//������ �̹��� �ִ� ã�´�...
	image* img = findImage(strKey);

	//Ű���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹��� ����~
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ�����...
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� �� ����Ʈ�� �߰��Ѵ�
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(std::string strKey, const DWORD resID, 
	int width, int height, bool trans, COLORREF transColor)
{	
	//������ �̹��� �ִ� ã�´�...
	image* img = findImage(strKey);

	//Ű���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹��� ����~
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ�����...
	if (FAILED(img->init(resID, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� �� ����Ʈ�� �߰��Ѵ�
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(std::string strKey, const char* fileName,
	float x, float y, int width, int height, bool trans,
	COLORREF transColor)
{
	//������ �̹��� �ִ� ã�´�...
	image* img = findImage(strKey);

	//Ű���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹��� ����~
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ�����...
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� �� ����Ʈ�� �߰��Ѵ�
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(std::string strKey, const char* fileName,
	int width, int height, bool trans,
	COLORREF transColor)
{
	//������ �̹��� �ִ� ã�´�...
	image* img = findImage(strKey);

	//Ű���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹��� ����~
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ�����...
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� �� ����Ʈ�� �߰��Ѵ�
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

//Ű�� �����ؼ� ������ �̹��� �ʱ�ȭ
image* imageManager::addFrameImage(std::string strKey, const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//������ �̹��� �ִ� ã�´�...
	image* img = findImage(strKey);

	//Ű���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹��� ����~
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ�����...
	if (FAILED(img->init(fileName, x, y, width, height, frameX,
		frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� �� ����Ʈ�� �߰��Ѵ�
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}



image* imageManager::addFrameImage(std::string strKey, const char* fileName,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//������ �̹��� �ִ� ã�´�...
	image* img = findImage(strKey);

	//Ű���� ���� �̹����� ������ �߰� ���� �ʰ� ������ �̹��� ����~
	if (img) return img;

	//�̹��� ����
	img = new image;

	//�̹����� ����� �ʱ�ȭ ���� �ʾ�����...
	if (FAILED(img->init(fileName, width, height, frameX,
		frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹��� �� ����Ʈ�� �߰��Ѵ�
	_mImageList.insert(std::make_pair(strKey, img));

	return img;
}

//�̹��� ã�� �Լ�
image* imageManager::findImage(std::string strKey)
{
	//�ش�Ű�� �ִ��� �˻��Ѵ�
	mapImageIter key = _mImageList.find(strKey);

	//Ű�� ã����...
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return NULL;
}

//�̹��� �����
BOOL imageManager::deleteImage(std::string strKey)
{
	//�ش�Ű �˻��Ѵ�
	mapImageIter key = _mImageList.find(strKey);

	//Ű ã����...
	if (key != _mImageList.end())
	{
		//�̹��� ����...
		key->second->release();

		//�޸� ����...
		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return true;
	}
	return false;
}

//��ü �̹��� �����
BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();
	return TRUE;
}

//���� �Լ�
void imageManager::render(std::string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(std::string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(std::string strKey, HDC hdc, int sourX, int sourY,
	int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::render(std::string strKey, HDC hdc, int destX, int destY,
	int sourX, int sourY,int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//���� ����
void imageManager::alphaRender(std::string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(std::string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(std::string strKey, HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::alphaRender(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

//���� ����
void imageManager::loopRender(std::string strKey, HDC hdc, const LPRECT drawArea, 
							  int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if(img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}
