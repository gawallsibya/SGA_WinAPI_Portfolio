#pragma once

#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	float _x;	//effect 좌표 x;
	float _y;	//effect 좌표 y;

	image* _effectImage;			//이미지
	animation* _effectAnimation;	//애니메이션
	bool _isRunning;				//돌고있냐	
	//float _elapsedTime;				//경과시간
	
	bool _bLife;
	bool _bAlphaFormat;
	bool _bReverse;
	bool _bCamera;
	BYTE _alpha;

public:
	HRESULT init(image* effectImage, animation* effectAnimation, bool reverse, BYTE alpha = 255, bool bAlphaFormat = false, bool bCamera = false);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void startEffect(float x, float y);
	void killEffect(void);

	BOOL getIsRunning(void) {return _isRunning;}
	inline BOOL getIsLife(void){ return _bLife; }

	inline void setFPS(float fps) { _effectAnimation->setFPS(fps); }

	effect(void);
	~effect(void);

};

