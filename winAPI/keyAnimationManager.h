#pragma once
#include "singletonBase.h"
#include <map>

//Ŭ���� ���漱��
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

	//ó������ ������ �޿�~ �ִϸ��̼��� ������
	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop, void* cbFunction, void* obj);

	//�������� ������(�迭����Ƽ�) �ִϸ��̼��� ������
	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop);
	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop, void* cbFunction);
	void addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop, void* cbFunction, void* obj);

	//���۰� ���� ��ǥ�� �̿��� �ִϸ��̼��� ������
	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void start(string animationKeyName);	//�ִϸ��̼� ����
	void stop(string animationKeyName);		//�ִϸ��̼� ����
	void pause(string animationKeyName);	//�ִϸ��̼� �Ͻ�����
	void resume(string animationKeyName);	//�ִϸ��̼� �ٽý���

	//�ִϸ��̼� ã�´�
	animation* findAnimation(string animationKeyName);

	//Ű�ִϸ��̼� ��� �����Ѵ�
	void deleteAll(void);

	keyAnimationManager();
	~keyAnimationManager();

	
};

