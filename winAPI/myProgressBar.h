#pragma once

class myProgressBar : public myRect
{
public:
	myProgressBar();
	~myProgressBar();

	void init(string progressTopImageName, string progressBottomImageName, float x, float y, float width, float height,
		float maxHp, float* hpAdress, BYTE alpha = 255, BYTE alpha2 = 255, bool bCamera = false);
	void update();
	void render(HDC hdc);

private:
	image* _topImg;
	image* _bottomImg;

	BYTE _alpha1;
	BYTE _alpha2;

	float _maxHp;
	float* _targetHp;
	float _targetHpWidth;

	bool _bCamera;
};

