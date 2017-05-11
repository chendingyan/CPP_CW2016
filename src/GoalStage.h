#pragma once
#include "StageClass.h"
class GoalStage :
	public StageClass
{
public:
	GoalStage(GoldMinerEngine * engine);
	~GoalStage();
	virtual void SetBackground();
	virtual void KeyPressed(int iKeyCode);
};

