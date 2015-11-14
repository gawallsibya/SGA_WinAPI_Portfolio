#include "StdAfx.h"
#include "effectManager.h"
#include "effect.h"

effectManager::effectManager(void)
{
}

effectManager::~effectManager(void)
{
}

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	iterEffects lIter;
	for (lIter = _lEffects.begin(); lIter != _lEffects.end();)
	{
		effect* temp = (*lIter);
		lIter = _lEffects.erase(lIter);
		SAFE_DELETE(temp);
	}
}

void effectManager::update(void)
{
	iterEffects lIter;
	for (lIter = _lEffects.begin(); lIter != _lEffects.end();)
	{
		(*lIter)->update();
		if (!(*lIter)->getIsLife())
		{
			effect* temp = (*lIter);
			lIter = _lEffects.erase(lIter);
			SAFE_DELETE(temp);
		}
		else
		{
			++lIter;

		}
	}
}

void effectManager::render(void)
{
	iterEffects lIter;
	for (lIter = _lEffects.begin(); lIter != _lEffects.end(); ++lIter)
	{
		(*lIter)->render();
	}
}

void effectManager::play(string imageName, string aniName, float x, float y, float fps, bool reverse, BYTE alpha, bool bAlphaFormat, bool bCamera)
{
	effect* ef = new effect;
	ef->init(IMAGEMANAGER->findImage(imageName), KEYANIMANAGER->findAnimation(aniName), reverse, alpha, bAlphaFormat, bCamera);
	ef->setFPS(fps);
	ef->startEffect(x, y);
	
	_lEffects.push_back(ef);

}
