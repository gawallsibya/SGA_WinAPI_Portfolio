#pragma once

class timer
{
private:
	bool			_isHardware;		//���� Ÿ�̸Ӹ� �����ϳ�?
	float			_timeScale;			//�ð� �����
	float			_timeElapsed;		//������ �ð��� ���� �ð��� �����
	__int64			_curTime;			//����ð�
	__int64			_lastTime;			//�������ð�
	__int64			_periodFrequency;	//�ð��ֱ�

	unsigned long	_frameRate;			//FPS
	unsigned long	_FPSFrameCount;		//FPSī��Ʈ
	float			_FPSTimeElapsed;	//FPS ������ �ð��� ���� �ð��� �����
	float			_worldTime;			//����Ÿ��

public:
	//�ʱ�ȭ
	HRESULT init(void);
	//���� �ð� ���
	void tick(float lockFPS = 0.0f);
	//���� FPS�� ���´�
	unsigned long getFrameRate(char* str = NULL) const;

	//������ �ð��� ����ð��� �����
	inline float getElapsedTime(void) const {
		return _timeElapsed;}
	//��ü ��� �ð�
	inline float getWorldTime(void) const {return _worldTime;}



	timer(void);
	~timer(void);
};

