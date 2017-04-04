#include "DynamicObject.h"


DynamicObject::DynamicObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY, int speed)
	: HookableObject(pEngine, sizeX, sizeY, posX, posY),
	m_pEngine(pEngine),
	m_speed(speed),
	direction(1)
{
}


DynamicObject::~DynamicObject()
{
}


void DynamicObject::Draw()
{
}


void DynamicObject::DoUpdate(int iCurrentTime)
{
	if (!IsVisible()){
		return;
	}
	m_mode = isHooked();
}
