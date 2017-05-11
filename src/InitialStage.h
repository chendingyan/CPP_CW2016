#pragma once

#include "StageClass.h"
class InitialStage :
	public StageClass
{
public:
	InitialStage(GoldMinerEngine *engine);
	~InitialStage();
	virtual void SetBackground();
	virtual void MousePressed(int iButton, int iX, int iY);
};

