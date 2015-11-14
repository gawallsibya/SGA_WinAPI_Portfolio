#pragma once

class progressBar 
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop; //hp바 탑 이미지
	image* _progressBarBottom; //hp바 백(뒷배경) 이미지

public:
	void init(int x, int y, int width, int height);
	//새로추가함
	void init(string topImageKeyName, string bottomImageKeyName,
		int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(HDC hdc);

	//체력바 게이지
	void setGauge(float currentGuage, float maxGuage);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect(void) { return _rcProgress; }

	progressBar(void);
	~progressBar(void);
};

