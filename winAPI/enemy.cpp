#include "stdafx.h"
#include "enemy.h"

enemy::enemy() : 
_recognitionRange(0.f),
_bAttackMode(false),
_hpBar(new myProgressBar)
{
}

enemy::~enemy()
{
	_recognitionRange = 0.f;
	_bAttackMode = false;
	SAFE_DELETE(_hpBar);
}

bool enemy::attackToTarget(vector<MYRECT>* attackRts, float damage)
{
	bool b = false;
	for (MYRECT& tempAR : *attackRts)
	{
		for (MYRECT& tempDR : *_target->getDamagedRects())
		{
			MYRECT rcInter;
			if (isCollisionRect(&rcInter, tempAR, tempDR))
			{
				// 때린 충돌대상이 이전에 때린 대상과 동일하지 않다면..
				if (!_target->isDamagedFromObjectAdress(attackRts))
				{
					b = true;
					// 때린 캐릭터 기억하기.
					_target->setTargetMemoryAddressLink(this);
					// 맞으면 피깎기.
					_target->setDamaged(damage);
					// 때린 충돌대상 기억하기.
					_target->addDamagedFromObjectAdress(attackRts);
					break;	// 맞았으면 다음 충돌박스와 비교할 필요 없으니 어택렉트 루프에서 아웃.
				}
			}
		}
	}
	return b;
}
