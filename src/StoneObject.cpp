#include "StoneObject.h"


StoneObject::StoneObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY)
	: StaticObject(pEngine, sizeX, sizeY, posX, posY),
	m_pEngine(pEngine)
{
	type = 2;
	m_iCurrentScreenX = m_iPreviousScreenX = iCurrentScreenX = m_PosX;
	m_iCurrentScreenY = m_iPreviousScreenY = iCurrentScreenY = m_PosY;

	m_iDrawWidth = m_SizeX;
	m_iDrawHeight = m_SizeY;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	stone.LoadImage("./img/stone.png");
	SetVisible(true);
}


StoneObject::~StoneObject()
{
}


void StoneObject::Draw()
{
	if (!IsVisible()){
		return;
	}
	switch (m_mode)
	{
	case 0:
	case 1:
		stone.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, stone.GetWidth(), stone.GetHeight());
		break;
	case 2:
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "+10 points!", 0xff0000);
		break;
	default:
		break;
	}
	StoreLastScreenPositionForUndraw();
}


void StoneObject::DoUpdate(int iCurrentTime)
{
	StaticObject::DoUpdate(iCurrentTime);
	m_mode = getMode();
}
