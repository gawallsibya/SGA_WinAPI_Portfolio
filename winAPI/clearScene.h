#pragma once
#include "gameNode.h"

class clearScene : public gameNode
{
public:
	clearScene();
	~clearScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

private:
	image* _bg;
	image* _blindImg;
	float _blindAlpha;

};

