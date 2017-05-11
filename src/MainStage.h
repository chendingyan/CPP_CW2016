#pragma once
#include "StageClass.h"
class MainStage :
	public StageClass
{
public:
	MainStage(GoldMinerEngine *engine);
	~MainStage();
	virtual void SetBackground();
	BombObject stone_bomber;
	// Get a reference to the current tile manager
	BombObject& GetTileManager() { return stone_bomber; }
	virtual void DrawStringsOnTheTop();
	virtual void KeyPressed(int iKeyCode);
	virtual void Run();
	void UndrawObjects();
	void DrawObjects();
};

