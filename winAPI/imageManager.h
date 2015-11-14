#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map>
#include <string>

//=========================================================
// 2014.11.24 ## imageManager ##       - Wednesday Of Blood
//=========================================================

class imageManager : public singletonBase <imageManager>
{
public:
	typedef std::map<std::string, image*> mapImageList;				//�̹��� ����Ʈ ��
	typedef std::map<std::string, image*>::iterator mapImageIter;	//�̹��� ����Ʈ ���ͷ�����

private:
	mapImageList _mImageList; //������ ������ �̹��� ����Ʈ~~~

public:
	//�¾�
	HRESULT init(void);

	//����
	void release(void);

	//Ű�� �����ؼ� �ʱ�ȭ
	image* addImage(std::string strKey, int width, int height);
	image* addImage(std::string strKey, const DWORD resID, 
		int width, int height, bool trans = false, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(std::string strKey, const char* fileName,
		float x, float y, int width, int height, bool trans = false, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(std::string strKey, const char* fileName,
		int width, int height, bool trans = false, COLORREF transColor = RGB(255, 0, 255));

	//Ű�� �����ؼ� ������ �̹��� �ʱ�ȭ
	image* addFrameImage(std::string strKey, const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);

	image* addFrameImage(std::string strKey, const char* fileName,
		int width, int height, int frameX, int frameY,
		BOOL trans, COLORREF transColor);

	//�̹��� ã�� �Լ�
	image* findImage(std::string strKey);

	//�̹��� �����
	BOOL deleteImage(std::string strKey);

	//��ü �̹��� �����
	BOOL deleteAll(void);

	//���� �Լ�
	void render(std::string strKey, HDC hdc);
	void render(std::string strKey, HDC hdc, int destX, int destY);
	void render(std::string strKey, HDC hdc, int sourX, int sourY,
		int sourWidth, int sourHeight);
	void render(std::string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY,int sourWidth, int sourHeight);

	//������ ����
	void frameRender(std::string strKey, HDC hdc, int destX, int destY);
	void frameRender(std::string strKey, HDC hdc, int destX, int destY, int frameX, int frameY);

	//���� ����
	void alphaRender(std::string strKey, HDC hdc, BYTE alpha);
	void alphaRender(std::string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(std::string strKey, HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaRender(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//���� ����
	void loopRender(std::string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	imageManager(void);
	~imageManager(void);
};


