#include "stdafx.h"
#include "remilia.h"
#include "missileManager.h"

#include "myProgressBar.h"

remilia::remilia()
{

}

remilia::~remilia()
{
	release();
}

void remilia::init()
{
	animationInit();

	memset(_bArrStateInfo, false, (sizeof(bool) * SI_MAX));
	_way = WAY_RIGHT;
	
	_attackStyle = AS_NULL;

	_maxHp = 1000.f;
	_hp = _maxHp;

	_maxSp = 250.f;
	_sp = 0.f;

	this->setSpeed(300.f); 
	_sp = 0.f;

	_combo_a1 = CA1_NULL;
	_comboTimer = 0.f;

	_dashTimer = 0.f;

	_pState = nullptr;

	//===========

	_pState = new remiliaState_idle;
	_pState->enter(this);

	_pMissileMgr = new missileManager;
	_pMissileMgr->init();

	this->setPivot(0.5f, 1.f);

	_effectMgr = new effectManager;
	_effectMgr->init();

}

void remilia::update()
{
	stateUpdate();
	commandUpdate();

	this->calcGravity();

	_pMissileMgr->update();
	_effectMgr->update();

	if (_dashTimer > 0.f)
	{
		_dashTimer -= TIMEMANAGER->getElapsedTime();
	}
	boundingRectUpdate();
}

void remilia::render(HDC hdc)
{
	POINT cameraPos = { (int)(this->getPos().x - this->getImage()->getFrameWidth() * 0.5f), (int)(this->getPos().y - this->getImage()->getFrameHeight()) };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	_way == WAY_RIGHT ? 
		this->getImage()->aniRender(hdc, cameraPos.x, cameraPos.y, this->getAnimation()) :
		this->getImage()->aniRender(hdc, cameraPos.x, cameraPos.y, this->getAnimation(), true);

	_pMissileMgr->render(hdc);
	_effectMgr->render();

	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	MYRECT cameraRect;
	for (MYRECT& temp : *this->getDamagedRects())
	{
		cameraRect = CAMERAMANAGER->ConvertWorldToScreenPos(&temp);
		Rectangle(hdc, (int)cameraRect.getMinX(), (int)cameraRect.getMinY(), (int)cameraRect.getMaxX(), (int)cameraRect.getMaxY());
	}
	for (MYRECT& temp : *this->getAttackRects())
	{
		cameraRect = CAMERAMANAGER->ConvertWorldToScreenPos(&temp);
		Rectangle(hdc, (int)cameraRect.getMinX(), (int)cameraRect.getMinY(), (int)cameraRect.getMaxX(), (int)cameraRect.getMaxY());
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	cameraPos = { (int)this->getPos().x, (int)this->getPos().y };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	Ellipse(hdc, cameraPos.x - 5, cameraPos.y, cameraPos.x + 5, cameraPos.y + 10);*/
}

void remilia::release()
{
	_bArrStateInfo[SI_MAX] = {};
	_way = {};
	// �޺�����
	_combo_a1 = {};
	_comboTimer = 0.f;

	// ��������
	_velocityY = 0.f;
	_hp = 0.f;
	_sp = 0.f;

	SAFE_DELETE(_pState);	// ���� ����

	_effectMgr->release();
	SAFE_DELETE(_effectMgr);
	SAFE_DELETE(_spBar);
}

void remilia::stateUpdate()
{  
	_pState->execute(this);
}

void remilia::commandUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		// ���
		if (_dashTimer > 0.f && _prevKey == VK_RIGHT)
		{
			_way = _prevWay;
			if (_prevWay == WAY_RIGHT)
			{
				if (_bArrStateInfo[SI_JUMP])
				{
					changeState(new remiliaState_dash_forward_air_ready);
					return;
				}
				if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
				{
					changeState(new remiliaState_dash_forward_ready);
					return;
				}
			}
			else
			{
				if (_bArrStateInfo[SI_JUMP])
				{
					changeState(new remiliaState_dash_back_air_ready);
					return;
				}
				if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
				{
					changeState(new remiliaState_dash_back_ready);
					return;
				}
			}
		}
		else
		{
			_dashTimer = 0.2f;
			_prevWay = _way;
			_prevKey = NULL;
		}
		_prevKey = VK_RIGHT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		// ���
		if (_dashTimer > 0.f && _prevKey == VK_LEFT)
		{
			_way = _prevWay;
			if (_prevWay == WAY_LEFT)
			{
				if (_bArrStateInfo[SI_JUMP])
				{
					changeState(new remiliaState_dash_forward_air_ready);
					return;
				}
				if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
				{
					changeState(new remiliaState_dash_forward_ready);
					return;
				}
			}
			else
			{
				if (_bArrStateInfo[SI_JUMP])
				{
					changeState(new remiliaState_dash_back_air_ready);
					return;
				}
				if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
				{
					changeState(new remiliaState_dash_back_ready);
					return;
				}
			}
		}
		else
		{
			_dashTimer = 0.2f;
			_prevWay = _way;
			_prevKey = NULL;
		}
		_prevKey = VK_LEFT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_Z))
	{
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			changeState(new remiliaState_attack_a1_start);
			_combo_a1 = CA1_1;
			return;
		}
		else if (_bArrStateInfo[SI_COMBO])
		{
			switch (_combo_a1)
			{
			case remilia::CA1_1:
				changeState(new remiliaState_attack_a1_start);
				_combo_a1 = CA1_2;
			break;
			case remilia::CA1_2:
				changeState(new remiliaState_attack_a3_start1);
				_combo_a1 = CA1_3;
			break;
			case remilia::CA1_3:
				changeState(new remiliaState_attack_c1_start);
				_combo_a1 = CA1_NULL;
				break;
			default:
				break;
			}
			return;
		}
	}

	// �� ��
	if ( KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// �ȱ�
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			_way = WAY_RIGHT;
			if (_bArrStateInfo[SI_IDLE])
			{
				changeState(new remiliaState_walk_forward);
				return;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{	
		//�ȱ�
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			_way = WAY_LEFT;
			
			if (_bArrStateInfo[SI_IDLE])
			{
				changeState(new remiliaState_walk_forward);
				return;
			}
		}
	}

	else if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_bArrStateInfo[SI_MOVE])
		{
			_bArrStateInfo[SI_MOVE] = false;
			changeState(new remiliaState_idle);
			return;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			changeState(new remiliaState_jump_ready);
			return;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			this->changeState(new remiliaState_sit_start);
			return;
		}
	}
	
	
	if (KEYMANAGER->isOnceKeyDown(VK_X))
	{
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			changeState(new remiliaState_shot_b_start);
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_1))
	{
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			if (_sp >= 100.f) changeState(new remiliaState_gungnir_create);
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_2))
	{
		if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
		{
			if (_sp >= 200.f) changeState(new remiliaState_huyajyou_ready);
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_hp = _maxHp;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_sp = _maxSp;
	}


}

void remilia::changeState(remiliaState* pNewState)
{
	// ����üũ
	if (_pState == nullptr || pNewState == nullptr)
	{
		// ������ ���� ǥ���Ҳ�..
		return;
	}
	// ���� ���� ��Ż
	_pState->exit(this);
	// ���� ���� ����
	delete _pState;
	
	// ���ο� ���¸� ���� ���·� ����
	_pState = pNewState;
	// ���ο� ���·� ����
	_pState->enter(this);
}

void remilia::boundingRectUpdate()
{
	this->moveFromDamagedRect(this->getPos().x, this->getPos().y);
}

void remilia::fireShotB()
{
	_way == WAY_RIGHT ?
		_pMissileMgr->createMissile(this, new shot_b, this->getPos().x, this->getPos().y - 50, vRight, false, this->getStageMemoryAddressLink()) :
		_pMissileMgr->createMissile(this, new shot_b, this->getPos().x, this->getPos().y - 50, vLeft, true, this->getStageMemoryAddressLink());
}

void remilia::fireGungnir()
{
	_way == WAY_RIGHT ?
		_pMissileMgr->createMissile(this, new gungnir, this->getPos().x, this->getPos().y - 70, vRight, false, this->getStageMemoryAddressLink()) :
		_pMissileMgr->createMissile(this, new gungnir, this->getPos().x, this->getPos().y - 70, vLeft, true, this->getStageMemoryAddressLink());
}

void remilia::setDie()
{
	this->changeState(new remiliaState_die);
}

void remilia::setDamaged(float damage)
{
	this->subHP(damage);
	if (this->getHP() <= 0.f)
	{
		this->setDie();
		return;
	}
	if (damage >= 100.f)
	{
		if (this->getPos().x - _target->getPos().x <= 0.f)
		{
			_way = WAY_RIGHT;
			this->changeState(new remiliaState_hit_down_back);
			return;
		}
		else
		{
			_way = WAY_LEFT;
			this->changeState(new remiliaState_hit_down_back);
			return;
		}
	}
	else
	{
		if (this->getPos().x - _target->getPos().x <= 0.f)
		{
			_way = WAY_RIGHT;
			this->changeState(new remiliaState_hit_forward);
			return;
		}
		else
		{
			_way = WAY_LEFT;
			this->changeState(new remiliaState_hit_forward);
			return;
		}
	}
}

bool remilia::attackToEnemys(vector<MYRECT>* attackRts, float damage)
{
	// ������ true, �ȸ����� false
	bool b = false;
	for (ENEMYMANAGER->getLIEnemyList() = ENEMYMANAGER->getLEnemyList().begin();
		ENEMYMANAGER->getLIEnemyList() != ENEMYMANAGER->getLEnemyList().end(); ++ENEMYMANAGER->getLIEnemyList())
	{
		for (MYRECT& tempAR : *attackRts)
		{
			for (MYRECT& tempDR : *(*ENEMYMANAGER->getLIEnemyList())->getDamagedRects())
			{
				MYRECT rcInter;
				if (isCollisionRect(&rcInter, tempAR, tempDR))
				{
					// ���� �浹����� ������ ���� ���� �������� �ʴٸ�..
					if (!(*ENEMYMANAGER->getLIEnemyList())->isDamagedFromObjectAdress(attackRts))
					{
						/*// Ÿ�� ����Ʈ ȿ��
						_way == WAY_RIGHT ?
							EFFECTMANAGER->play("remilia_hit_effect2", "remilia_hit_effect2",
							tempAR.getPos().x - RND->getFloat(rcInter.getSize().width), tempAR.getPos().y - RND->getFloat(rcInter.getSize().height),
							(KEYANIMANAGER->findAnimation("remilia_hit_effect2")->getMaxFrame() + 1) / 0.2f, false, 128, true, true) :
							EFFECTMANAGER->play("remilia_hit_effect2", "remilia_hit_effect2",
							tempAR.getPos().x + RND->getFloat(rcInter.getSize().width), tempAR.getPos().y + RND->getFloat(rcInter.getSize().height),
							(KEYANIMANAGER->findAnimation("remilia_hit_effect2")->getMaxFrame() + 1) / 0.2f, false, 128, true, true);*/
						b = true;

						switch (_attackStyle)
						{
						
						case remilia::AS_A1:
							break;
						case remilia::AS_A3:
							this->addSP(5.f);
							break;
						case remilia::AS_C1:
							this->addSP(15.f);
							break;
						case remilia::AS_HUYAJYOU:
							this->addHP(10.f);
							break;
						default:
							break;
						}

						// ���� ĳ���� ����ϱ�.
						(*ENEMYMANAGER->getLIEnemyList())->setTargetMemoryAddressLink(this);
						// ������ �Ǳ��.
						(*ENEMYMANAGER->getLIEnemyList())->setDamaged(damage);
						// ���� �浹��� ����ϱ�.
						(*ENEMYMANAGER->getLIEnemyList())->addDamagedFromObjectAdress(attackRts);

						(*ENEMYMANAGER->getLIEnemyList())->AttackModeStart();
						break;	// �¾����� ���� �浹�ڽ��� ���� �ʿ� ������ ���÷�Ʈ �������� �ƿ�.
					}
				}
			}
		}
	}
	return b;
}