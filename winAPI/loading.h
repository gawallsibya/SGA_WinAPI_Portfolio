#pragma once

#include "gameNode.h"
#include "progressBar.h"
#include <string>
#include <vector>

//로딩아이템 종류
enum LOADING_KIND
{
	LOADING_KIND_IMAGE_00,
	LOADING_KIND_IMAGE_01,
	LOADING_KIND_IMAGE_02,
	LOADING_KIND_FRAMEIMAGE_00,
	LOADING_KIND_FRAMEIMAGE_01,
	LOADING_KIND_SOUND_00,
	LOADING_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;
	const char* fileName;
	int x, y;
	int width, height;
	int frameX, frameY;
	bool trans;
	COLORREF transColor;
};

class loadItem
{
private:
	LOADING_KIND _kind;

	tagImageResource _imageResource;

public:
	//이미지 로드 아이템
	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	HRESULT initForFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	void release(void);

	LOADING_KIND getLoadingKind(void) { return _kind; }
	tagImageResource getImageResource(void) { return _imageResource; }

	loadItem(void);
	~loadItem(void);
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	image* _background;
	progressBar* _loadingBar;

	int _current;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadImage(string keyName, int width, int height);
	void loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	void loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	void loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	BOOL loadNext(void);

	vector<loadItem*> getLoadItem(void) { return _vLoadItem; }

	loading(void);
	~loading(void);
};
