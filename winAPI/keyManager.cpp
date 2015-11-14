#include "stdafx.h"
#include "keyManager.h"

keyManager::keyManager(void)
{
}

keyManager::~keyManager(void)
{
}

HRESULT keyManager::init(void)
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyDown().set(i, false);
		this->getKeyUp().set(i, false);
	}

	return S_OK;
}

void keyManager::release(void)
{
}

//Ű�� �ѹ� ���ȴ��� �˻�
bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

//Ű�� �� �ѹ��� ���Ǿ����� �˻�
bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}

//Ű�� ��� ���ȴ��� �˻�
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

//���Ű��? (�̰� ���� ���� ����)
bool keyManager::isToggleKey(int key)
{
	if (GetAsyncKeyState(key) & 0x0001) return true;
	return false;
}

