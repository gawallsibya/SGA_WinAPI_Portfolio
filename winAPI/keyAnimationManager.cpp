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
	//모든 키애니메이션을 삭제한다
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

//처음부터 끝까지 쭈욱~ 애니매이션을 돌려라
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

//수동으로 선택한(배열에담아서) 애니매이션을 돌려라
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

//시작과 끝의 좌표를 이용한 애니메이션을 돌려라
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


//애니메이션 시작
void keyAnimationManager::start(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->start();
}

//애니메이션 종료
void keyAnimationManager::stop(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->stop();
}

//애니메이션 일시정지
void keyAnimationManager::pause(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->pause();
}

//애니메이션 다시시작
void keyAnimationManager::resume(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->resume();
}

//애니메이션 찾는다
animation* keyAnimationManager::findAnimation(string animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	if (iter != _mTotalAnimations.end())
	{
		return iter->second;
	}

	return NULL;
}

//키애니메이션 모두 삭제한다
void keyAnimationManager::deleteAll(void)
{
	//맵 전체를 돌며 지운다
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

