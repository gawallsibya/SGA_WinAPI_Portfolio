#pragma once

class object : public myRect
{
public:
	object();
	~object();

	virtual void release(void);
	virtual void update(void) = 0;
	virtual void render(HDC hdc) = 0;

	//inline MYRECT* getBoundingBox()  { return dynamic_cast<MYRECT*>(this); }

	void moveTo(float x, float y);
	void moveTo(VECTOR2D vecPos);

	void moveFrom(float x, float y);
	void moveFrom(VECTOR2D vecPos);


protected:
	animation* _ani;
	image* _img;

};
