#pragma once
#include "DynamicObject.h"
class BadPigObject :
	public DynamicObject
{
public:
	BadPigObject(GoldMinerEngine *pEngine, int sizeX, int sizeY, int posX, int posY, int speed);
	~BadPigObject();
	ImageData prl1, prr1, prl2, prr2, prl3, prr3;//stands for pig_run_left and pig_run_right
	GoldMinerEngine * m_pEngine;
	int updown;
	int diamond_loc[2];
	int starttime;
	int score;
private:
	int direction;
	int num_of_diamond;
	int diamond_help;
	int offset;
	int min;
public:
	void Draw();
	void DoUpdate(int iCurrentTime);
	void DiamondSearchAlgorithm();
};

