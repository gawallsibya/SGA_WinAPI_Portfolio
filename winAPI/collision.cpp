#include "stdafx.h"
#include "collision.h"

namespace MY_UTIL
{
	bool isCollisionRect(MYRECT* rcInter, const MYRECT& rc1, const MYRECT& rc2)
	{
		if ((rc1.getMinX() <= rc2.getMaxX() && rc1.getMaxX() >= rc2.getMinX()) &&
			(rc1.getMinY() <= rc2.getMaxY() && rc1.getMaxY() >= rc2.getMinY()))
		{
			float width = 0.f;
			float height = 0.f;
			// 가로충돌
			if (rc1.getMinX() <= rc2.getMaxX() && rc1.getMaxX() >= rc2.getMinX())
			{
				width = rc1.getMinX() - rc2.getMaxX();
			}
			// 세로충돌
			if (rc1.getMinY() <= rc2.getMaxY() && rc1.getMaxY() >= rc2.getMinY())
			{
				height = rc1.getMinY() - rc2.getMaxY();
			}
			rcInter->setSize(width, height);
			return true;
		}
		else
		{
			return false;
		}

		//return false;*/
	}
}