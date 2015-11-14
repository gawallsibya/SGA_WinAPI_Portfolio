#include "stdafx.h"
#include "goldCatfish.h"

void goldCatfish::animationInit()
{
	// goldCatfish right
	KEYANIMANAGER->addCoordinateFrameAnimation("r_goldCatfish_idle", "goldCatfish_idle", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_goldCatfish_jump_ready", "goldCatfish_jump", 0, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_goldCatfish_jump_start", "goldCatfish_jump", 1, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_goldCatfish_die", "goldCatfish_die", 0, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_goldCatfish_spark", "goldCatfish_spark", 0, 0, 10, false, false);


	// goldCatfish left
	KEYANIMANAGER->addCoordinateFrameAnimation("l_goldCatfish_idle", "goldCatfish_idle", 1, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_goldCatfish_jump_ready", "goldCatfish_jump", 1, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_goldCatfish_jump_start", "goldCatfish_jump", 0, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_goldCatfish_die", "goldCatfish_die", 0, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_goldCatfish_spark", "goldCatfish_spark", 0, 0, 10, false, false);


	// goldCatfish effect center
	KEYANIMANAGER->addCoordinateFrameAnimation("goldCatfish_jump_start_effect", "goldCatfish_jump_start_effect", 0, 35, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("goldCatfish_spark_effect1", "goldCatfish_spark_effect1", 0, 29, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("goldCatfish_spark_effect2", "goldCatfish_spark_effect2", 0, 0, 10, false, false);
}