#pragma once
#include "StaticObject.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "GoldMinerEngine.h"

class GoldObject :
	public StaticObject
{
public:
	GoldObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY);
	~GoldObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
	GoldMinerEngine * m_pEngine;
private:
	ImageData gold;
};

