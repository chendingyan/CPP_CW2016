#include "StaticObject.h"


StaticObject::StaticObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY)
	: HookableObject(pEngine, sizeX, sizeY, posX, posY),
	m_pEngine(pEngine)
{
}


StaticObject::~StaticObject()
{
}


void StaticObject::DoUpdate(int iCurrentTime)
{
	if (!IsVisible()){
		return;
	}
	m_mode = isHooked();
	//RedrawWholeScreen();
	//RedrawObjects();
}


int StaticObject::getMode()
{
	return m_mode;
}
