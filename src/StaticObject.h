#pragma once
#include "HookableObject.h"
#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"

class StaticObject :
	public HookableObject
{
public:
	StaticObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY);
	~StaticObject();
	GoldMinerEngine * m_pEngine;
	

	void DoUpdate(int iCurrentTime);
};

