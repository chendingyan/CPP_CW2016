#pragma once

#include "StageClass.h"
class WinStage :
	public StageClass
{
public:
	WinStage(GoldMinerEngine * engine);
	~WinStage();
	virtual void SetBackground();
	virtual void KeyPressed(int iKeyCode);
};

