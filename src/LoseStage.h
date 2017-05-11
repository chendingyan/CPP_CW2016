#pragma once
#include "StageClass.h"
class LoseStage :
	public StageClass
{
public:
	LoseStage(GoldMinerEngine * engine);
	~LoseStage();
	virtual void SetBackground();
	virtual void KeyPressed(int iKeyCode);
};

