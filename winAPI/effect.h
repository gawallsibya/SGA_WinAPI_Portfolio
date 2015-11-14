#pragma once

#include "gameNode.h"

class image;
class animation;

class effect : public gameNode
{
protected:
	float _x;	//effect ��ǥ x;
	float _y;	//effect ��ǥ y;

	image* _effectImage;			//�̹���
	animation* _effectAnimation;	//�ִϸ��̼�
	bool _isRunning;				//�����ֳ�	
	//float _elapsedTime;				//����ð�
	
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

