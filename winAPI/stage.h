#pragma once

class enemyManager;
class stage : public myRect
{
public:
	stage();
	virtual ~stage();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(HDC hdc) = 0;

	inline image* getCollisionBackground() { return _bg_collision; }

protected:
	image* _bg;
	image* _bg_collision;

	image* _blindImg;
	float _blindAlpha;
};

