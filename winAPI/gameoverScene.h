#pragma once
#include "gameNode.h"

class gameoverScene : public gameNode
{
public:
	gameoverScene();
	~gameoverScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

private:
	image* _bg;
	image* _blindImg;
	float _blindAlpha;

};

