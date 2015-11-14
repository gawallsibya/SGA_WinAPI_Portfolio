#include "stdafx.h"
#include "remilia.h"

void remilia::animationInit()
{
	// remilia right
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_idle", "remilia_idle", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_walk_back", "remilia_walk_back", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_walk_forward", "remilia_walk_forward", 0, 7, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_back_ready", "remilia_dash_back", 0, 1, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_back_start", "remilia_dash_back", 2, 7, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_back_end", "remilia_dash_back", 8, 10, 20, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_back_air_ready", "remilia_dash_back_air", 0, 3, 9, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_back_air_start", "remilia_dash_back_air", 4, 6, 9, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_back_air_end", "remilia_dash_back_air", 7, 8, 9, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_forward_ready", "remilia_dash_forward", 0, 1, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_forward_start", "remilia_dash_forward", 2, 7, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_forward_end", "remilia_dash_forward", 8, 9, 20, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_forward_air_ready", "remilia_dash_forward_air", 0, 2, 9, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_forward_air_start", "remilia_dash_forward_air", 3, 6, 9, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_dash_forward_air_end", "remilia_dash_forward_air", 7, 8, 9, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_jump_ready", "remilia_jump", 0, 3, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_jump_start", "remilia_jump", 4, 13, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_jump_end", "remilia_jump", 14, 16, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_sit_start", "remilia_sit", 0, 3, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_sit_end", "remilia_sit", 4, 7, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a1_start", "remilia_attack_a1", 0, 2, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a1_end", "remilia_attack_a1", 3, 4, 20, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a2_start", "remilia_attack_a2", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a2_end", "remilia_attack_a2", 2, 7, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a3_start1", "remilia_attack_a3", 0, 3, 12, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a3_start2", "remilia_attack_a3", 4, 8, 12, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a3_end", "remilia_attack_a3", 9, 11, 12, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_c1_start", "remilia_attack_c1", 0, 6, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_c1_end", "remilia_attack_c1", 7, 14, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_shot_b_start", "remilia_shot_b", 0, 4, 15, false, false);
	int r_shot_b[] = { 5, 6, 5, 6, 5, 6, 6, 6, 6, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("r_remilia_shot_b_end", "remilia_shot_b", r_shot_b, 10, 15, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_shot_gungnir_create", "remilia_shot_gungnir", 0, 5, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_shot_gungnir_ready", "remilia_shot_gungnir", 6, 12, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_shot_gungnir_start", "remilia_shot_gungnir", 13, 18, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_huyajyou_ready", "remilia_huyajyou", 0, 2, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_huyajyou_start", "remilia_huyajyou", 3, 8, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_huyajyou_end", "remilia_huyajyou", 9, 9, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_hit_down_back", "remilia_hit_down_back", 0, 4, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_stand_up_back_ready", "remilia_stand_up_back", 0, 0, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_stand_up_back_start", "remilia_stand_up_back", 1, 4, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_hit_down_forward", "remilia_hit_down_forward", 3, 0, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_hit_forward", "remilia_hit_forward", 0, 2, 15, false, false);


	// remilia left
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_idle", "remilia_idle", 7, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_walk_back", "remilia_walk_back", 8, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_walk_forward", "remilia_walk_forward", 7, 0, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_back_ready", "remilia_dash_back", 10, 9, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_back_start", "remilia_dash_back", 8, 3, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_back_end", "remilia_dash_back", 2, 0, 20, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_back_air_ready", "remilia_dash_back_air", 8, 5, 9, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_back_air_start", "remilia_dash_back_air", 4, 2, 9, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_back_air_end", "remilia_dash_back_air", 1, 0, 9, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_forward_ready", "remilia_dash_forward", 9, 8, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_forward_start", "remilia_dash_forward", 7, 2, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_forward_end", "remilia_dash_forward", 1, 0, 20, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_forward_air_ready", "remilia_dash_forward_air", 8, 6, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_forward_air_start", "remilia_dash_forward_air", 5, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_dash_forward_air_end", "remilia_dash_forward_air", 1, 0, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_jump_ready", "remilia_jump", 17, 14, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_jump_start", "remilia_jump", 13, 4, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_jump_end", "remilia_jump", 3, 1, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_sit_start", "remilia_sit", 7, 4, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_sit_end", "remilia_sit", 3, 0, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a1_start", "remilia_attack_a1", 4, 2, 20, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a1_end", "remilia_attack_a1", 1, 0, 20, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a2_start", "remilia_attack_a2", 7, 6, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a2_end", "remilia_attack_a2", 5, 0, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a3_start1", "remilia_attack_a3", 11, 8, 12, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a3_start2", "remilia_attack_a3", 7, 3, 12, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_a3_end", "remilia_attack_a3", 2, 0, 12, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_c1_start", "remilia_attack_c1", 14, 8, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_c1_end", "remilia_attack_c1", 7, 0, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_shot_b_start", "remilia_shot_b", 7, 3, 15, false, false);
	int l_shot_b[] = { 2, 1, 2, 1, 2, 1, 1, 1, 1, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("l_remilia_shot_b_end", "remilia_shot_b", l_shot_b, 10, 15, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_shot_gungnir_create", "remilia_shot_gungnir", 18, 13, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_shot_gungnir_ready", "remilia_shot_gungnir", 12, 6, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_shot_gungnir_start", "remilia_shot_gungnir", 5, 0, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_huyajyou_ready", "remilia_huyajyou", 10, 8, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_huyajyou_start", "remilia_huyajyou", 7, 1, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_huyajyou_end", "remilia_huyajyou", 1, 1, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_hit_down_back", "remilia_hit_down_back", 4, 0, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_stand_up_back_ready", "remilia_stand_up_back", 4, 4, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_stand_up_back_start", "remilia_stand_up_back", 3, 0, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_hit_down_forward", "remilia_hit_down_forward", 0, 3, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_hit_forward", "remilia_hit_forward", 2, 0, 15, false, false);


	// remilia effect right
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_c1_effect", "remilia_attack_c1_effect", 0, 8, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a3_effect1", "remilia_attack_a3_effect", 0, 23, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a3_effect2", "remilia_attack_a3_effect", 24, 47, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_attack_a3_effect2", "remilia_attack_a3_effect", 24, 47, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_shot_b_missile", "remilia_shot_b_missile", 0, 19, 15, false, true);
	int r_gungnir_create[] = { 4, 3, 2, 1, 0, 9, 8, 7, 6, 5, 14, 13, 12, 11, 10, 19, 18, 17, 16, 15, 24, 23, 22, 21, 20, 29, 28, 27, 26, 25, 33, 32, 31, 30 };
	KEYANIMANAGER->addArrayFrameAnimation("r_remilia_shot_gungnir_create_effect", "remilia_shot_gungnir_create_effect", r_gungnir_create, 34, 15, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_shot_gungnir_ready_effect", "remilia_shot_gungnir_ready_effect", 0, 5, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_gungnir_effect", "remilia_gungnir_effect", 2, 0, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_remilia_gungnir", "remilia_gungnir", 0, 0, 15, false, false);

	// remilia effect left
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_attack_c1_effect", "remilia_attack_c1_effect", 8, 0, 15, false, false);
	int l_attack_a3_effect1[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 29, 28, 27, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("l_remilia_attack_a3_effect1", "remilia_attack_a3_effect", l_attack_a3_effect1, 24, 15, false);
	int l_attack_a3_effect2[] = { 25, 24, 23, 22, 21, 20, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 49, 48, 47, 46, 45, 44, 43, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("l_remilia_attack_a3_effect2", "remilia_attack_a3_effect", l_attack_a3_effect2, 24, 15, false);
	int l_shot_b_missile[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("l_remilia_shot_b_missile", "remilia_shot_b_missile", l_shot_b_missile, 20, 15, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_shot_gungnir_create_effect", "remilia_shot_gungnir_create_effect", 0, 33, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_shot_gungnir_ready_effect", "remilia_shot_gungnir_ready_effect", 5, 0, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_gungnir_effect", "remilia_gungnir_effect", 0, 2, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_remilia_gungnir", "remilia_gungnir", 0, 0, 15, false, false);

	// remilia effect center
	KEYANIMANAGER->addCoordinateFrameAnimation("remilia_huyajyou_effect", "remilia_huyajyou_effect", 0, 31, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("remilia_hit_effect1", "remilia_hit_effect1", 0, 17, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("remilia_hit_effect2", "remilia_hit_effect2", 0, 18, 10, false, false);
}