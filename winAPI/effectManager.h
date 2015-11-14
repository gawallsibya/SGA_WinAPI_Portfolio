#pragma once

#include "singletonBase.h"
#include <list>
#include <map>

class effect;

using namespace std;

class effectManager : public singletonBase <effectManager>
{
private:
	typedef list<effect*> arrEffects;
	typedef list<effect*>::iterator iterEffects;

private:
	//arrTotalEffect _vTotalEffects; //¸ðµç ÀÌÆåÆ®
	arrEffects _lEffects;

public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	void play(string imageName, string aniName, float x, float y, float fps, bool reverse, BYTE alpha = 255, bool bAlphaFormat = false, bool bCamera = false);
	effectManager(void);
	~effectManager(void);
};


