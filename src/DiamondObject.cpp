#include "DiamondObject.h"


DiamondObject::DiamondObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY)
	: StaticObject(pEngine, sizeX, sizeY, posX, posY),
	m_pEngine(pEngine)
{
	type = 3;
	m_iCurrentScreenX = iCurrentScreenX = m_iPreviousScreenX = posX;
	m_iCurrentScreenY = iCurrentScreenY = m_iPreviousScreenY = posY;

	m_iDrawWidth = sizeX;
	m_iDrawHeight = sizeY;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	
	diamond.LoadImage("./img/diamond.png");
	SetVisible(true);
}


DiamondObject::~DiamondObject()
{
}


void DiamondObject::Draw()
{
	if (!IsVisible()){
		return;
	}
	switch (m_mode)
	{
	case 0:
		
	case 1:
		diamond.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, diamond.GetWidth(), diamond.GetHeight());
		break;
	case 2:
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "+200 points!", 0xff0000);
		break;
	default:
		break;
	}
	StoreLastScreenPositionForUndraw();
}


void DiamondObject::DoUpdate(int iCurrentTime)
{
	StaticObject::DoUpdate(iCurrentTime);
	m_mode = getMode();
}