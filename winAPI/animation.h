#pragma once

#include <vector>

//======================================
//  - ## animation ## - Tuesday Of Blood -
//======================================

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

class animation
{
public:
	typedef std::vector<POINT>	_vFrameList;	//������������ ���� ������ �����ؾ� �Ѵ�.
	typedef	std::vector<int> _vPlayList;		//�������÷��� ����Ʈ


private:
	int _frameNum;					//������ ��

	_vFrameList _frameList;			//������ ��ġ ����Ʈ
	_vPlayList _playList;			//�÷��� ����Ʈ

	int _frameWidth;				//������ ���� ũ��
	int	_frameHeight;				//������ ���� ����

	BOOL _loop;						//���� ����
	float _frameUpdateSec;			//������ ������Ʈ ��
	float _elapsedSec;				//������ ���� ��

	DWORD _nowPlayIdx;				//���� �÷��� �ε��� ( PLAY_LIST ���� �����Ѵ� )
	BOOL _play;						//���� �÷��� ����

	void* _obj;

	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;
	CALLBACK_FUNCTION _callbackFunction;

public:
	animation(void);
	~animation(void);

	HRESULT init(int totalW, int totalH, int frameW, int frameH);						//�̹��� �� ���μ���ũ��� �� �������� ���μ��� ũ��� ����
	void release(void);

	//ó������ ������
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);						//�⺻ ����
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�迭�� ��Ƽ� ������ ������
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);					//�÷��� ������ �迭�� ����
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//������ ���ؼ� ������ ������
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);		//�÷��� ������ ���۰� ����� ����
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void setFPS(float framePerSec);				//�ʴ� ���� Ƚ��

	void frameUpdate(float elpasedTime);		//������ ������Ʈ Ÿ��

	void start(void);			//�÷��� ����
	void stop(void);			//�÷��� ���� ����
	void pause(void);			//�÷��� �Ͻ� ����
	void resume(void);			//�÷��� �ٽ� ����

	//�÷��� ���� Ȯ��
	inline BOOL isPlay(void) { return _play; }

	//������ ��ġ�� ��´�.
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	//������ ���� ũ�⸦ ��´�.
	inline int getFrameWidth(void) { return _frameWidth; }

	//������ ���� ũ�⸦ ��´�.
	inline int getFrameHeight(void)	{ return _frameHeight; }

	inline int getPlayFrame() { return _nowPlayIdx; }
	inline int getMaxFrame() { return _playList.size()-1; }
};
