#pragma once

#include "StageClass.h"
class PauseStage :
	public StageClass
{
public:
	PauseStage(GoldMinerEngine * engine);
	~PauseStage();
	virtual void SetBackground();
	virtual void DrawStringsOnTheTop();
	virtual void KeyPressed(int iKeyCode);
	void UnDrawStrings();
	void UndrawObjects();
	void DrawObjects();
};

