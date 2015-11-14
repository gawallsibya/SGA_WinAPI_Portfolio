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
	typedef std::vector<POINT>	_vFrameList;	//프레임접근은 임의 접근이 가능해야 한다.
	typedef	std::vector<int> _vPlayList;		//프레임플레이 리스트


private:
	int _frameNum;					//프레임 수

	_vFrameList _frameList;			//프레임 위치 리스트
	_vPlayList _playList;			//플레이 리스트

	int _frameWidth;				//프레임 가로 크기
	int	_frameHeight;				//프레임 세로 세로

	BOOL _loop;						//루프 여부
	float _frameUpdateSec;			//프레임 업데이트 초
	float _elapsedSec;				//프레임 지난 초

	DWORD _nowPlayIdx;				//현재 플레이 인덱스 ( PLAY_LIST 값을 참조한다 )
	BOOL _play;						//현재 플레이 여부

	void* _obj;

	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;
	CALLBACK_FUNCTION _callbackFunction;

public:
	animation(void);
	~animation(void);

	HRESULT init(int totalW, int totalH, int frameW, int frameH);						//이미지 총 가로세로크기와 한 프레임의 가로세로 크기로 셋팅
	void release(void);

	//처음부터 끝까지
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);						//기본 셋팅
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열에 담아서 프레임 돌리기
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);					//플레이 프레임 배열로 셋팅
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//구간을 정해서 프레임 돌리기
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);		//플레이 프레임 시작과 종료로 셋팅
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void setFPS(float framePerSec);				//초당 갱신 횟수

	void frameUpdate(float elpasedTime);		//프레임 업데이트 타임

	void start(void);			//플레이 시작
	void stop(void);			//플레이 완전 정지
	void pause(void);			//플레이 일시 정시
	void resume(void);			//플레이 다시 시작

	//플레이 여부 확인
	inline BOOL isPlay(void) { return _play; }

	//프레임 위치를 얻는다.
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	//프래임 가로 크기를 얻는다.
	inline int getFrameWidth(void) { return _frameWidth; }

	//프레임 세로 크기를 얻는다.
	inline int getFrameHeight(void)	{ return _frameHeight; }

	inline int getPlayFrame() { return _nowPlayIdx; }
	inline int getMaxFrame() { return _playList.size()-1; }
};
