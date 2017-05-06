#include "BadPigObject.h"
#include "templates.h"
#include "header.h"
#include "DiamondObject.h"
#include "PigObject.h"
BadPigObject::BadPigObject(GoldMinerEngine *pEngine, int sizeX, int sizeY, int posX, int posY, int speed)
	: DynamicObject(pEngine, sizeX, sizeY, posX, posY, speed)
	, m_pEngine(pEngine)
	, direction(1)
	, diamond_help(0)
	, min(1000000)
	, updown(0)
	, starttime(0)
	, score(0)

{
	diamond_loc[0] = 0;
	diamond_loc[1] = 0;
	m_iCurrentScreenX = m_iPreviousScreenX = iCurrentScreenX = posX;
	m_iCurrentScreenY = m_iPreviousScreenY = iCurrentScreenY = posY;
	//we also need space for numbers on the pig
	m_iDrawWidth = m_SizeX;
	m_iDrawHeight = m_SizeY + 30;
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	prl1.LoadImage("./img/badpig_left1.png");
	prr1.LoadImage("./img/badpig_right1.png");
	prl2.LoadImage("./img/badpig_left2.png");
	prr2.LoadImage("./img/badpig_right2.png");
	prl3.LoadImage("./img/badpig_left3.png");
	prr3.LoadImage("./img/badpig_right3.png");

	SetVisible(true);

}


BadPigObject::~BadPigObject()
{
}


void BadPigObject::Draw()
{
	if (!IsVisible()){
		return;
	}
	char * str = (char *)malloc(sizeof(char) * 10);
	switch (m_mode)
	{
	case 0:

		if (GetEngine()->GetTime() - starttime >= 300){
			score = rand() % 40 - 20;
			starttime = GetEngine()->GetTime();
		}
		sprintf(str, "%d", score);
		GetEngine()->DrawScreenString(iCurrentScreenX, iCurrentScreenY, str, 0xff0000);
		switch (direction)
		{
		case 1: // go left
			if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 0 && (static_cast<int> (m_iCurrentScreenX) % 9) < 3){
				prl1.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, prl1.GetWidth(), prl1.GetHeight());
			}
			else if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 3 && (static_cast<int> (m_iCurrentScreenX) % 9) < 6){
				prl2.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, prl2.GetWidth(), prl2.GetHeight());
			}
			else{
				prl3.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, prl3.GetWidth(), prl3.GetHeight());
			}
			break;
		case 2: // go right
			if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 0 && (static_cast<int> (m_iCurrentScreenX) % 9) < 3){
				prr1.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, prr1.GetWidth(), prr1.GetHeight());
			}
			else if ((static_cast<int> (m_iCurrentScreenX) % 9) >= 3 && (static_cast<int> (m_iCurrentScreenX) % 9) < 6){
				prr2.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, prr2.GetWidth(), prr2.GetHeight());
			}
			else{
				prr3.RenderImageWithMask(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, prr3.GetWidth(), prr3.GetHeight());
			}
			break;
		}

	case 1: //be caught
		if (direction == 0){
			prr2.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, iCurrentScreenX, iCurrentScreenY + 30, prr2.GetWidth(), prr2.GetHeight());
		}

		break;
	case 2:
		char buf[100];
		sprintf(buf, "+%d points!", score);
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, buf, 0xff0000);
		break;
	default:
		break;
	}
}


void BadPigObject::DoUpdate(int iCurrentTime)
{
	if (!IsVisible()){
		return;
	}
	if (diamond_help != -1){
		DiamondSearchAlgorithm();
	}

	if (diamond_loc[0] != 0){
		m_mode = HookableObject::isHooked();
		if (diamond_help == 0){
			if (m_iCurrentScreenX < diamond_loc[0]){
				m_iCurrentScreenX++;
				direction = 0;
				if (m_iCurrentScreenY + 30 < diamond_loc[1]){
					m_iCurrentScreenY++;
				}
				else if (m_iCurrentScreenY + 30 > diamond_loc[1]){
					m_iCurrentScreenY--;
				}
			}
			else{
				m_iCurrentScreenX--;
				direction = 1;
				if (m_iCurrentScreenY + 30 < diamond_loc[1]){
					m_iCurrentScreenY += 1;
				}
				else{
					m_iCurrentScreenY--;
				}
			}
		}
		else{
			updown++;
			if ((int)(iCurrentTime / 500) % 2 == 0){
				m_iCurrentScreenY++;
			}
			else{
				m_iCurrentScreenY--;
			}
		}
		RedrawObjects();
	}
	else{
		switch (direction)
		{
		case 1:
			iCurrentScreenX -= m_speed;
			m_iCurrentScreenX = iCurrentScreenX;
			if (iCurrentScreenX < 10){
				direction = 2;
			}
			for (int i = 1; i < m_pEngine->obj_num; i++){
				HookableObject * obj = dynamic_cast<HookableObject*> (GetEngine()->GetDisplayableObject(i));
				if (CollsionDetection(obj)){
					direction = 2;
				}
			}
			break;
		case 2:
			iCurrentScreenX += m_speed;
			m_iCurrentScreenX = iCurrentScreenX;
			if (iCurrentScreenX > 720){
				direction = 1;
			}
			for (int i = 1; i < m_pEngine->obj_num; i++){
				HookableObject* obj = dynamic_cast<HookableObject*> (GetEngine()->GetDisplayableObject(i));
				if (CollsionDetection(obj)){
					direction = 1;
				}
			}
			break;
		default:
			break;
		}
		m_mode = isHooked();
	}
}


void BadPigObject::DiamondSearchAlgorithm()
{
	num_of_diamond = m_pEngine->diamond_num;
	int obj_num = m_pEngine->obj_num;
	int gs_num = m_pEngine->gs_num;
	int counter = 0;
	int diamond_visit = 0;
	DisplayableObject * object;

	for (int i = gs_num; i < obj_num; i++){
		object = m_pEngine->GetDisplayableObject(i);
		DiamondObject * diamond = dynamic_cast<DiamondObject *>(object);

		if (diamond == NULL){
			return;
		}
		int dx = diamond->m_PosX;
		int dy = diamond->m_PosY;
		if (diamond->IsVisible()){
			if (m_mode != 0){
				diamond->pigLeaves();
				diamond_loc[0] = 0;
				diamond_help = -1;
				return;
			}

			if (diamond_help == 0){
				if (m_iCurrentScreenX < dx + 2 && m_iCurrentScreenY + 30 < dy + 2 && m_iCurrentScreenY + 30 > dy - 2 && m_iCurrentScreenX > dx - 2){
					diamond_help = 1;
					diamond->PigComes();
				}
				counter = 0;
				int distance = (m_iCurrentScreenX - dx)*(m_iCurrentScreenX - dx) + (m_iCurrentScreenY - dy)*(m_iCurrentScreenY - dy);

				if (distance < min){
					min = distance;
					diamond_loc[counter] = dx;
					counter++;
					diamond_loc[counter] = dy;
				}
			}
			else{
				if (updown > 40 && diamond->arrived == 1){
					diamond->pigWaits();
					updown = 0;
				}
			}
		}
		else{
			diamond_visit++;
			if (diamond->arrived == 1){
				diamond->pigLeaves();
				diamond_help = 0;
			}
			if (dx == diamond_loc[0] && dy == diamond_loc[1]){
				diamond_loc[0] = 0;
				diamond_loc[1] = 1;
				min = 1000000;
				diamond_help = 0;
			}
		}
	}
	if (diamond_visit == num_of_diamond){
		diamond_help = -1;
	}
}
