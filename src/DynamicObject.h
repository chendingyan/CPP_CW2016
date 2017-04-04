#pragma once
#include "HookableObject.h"
#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"
class DynamicObject :
	public HookableObject
{
public:
	DynamicObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY, int speed);
	~DynamicObject();
	GoldMinerEngine * m_pEngine;
	double m_speed;
	int direction; //1-left, 2-right
	void Draw();
	void DoUpdate(int iCurrentTime);
};

