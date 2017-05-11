#pragma once

#include "GoldMinerEngine.h"
class GoldMinerEngine;

class StageClass
{
public:
	StageClass(GoldMinerEngine *engine);
	~StageClass();
	int label;
	virtual void SetBackground();
	GoldMinerEngine * engine;
	char buf[20];
	virtual void MousePressed(int iButton, int iX, int iY);
	virtual void DrawStringsOnTheTop();
	virtual void KeyPressed(int iKeyCode);
	virtual void Run();
	virtual void UnDrawStrings();
	virtual void UndrawObjects();
	virtual void DrawObjects();
	//BombObject stone_bomber;
	//// Get a reference to the current tile manager
	//virtual BombObject & GetTileManager();
};

