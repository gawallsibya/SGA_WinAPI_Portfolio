#pragma once
#include "gameNode.h"
#include "animation.h"

class animationTest : public gameNode
{
private:
	animation* _ani1;
	animation* _ani2;
	animation* _ani3;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	animationTest(void);
	~animationTest(void);
};

