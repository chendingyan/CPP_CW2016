#pragma once
#include "StageClass.h"
class ScoreStage :
	public StageClass
{
public:
	ScoreStage(GoldMinerEngine * engine);
	~ScoreStage();
	virtual void SetBackground();
	virtual void DrawStringsOnTheTop();
	virtual void KeyPressed(int iKeyCode);
};

