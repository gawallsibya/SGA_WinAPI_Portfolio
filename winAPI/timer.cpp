#include "stdafx.h"
#include "timer.h"
#include <MMSystem.h>
//TimeGetTime �Լ��� ����ϱ� ���� ���̺귯��
//�����찡 �������� �ð��� �˷��ִ� API
#pragma comment (lib, "winmm.lib")

timer::timer(void)
{
}

timer::~timer(void)
{
}

//�ʱ�ȭ
HRESULT timer::init(void)
{
	//���� Ÿ�̸� �������� üũ�Ѵ�
	//���� ������ �Ǹ� �ʴ� �и��������� ���� ��(1000)
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//�ʴ� �ð� ��� ����
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		//�и� ������ ������ �ð����� �ʴ� 1000ī��Ʈ �Ѵ�
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;			//FPS
	_FPSFrameCount = 0;		//FPSī��Ʈ
	_FPSTimeElapsed = 0.0f;	//FPS ������ �ð��� ���� �ð��� �����
	_worldTime = 0.0f;		//����Ÿ��
	_timeElapsed = 0.0f;	//������ �ð��� ����ð��� �����
	return S_OK;
}

//���� �ð� ���
void timer::tick(float lockFPS)
{
	//���� Ÿ�̸Ӹ� �����ϸ�..
	if(_isHardware)
	{
		//������ ����ũ���� ������ ����Ѵ�
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//�������� ������ time�Լ� �̿� (�и�~)
		_curTime = timeGetTime();
	}

	//������ �ð��� ����ð��� �����
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if(lockFPS > 0.0f)
	{
		//���� �������� �ð��� �����Ҷ����� ����~~
		while(_timeElapsed < (1.0f / lockFPS))
		{
			if(_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			//������ �ð��� ����ð��� �����
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime; //������ �ð� ����Ѵ�
	_FPSFrameCount++; //�ʴ� ������ ī��Ʈ++
	_FPSTimeElapsed += _timeElapsed; //�ʴ� ������ �ð� ������� ������Ų��
	_worldTime += _timeElapsed; //��ü�ð� ����� ������Ų��

	//������ �ʱ�ȭ�� 1�ʸ��� �����Ѵ�
	if(_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

//���� FPS�� ���´�
unsigned long timer::getFrameRate(char* str) const
{
	if(str != NULL)
	{
		int len = to_string(_frameRate).length() + 7;
		sprintf_s(str, len, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
