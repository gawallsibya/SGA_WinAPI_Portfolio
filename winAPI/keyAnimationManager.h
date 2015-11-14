#pragma once
#include "singletonBase.h"
#include <map>

//클래스 전방선언
class image;
class animation;

class keyAnimationManager : public singletonBase <keyAnimationManager>
{
private:
	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterAnimations;

private:
	arrAnimation _mTotalAnimations;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//처음부터 끝까지 쭈욱~ 애니매이션을 돌려라
	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop, void* cbFunction, void* obj);

	//수동으로 선택한(배열에담아서) 애니매이션을 돌려라
	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop);
	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop, void* cbFunction);
	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop, void* cbFunction, void* obj);

	//시작과 끝의 좌표를 이용한 애니메이션을 돌려라
	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void start(string animationKeyName);	//애니메이션 시작
	void stop(string animationKeyName);		//애니메이션 종료
	void pause(string animationKeyName);	//애니메이션 일시정지
	void resume(string animationKeyName);	//애니메이션 다시시작

	//애니메이션 찾는다
	animation* findAnimation(string animationKeyName);

	//키애니메이션 모두 삭제한다
	void deleteAll(void);

	keyAnimationManager();
	~keyAnimationManager();

	
};

