#include "stdafx.h"
#include "ui_state.h"
#include "remilia.h"
#include "myProgressBar.h"
#include "card.h"

ui_state::ui_state() : 
_player(nullptr),
//_boss(nullptr),
_ui_bg(nullptr),
_ui_bg_effect(nullptr),
_hpBar(nullptr),
_spBar(nullptr),
//_hpBarBoss(nullptr),
_card1(nullptr),
_card2(nullptr)
{
}


ui_state::~ui_state()
{
}


void ui_state::init(remilia* target)
{
	_player = target;

	IMAGEMANAGER->addFrameImage("ui_state2", "ImageResource/ui_state2.bmp", 0.f, 0.f, 1600, 95, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ui_state3", "ImageResource/ui_state3.bmp", 0.f, 0.f, 1600, 95, 1, 1, false, RGB(255, 0, 255));
	_ui_bg = IMAGEMANAGER->findImage("ui_state2");
	_ui_bg_effect = IMAGEMANAGER->findImage("ui_state3");

	_hpBar = new myProgressBar;
	_hpBar->init("ui_state_hpBar_top", "hpBar_bottom", 100, 20, 700, 20, _player->getMaxHP(), _player->getHPAdress(), 255, 128);
	_spBar = new myProgressBar;
	_spBar->init("ui_state_spBar_top", "spBar_bottom", 100, 50, 500, 20, _player->getMaxSP(), _player->getSPAdress(), 255, 128);

	_card1 = new card;
	_card1->init("card_gungnir", 830, 20, 41, 65, 100, _player->getSPAdress());
	_card2 = new card;
	_card2->init("card_huyajyou", 880, 20, 41, 65, 200, _player->getSPAdress());
}

void ui_state::update()
{
	_hpBar->update();
	_spBar->update();
	_card1->update();
	_card2->update();

	//if (_boss != nullptr && *_boss->getHPAdress() <= 0.f) SAFE_DELETE(_hpBarBoss);
	//if (_hpBarBoss != nullptr) _hpBarBoss->update();
}

void ui_state::render(HDC hdc)
{
	_ui_bg->alphaRender(hdc, 0, 0, 0, 0, _ui_bg->getFrameWidth(), _ui_bg->getFrameHeight(), 255, true);
	_hpBar->render(hdc);
	_spBar->render(hdc);

	//if (_hpBarBoss != nullptr) _hpBarBoss->render(hdc);

	_card1->render(hdc);
	_card2->render(hdc);
	_ui_bg_effect->alphaRender(hdc, 0, 0, 0, 0, _ui_bg->getFrameWidth(), _ui_bg->getFrameHeight(), 255, true);
}

void ui_state::release()
{
	_player = nullptr;
	//_boss = nullptr;
	_ui_bg = nullptr;

	SAFE_DELETE(_hpBar);
	SAFE_DELETE(_spBar);
	//SAFE_DELETE(_hpBarBoss);
}

//void ui_state::setBossMemoryAddressLink(enemy* boss) 
//{
//	_boss = boss;
//
//	if (_hpBarBoss != nullptr) SAFE_DELETE(_hpBarBoss);
//
//	_hpBarBoss = new myProgressBar;
//	_hpBarBoss->init("hpBar_top", "hpBar_bottom", 250, 100, 1000, 50, _boss->getMaxHP(), _boss->getHPAdress(), 180, 180);
//}