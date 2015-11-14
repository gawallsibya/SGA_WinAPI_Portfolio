#pragma once
#include "missile.h"

class gungnir : public missile
{
public:
	gungnir();
	~gungnir();

	virtual void init(character* master, float x, float y, VECTOR2D vMovePos, bool reverse);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();

	inline effectManager* getEffectManager() { return _effectMgr; }

private:
	
};

