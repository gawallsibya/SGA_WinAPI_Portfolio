#pragma once
#include "gameNode.h"

class remilia;
class myProgressBar;
class card;

class ui_state : public singletonBase<ui_state>
{
public:
	ui_state();
	~ui_state();

	void init(remilia* target);
	void update();
	void render(HDC hdc);
	void release();

	void setBossMemoryAddressLink(enemy* boss);

private:
	remilia* _player;

	//enemy* _boss;

	image* _ui_bg;
	image* _ui_bg_effect;

	myProgressBar* _hpBar;
	myProgressBar* _spBar;

	//myProgressBar* _hpBarBoss;

	card* _card1;
	card* _card2;
};

