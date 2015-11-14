#pragma once
#include "singletonBase.h"
#include "myRect.h"

POINT getWorldToMousePoint();

class cameraManager : public singletonBase<cameraManager>, public myRect
{
public:
	cameraManager();
	~cameraManager();

	HRESULT init(float minX, float minY, float maxX, float maxY);
	void update();
	void release(void);

	void setTargetAddressLink(MYRECT* const targetPos);
	const MYRECT* getTargetAddressLink() const;
	MYRECT ConvertWorldToScreenPos(const MYRECT* srcVec);
	POINT ConvertWorldToScreenPos(const POINT* srcPoint);
	VECTOR2D ConvertWorldToScreenPos(const VECTOR2D* srcPoint);
	MYRECT ConvertScreenToWorldPos(const MYRECT* srcVec);
	POINT ConvertScreenToWorldPos(const POINT* srcPoint);
	VECTOR2D ConvertScreenToWorldPos(const VECTOR2D* srcPoint);

private:
	MYRECT* _targetPos;

	float _minX, _minY, _maxX, _maxY;
};

