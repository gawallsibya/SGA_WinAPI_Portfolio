#include "stdafx.h"
#include "stage.h"


stage::stage() : 
_bg(nullptr),
_bg_collision(nullptr),
_blindImg(nullptr),
_blindAlpha(255)
{
}


stage::~stage()
{
	_bg = nullptr;
	_bg_collision = nullptr;
	_blindImg = nullptr;
	_blindAlpha = 0;
}
