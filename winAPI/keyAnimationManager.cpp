#include "stdafx.h"
#include "keyAnimationManager.h"
#include "image.h"
#include "animation.h"

keyAnimationManager::keyAnimationManager()
{
}

keyAnimationManager::~keyAnimationManager()
{
}

HRESULT keyAnimationManager::init(void)
{
	return S_OK;
}

void keyAnimationManager::release(void)
{
	//��� Ű�ִϸ��̼��� �����Ѵ�
	deleteAll();
}

void keyAnimationManager::update(void)
{
	iterAnimations iter = _mTotalAnimations.begin();
	for (iter; iter != _mTotalAnimations.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;
		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}
}

void keyAnimationManager::render(void)
{
}

//ó������ ������ �޿�~ �ִϸ��̼��� ������
void keyAnimationManager::addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAnimationManager::addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop, void* cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAnimationManager::addDefaultFrameAnimation(string animationKeyName, char* imageKeyName, float fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

//�������� ������(�迭����Ƽ�) �ִϸ��̼��� ������
void keyAnimationManager::addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAnimationManager::addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop, void* cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAnimationManager::addArrayFrameAnimation(string animationKeyName, char* imageKeyName, int* arr, int arrLen, float fps, int loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

//���۰� ���� ��ǥ�� �̿��� �ִϸ��̼��� ������
void keyAnimationManager::addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAnimationManager::addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop, void* cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAnimationManager::addCoordinateFrameAnimation(string animationKeyName, char* imageKeyName, int start, int end, float fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimations.insert(pair<string, animation*>(animationKeyName, ani));
}


//�ִϸ��̼� ����
void keyAnimationManager::start(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->start();
}

//�ִϸ��̼� ����
void keyAnimationManager::stop(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->stop();
}

//�ִϸ��̼� �Ͻ�����
void keyAnimationManager::pause(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->pause();
}

//�ִϸ��̼� �ٽý���
void keyAnimationManager::resume(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->resume();
}

//�ִϸ��̼� ã�´�
animation* keyAnimationManager::findAnimation(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	if (iter != _mTotalAnimations.end())
	{
		return iter->second;
	}

	return NULL;
}

//Ű�ִϸ��̼� ��� �����Ѵ�
void keyAnimationManager::deleteAll(void)
{
	//�� ��ü�� ���� �����
	iterAnimations iter = _mTotalAnimations.begin();

	for (; iter != _mTotalAnimations.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mTotalAnimations.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mTotalAnimations.clear();
}

