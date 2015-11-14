#include "stdafx.h"
#include "cameraManager.h"

////부모클래스 안만들어서 임시로
//#include "player.h"

POINT getWorldToMousePoint()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(_hWnd, &pt);
	pt = CAMERAMANAGER->ConvertScreenToWorldPos(&pt);

	return pt;
}

cameraManager::cameraManager() : 
_targetPos(dynamic_cast<MYRECT*>(this)),
_minX(0.f), 
_minY(0.f),
_maxX(0.f),
_maxY(0.f)
{
}

cameraManager::~cameraManager()
{
	release();
}

HRESULT cameraManager::init(float minX, float minY, float maxX, float maxY)
{
	// 기본설정
	setPivot(0.5f, 0.5f);
	RECT rt = RectMake(0, 0, WINSIZEX, WINSIZEY);
	setSize(static_cast<float>(rt.right), static_cast<float>(rt.bottom));
	setPos(getHalfSize().width, getHalfSize().height);

	_minX = minX;
	_minY = minY;
	_maxX = maxX;
	_maxY = maxY;

	return S_OK;
}


void cameraManager::setTargetAddressLink(MYRECT* const targetPos)
{
	_targetPos = targetPos;
}

const MYRECT* cameraManager::getTargetAddressLink() const
{
	return _targetPos;
}

MYRECT cameraManager::ConvertWorldToScreenPos(const MYRECT* srcVec)
{
	//오브젝트 정보 복사
	MYRECT myRt = *srcVec;

	//좌표값만 수정
	MYRECT rt = *_targetPos;
	if (rt.getPos().x - this->getPos().x < _minX) rt.setPosX(_minX + this->getPos().x);
	if (rt.getPos().x > _maxX - this->getPos().x) rt.setPosX(_maxX - this->getPos().x);
	if (rt.getPos().y - this->getPos().y < _minY) rt.setPosY(_minY + this->getPos().y);
	if (rt.getPos().y > _maxY - this->getPos().y) rt.setPosY(_maxY - this->getPos().y);

	VECTOR2D vec = this->getPos() + (myRt.getPos() - rt.getPos());
	myRt.setPos(vec.x, vec.y);
	
	return myRt;
}

POINT cameraManager::ConvertWorldToScreenPos(const POINT* srcPoint)
{
	//좌표값만 수정
	POINT pt;

	MYRECT rt = *_targetPos;
	if (rt.getPos().x - this->getPos().x < _minX) rt.setPosX(_minX + this->getPos().x);
	if (rt.getPos().x > _maxX - this->getPos().x) rt.setPosX(_maxX - this->getPos().x);
	if (rt.getPos().y - this->getPos().y < _minY) rt.setPosY(_minY + this->getPos().y);
	if (rt.getPos().y > _maxY - this->getPos().y) rt.setPosY(_maxY - this->getPos().y);
	
	pt.x = static_cast<int>(getPos().x + srcPoint->x - rt.getPos().x);
	pt.y = static_cast<int>(getPos().y + srcPoint->y - rt.getPos().y);

	return pt;
}

VECTOR2D cameraManager::ConvertWorldToScreenPos(const VECTOR2D* srcPoint)
{
	//좌표값만 수정
	VECTOR2D pt;

	MYRECT rt = *_targetPos;
	if (rt.getPos().x - this->getPos().x < _minX) rt.setPosX(_minX + this->getPos().x);
	if (rt.getPos().x > _maxX - this->getPos().x) rt.setPosX(_maxX - this->getPos().x);
	if (rt.getPos().y - this->getPos().y < _minY) rt.setPosY(_minY + this->getPos().y);
	if (rt.getPos().y > _maxY - this->getPos().y) rt.setPosY(_maxY - this->getPos().y);

	pt.x = this->getPos().x + srcPoint->x - rt.getPos().x;
	pt.y = this->getPos().y + srcPoint->y - rt.getPos().y;

	return pt;
}

MYRECT cameraManager::ConvertScreenToWorldPos(const MYRECT* srcVec)
{
	//오브젝트 정보 복사
	MYRECT obj = *srcVec;
	//좌표값만 수정
	VECTOR2D vec = obj.getPos() + _targetPos->getPos() - this->getPos();
	obj.setPos(vec.x, vec.y);

	return obj;
}

POINT cameraManager::ConvertScreenToWorldPos(const POINT* srcPoint)
{

	//좌표값만 수정
	POINT pt;
	pt.x = static_cast<int>(srcPoint->x + _targetPos->getPos().x - this->getPos().x);
	pt.y = static_cast<int>(srcPoint->y + _targetPos->getPos().y - this->getPos().y);

	return pt;
}

VECTOR2D cameraManager::ConvertScreenToWorldPos(const VECTOR2D* srcPoint)
{

	//좌표값만 수정
	VECTOR2D pt;
	pt.x = srcPoint->x + _targetPos->getPos().x - this->getPos().x;
	pt.y = srcPoint->y + _targetPos->getPos().y - this->getPos().y;

	return pt;
}

void cameraManager::release(void)
{
	_targetPos = nullptr;
	_minX = 0.f;
	_minY = 0.f;
	_maxX = 0.f;
	_maxY = 0.f;
}
