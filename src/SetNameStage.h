#pragma once
#include "StageClass.h"
class SetNameStage :
	public StageClass
{
public:
	SetNameStage(GoldMinerEngine * engine);
	~SetNameStage();
	virtual void SetBackground();
	virtual void KeyPressed(int iKeyCode);
};

