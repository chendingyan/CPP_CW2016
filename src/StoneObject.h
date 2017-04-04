#pragma once
#include "StaticObject.h"
#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"

class StoneObject :
	public StaticObject
{
public:
	StoneObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY);
	~StoneObject();

	void Draw();
	void DoUpdate(int iCurrentTime);
	
	GoldMinerEngine *m_pEngine;
	ImageData stone;
};

