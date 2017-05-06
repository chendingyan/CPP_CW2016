#pragma once
#include "DisplayableObject.h"
#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"
class HookableObject :
	public DisplayableObject
{
public:
	HookableObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY);
	~HookableObject();

	int isHooked();
	void Draw();
	void DoUpdate(int iCurrentTime);
	int m_mode;
	int m_SizeX;
	int m_SizeY;
	int m_PosX;
	int m_PosY;
	int type;//1-gold, 2-stone...
	GoldMinerEngine * m_pEngine;
	double iCurrentScreenX, iCurrentScreenY;
	void BombDetection();
};

