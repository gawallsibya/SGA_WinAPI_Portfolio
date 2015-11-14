#include "StdAfx.h"
#include "sceneManager.h"
#include "gameNode.h"


//�ε� �����
DWORD CALLBACK loadingScene(LPVOID prc)
{
	//��ü �� init �Լ� �����Ѵ�..
	sceneManager::_readyScene->init();

	//������� ��ü�� ������ �ٲ۴�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε��� �����Ѵ�
	sceneManager::_loadScene->release();
	sceneManager::_loadScene = NULL;
	sceneManager::_readyScene = NULL;

	return NULL;
}

sceneManager::sceneManager(void)
{
}

sceneManager::~sceneManager(void)
{
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	miSceneList iter = _mSceneList.begin();

	for (; iter != _mSceneList.end() ;)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mSceneList.clear();
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//�� �߰�~~
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

//�ε��� �߰�~~
gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}

//��ü����
HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã����...
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ� �ϴ� ���� ������� ������ ����..
	if (find->second == _currentScene) return E_FAIL;

	//ã���� ����� ���� �ʱ�ȭ�Ѵ�
	if (SUCCEEDED(find->second->init()))
	{
		//������ ���� ������ ������...
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã����...
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ� �ϴ� ���� ������� ������ ����..
	if (find->second == _currentScene) return E_FAIL;

	//�ε��� ã�´�
	miSceneList findLoading = _mLoadingSceneList.find(loadingSceneName);

	//�ε��� ã�Ƽ� ������ �ٷ� ��ü�� ��...
	if (findLoading == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	//ã���� ����� ���� �ʱ�ȭ�Ѵ�
	if (SUCCEEDED(findLoading->second->init()))
	{
		//������ ���� ������ ������...
		if (_currentScene) _currentScene->release();

		//�ε���
		_currentScene = findLoading->second;

		//�ε����� �Ŀ� ����� �� ���� �ִ´�
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, loadingScene, NULL, 0, &_loadThreadID));

		return S_OK;
	}

	return E_FAIL;
}

