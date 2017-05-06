#include "GoldObject.h"
#include "StaticObject.h"

GoldObject::GoldObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY)
	: StaticObject(pEngine, sizeX, sizeY, posX, posY),
	m_pEngine(pEngine)
{
	type = 1;
	m_iCurrentScreenX = m_iPreviousScreenX = iCurrentScreenX = posX;
	m_iCurrentScreenY = m_iPreviousScreenY = iCurrentScreenY = posY;

	m_iDrawWidth = m_SizeX;
	m_iDrawHeight = m_SizeY;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	switch (m_SizeX)
	{
	case 50: gold.LoadImage("./img/small_gold.png"); break;
	case 53: gold.LoadImage("./img/med_gold.png"); break;
	case 60: gold.LoadImage("./img/big_gold.png"); break;
	default:
		break;
	}

	SetVisible(true);
}


GoldObject::~GoldObject()
{
}


void GoldObject::Draw()
{
	if (!IsVisible()){
		return;
	}
	switch (m_mode)
	{
	case 0:
		//break;
	case 1:
		gold.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, gold.GetWidth(), gold.GetHeight());
		break;
	case 2:
		//show score
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "+50 points!", 0xff0000);
		break;
	default:
		break;
	}
	StoreLastScreenPositionForUndraw();
}


void GoldObject::DoUpdate(int iCurrentTime)
{
	m_mode = HookableObject::isHooked();
}
