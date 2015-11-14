#include "stdafx.h"
#include "object.h"

object::object() :_ani(nullptr), _img(nullptr)
{
}


object::~object()
{
	release();
}


void object::release(void)
{
	_ani = nullptr;
	_img = nullptr;
	
}

