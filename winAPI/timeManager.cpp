#include "stdafx.h"
#include "timeManager.h"

timeManager::timeManager(void) : _timer(nullptr)
{
}

timeManager::~timeManager(void)
{
}

//�ʱ�ȭ
HRESULT timeManager::init(void)
{
	//Ÿ�̸� ����
	_timer = new timer;
	
	//Ÿ�̸� �ʱ�ȭ
	_timer->init();

	return S_OK;
}

//Ÿ�̸� ����
void timeManager::release(void)
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
	}
}

//Ÿ�̸� ������ ����
void timeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

//�ش� HDC�� ���� ���
void timeManager::render(HDC hdc)
{
	char str[256] = {};
	std::string strFrame = "";

	//���� ����� (TRANSPARENT: ����, QPAQUEL: ������)
	SetBkMode(hdc, TRANSPARENT);
	//���� ����
	SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	if(_timer != NULL)
	{
		//������ ��´�
		sprintf_s(str, "framePerSec : %d", _timer->getFrameRate());
		TextOutA(hdc, 0, 0, str, strlen(str));

		//���� Ÿ�� ��´�(����ð�)
		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOutA(hdc, 0, 20, str, strlen(str));

		//���� tick ��´�
		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOutA(hdc, 0, 40, str, strlen(str));
	}
#else
	if(time != NULL)
	{
		//������ ��´�
		sprintf(str, "framePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));		
	}
#endif
}
