#pragma once
#include "StageClass.h"

class IntroStage :
	public StageClass
{
public:
	IntroStage(GoldMinerEngine * engine);
	~IntroStage();
	virtual void SetBackground();
	virtual void KeyPressed(int iKeyCode);
};

