#pragma once
#include "singletonbase.h"
#include <map>
#include <string>

class gameNode;

using namespace std;

class sceneManager : public singletonBase <sceneManager>
{
public:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	static gameNode* _currentScene;	//�����
	static gameNode* _loadScene;	//�ε���
	static gameNode* _readyScene;	//��ü ��� ���� ��

	mSceneList _mSceneList;
	mSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰�~~
	gameNode* addScene(string sceneName, gameNode* scene);

	//�ε��� �߰�~~
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//��ü����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);
	
	friend DWORD CALLBACK loadingScene(LPVOID prc);

	sceneManager(void);
	~sceneManager(void);
};
