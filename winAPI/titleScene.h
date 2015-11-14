#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
private:
	enum BTN_STYLE { BTN_START = 0, BTN_EXIT, BTN_MAX };
public:
	titleScene();
	~titleScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

private:
	void buttonStateUpdate();
	void buttonImageUpdate();

private:
	image* _bg;
	image* _startBtn;
	image* _exitBtn;

	BTN_STYLE _stelectedBtn;

};

