#include "StdAfx.h"
#include "loadScene.h"

loadScene::loadScene()
{
}
loadScene::~loadScene()
{
}

HRESULT loadScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이곳에 이미지 추가할것 전부 집어 넣어라

	// remilia
	_loading->loadFrameImage("remilia_idle", "ImageResource/remilia_idle.bmp", 0, 0, 1136, 108, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_walk_back", "ImageResource/remilia_walk_back.bmp", 0, 0, 1404, 104, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_walk_forward", "ImageResource/remilia_walk_forward.bmp", 0, 0, 1088, 99, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_dash_back", "ImageResource/remilia_dash_back.bmp", 0, 0, 1551, 117, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_dash_back_air", "ImageResource/remilia_dash_back_air.bmp", 0, 0, 1512, 109, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_dash_forward", "ImageResource/remilia_dash_forward.bmp", 0, 0, 1280, 111, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_dash_forward_air", "ImageResource/remilia_dash_forward_air.bmp", 0, 0, 1170, 142, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_jump", "ImageResource/remilia_jump.bmp", 0, 0, 2628, 109, 18, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_sit", "ImageResource/remilia_sit.bmp", 0, 0, 1056, 89, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_attack_a1", "ImageResource/remilia_attack_a1.bmp", 0, 0, 820, 91, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_attack_a2", "ImageResource/remilia_attack_a2.bmp", 0, 0, 1472, 129, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_attack_a3", "ImageResource/remilia_attack_a3.bmp", 0, 0, 1704, 115, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_attack_c1", "ImageResource/remilia_attack_c1.bmp", 0, 0, 2790, 133, 15, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_shot_b", "ImageResource/remilia_shot_b.bmp", 0, 0, 1168, 119, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_shot_gungnir", "ImageResource/remilia_shot_gungnir.bmp", 0, 0, 3420, 146, 19, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_huyajyou", "ImageResource/remilia_huyajyou.bmp", 0, 0, 1474, 126, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_hit_down_back", "ImageResource/remilia_hit_down_back.bmp", 0, 0, 500, 70, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_stand_up_back", "ImageResource/remilia_stand_up_back.bmp", 0, 0, 850, 100, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_hit_down_forward", "ImageResource/remilia_hit_down_forward.bmp", 0, 0, 360, 82, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_hit_forward", "ImageResource/remilia_hit_forward.bmp", 0, 0, 372, 113, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_card_gungnir", "ImageResource/remilia_card_gungnir.bmp", 0, 0, 41, 65, 1, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("remilia_card_huyajyou", "ImageResource/remilia_card_huyajyou.bmp", 0, 0, 41, 65, 1, 1, false, RGB(255, 0, 255));

	// remilia effect
	_loading->loadFrameImage("remilia_attack_c1_effect", "ImageResource/remilia_attack_c1_effect.bmp", 0, 0, 1728, 174, 9, 1, false, RGB(0, 0, 0));
	_loading->loadFrameImage("remilia_attack_a3_effect", "ImageResource/remilia_attack_a3_effect.bmp", 0, 0, 1340, 1193, 10, 8, false, RGB(0, 0, 0));
			  
	_loading->loadFrameImage("remilia_shot_b_missile", "ImageResource/remilia_shot_b_missile.bmp", 0, 0, 800, 210, 10, 2, false, RGB(0, 0, 0));
	_loading->loadFrameImage("remilia_gungnir", "ImageResource/remilia_gungnir.bmp", 0, 0, 520, 440, 1, 1, false, RGB(0, 0, 0));
			  
	_loading->loadFrameImage("remilia_shot_gungnir_create_effect", "ImageResource/remilia_shot_gungnir_create_effect.bmp", 0, 0, 2600, 3080, 5, 7, false, RGB(0, 0, 0));
	_loading->loadFrameImage("remilia_shot_gungnir_ready_effect", "ImageResource/remilia_shot_gungnir_ready_effect.bmp", 0, 0, 2184, 426, 6, 1, false, RGB(0, 0, 0));
	_loading->loadFrameImage("remilia_gungnir_effect", "ImageResource/remilia_gungnir_effect.bmp", 0, 0, 1560, 440, 3, 1, false, RGB(0, 0, 0));
	_loading->loadFrameImage("remilia_huyajyou_effect", "ImageResource/remilia_huyajyou_effect.bmp", 0, 0, 4716, 6905, 5, 7, false, RGB(0, 0, 0));
	
	_loading->loadFrameImage("remilia_hit_effect1", "ImageResource/remilia_hit_effect1.bmp", 0, 0, 2304, 64, 18, 1, false, RGB(0, 0, 0));
	_loading->loadFrameImage("remilia_hit_effect2", "ImageResource/remilia_hit_effect2.bmp", 0, 0, 1824, 96, 19, 1, false, RGB(0, 0, 0));

	// goldCatfish
	_loading->loadFrameImage("goldCatfish_idle", "ImageResource/goldCatfish_idle.bmp", 0, 0, 1120, 329, 2, 1, false, RGB(1, 0, 1));
	_loading->loadFrameImage("goldCatfish_jump", "ImageResource/goldCatfish_jump.bmp", 0, 0, 1160, 401, 2, 1, false, RGB(1, 0, 1));
	_loading->loadFrameImage("goldCatfish_die", "ImageResource/goldCatfish_die.bmp", 0, 0, 560, 290, 1, 1, false, RGB(1, 0, 1));
	_loading->loadFrameImage("goldCatfish_spark", "ImageResource/goldCatfish_spark.bmp", 0, 0, 660, 346, 1, 1, false, RGB(1, 0, 1));

	// goldCatfish effect
	_loading->loadFrameImage("goldCatfish_jump_start_effect", "ImageResource/goldCatfish_jump_start_effect.bmp", 0, 0, 6000, 1500, 8, 5, false, RGB(255, 0, 255));
	_loading->loadFrameImage("goldCatfish_spark_effect1", "ImageResource/goldCatfish_spark_effect1.bmp", 0, 0, 19800, 256, 30, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("goldCatfish_spark_effect2", "ImageResource/goldCatfish_spark_effect2.bmp", 0, 0, 600, 600, 1, 1, false, RGB(255, 0, 255));


	// snake
	_loading->loadFrameImage("snake_walk_forward", "ImageResource/snake_walk_forward.bmp", 0, 0, 924, 99, 6, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("snake_idle", "ImageResource/snake_idle.bmp", 0, 0, 1500, 97, 10, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("snake_die", "ImageResource/snake_die.bmp", 0, 0, 1200, 114, 5, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("snake_attack", "ImageResource/snake_attack.bmp", 0, 0, 2520, 97, 6, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("snake_hit_forward", "ImageResource/snake_hit_forward.bmp", 0, 0, 148, 114, 1, 1, false, RGB(255, 0, 255));


	// blueBoogie
	_loading->loadFrameImage("blueBoogie_walk_forward", "ImageResource/blueBoogie_walk_forward.bmp", 0, 0, 848, 84, 8, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("blueBoogie_idle", "ImageResource/blueBoogie_idle.bmp", 0, 0, 848, 86, 8, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("blueBoogie_die", "ImageResource/blueBoogie_die.bmp", 0, 0, 800, 154, 5, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("blueBoogie_attack", "ImageResource/blueBoogie_attack.bmp", 0, 0, 1824, 95, 12, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("blueBoogie_hit_forward", "ImageResource/blueBoogie_hit_forward.bmp", 0, 0, 104, 95, 1, 1, false, RGB(255, 0, 255));


	// stageObject
	_loading->loadFrameImage("stage_portal_on", "ImageResource/stage_portal_on.bmp", 0, 0, 560, 121, 8, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_portal_off", "ImageResource/stage_portal_off.bmp", 0, 0, 560, 121, 8, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_blind_black", "ImageResource/stage_blind_black.bmp", 0, 0, 1600, 900, 1, 1, false, RGB(255, 0, 255));
	_loading->loadFrameImage("stage_blind_white", "ImageResource/stage_blind_white.bmp", 0, 0, 1600, 900, 1, 1, false, RGB(255, 0, 255));

	return S_OK;
}

void loadScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩끝난후 화면전환
	if (!_loading->loadNext())
	{
		SCENEMANAGER->changeScene("gameScene");
	}
}

void loadScene::render(void)
{
	_loading->render();
}

