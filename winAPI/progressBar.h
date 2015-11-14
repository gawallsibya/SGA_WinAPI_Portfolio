#pragma once

class progressBar 
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop; //hp�� ž �̹���
	image* _progressBarBottom; //hp�� ��(�޹��) �̹���

public:
	void init(int x, int y, int width, int height);
	//�����߰���
	void init(string topImageKeyName, string bottomImageKeyName,
		int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(HDC hdc);

	//ü�¹� ������
	void setGauge(float currentGuage, float maxGuage);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect(void) { return _rcProgress; }

	progressBar(void);
	~progressBar(void);
};

