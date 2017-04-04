#pragma once
#include "DynamicObject.h"

class PigObject :
	public DynamicObject
{
public:
	PigObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY, double speed);
	~PigObject();
	ImageData prl1, prr1, prl2, prr2, prl3, prr3, ph;//stands for pig_run_left and pig_run_right and pig_hook
	GoldMinerEngine * m_pEngine;

	void Draw();
	void DoUpdate(int iCurrentTime);
};

