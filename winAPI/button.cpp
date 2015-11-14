#include "StdAfx.h"
#include "button.h"

button::button(void)
{
}

button::~button(void)
{
}

HRESULT button::init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction)
{
	gameNode::init();

	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = static_cast<float>(x);
	_y = static_cast<float>(y);

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(),
		_image->getFrameHeight());

	return S_OK;
}

void button::release(void)
{
	gameNode::release();
}

void button::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if(KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;

	gameNode::update();
}

void button::render(void)
{
	switch (_direction)
	{
		case BUTTONDIRECTION_UP: case BUTTONDIRECTION_NULL:
			_image->frameRender(getMemDC(), _rc.left,
				_rc.top, _btnUpFramePoint.x,
				_btnUpFramePoint.y);
		break;
		case BUTTONDIRECTION_DOWN:
			_image->frameRender(getMemDC(), _rc.left,
				_rc.top, _btnDownFramePoint.x,
				_btnDownFramePoint.y);
		break;
	}
}
