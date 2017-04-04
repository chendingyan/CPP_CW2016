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


bool DynamicObject::CollsionDetection(HookableObject * obj)
{
	if (obj->m_PosY < GetYCentre() && obj->m_PosY + obj->m_SizeY > GetYCentre()){
		if (direction == 1){
			int distance = obj->m_PosX + obj->m_SizeX - iCurrentScreenX;
			if ( SDL_abs(distance) <= 1){
				return true;
			}
		}
		else if (direction == 2){
			int distance = obj->m_PosX - iCurrentScreenX - m_SizeX;
			if ( SDL_abs(distance) <= 1){
				return true;
			}
		}
	}
	return false;
}


