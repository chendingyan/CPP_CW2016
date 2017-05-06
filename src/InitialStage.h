#pragma once

#include "StageClass.h"
class GoldMinerEngine;
class InitialStage :
	public StageClass
{
public:
	InitialStage(GoldMinerEngine *engine);
	~InitialStage();
	ImageData bg_img, start_button, score_button;
	virtual void SetBackground();
};

