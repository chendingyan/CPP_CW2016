#pragma once
#include "StaticObject.h"
#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"

class DiamondObject :
	public StaticObject
{
public:
	DiamondObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY);
	~DiamondObject();
	GoldMinerEngine * m_pEngine;
	ImageData diamond;

	void Draw();
	void DoUpdate(int iCurrentTime);
};

