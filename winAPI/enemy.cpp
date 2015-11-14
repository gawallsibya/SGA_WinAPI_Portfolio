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
				// ���� �浹����� ������ ���� ���� �������� �ʴٸ�..
				if (!_target->isDamagedFromObjectAdress(attackRts))
				{
					b = true;
					// ���� ĳ���� ����ϱ�.
					_target->setTargetMemoryAddressLink(this);
					// ������ �Ǳ��.
					_target->setDamaged(damage);
					// ���� �浹��� ����ϱ�.
					_target->addDamagedFromObjectAdress(attackRts);
					break;	// �¾����� ���� �浹�ڽ��� ���� �ʿ� ������ ���÷�Ʈ �������� �ƿ�.
				}
			}
		}
	}
	return b;
}
