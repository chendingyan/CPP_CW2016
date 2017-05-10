#include "PigObject.h"
#include "HookObject.h"

PigObject::PigObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY, double speed)
	: DynamicObject(pEngine, sizeX, sizeY, posX, posY, speed),
	m_pEngine(pEngine),
	score(0),
	starttime(0)
{
	type = 4;
	m_iCurrentScreenX = m_iPreviousScreenX = iCurrentScreenX = posX;
	m_iCurrentScreenY = m_iPreviousScreenY = iCurrentScreenY = posY;

	//we also need space for numbers on the pig
	m_iDrawWidth = m_SizeX;
	m_iDrawHeight = m_SizeY + 30;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	prl1.LoadImage("./img/pig_run1_left.png");
	prr1.LoadImage("./img/pig_run1_right.png");
	prl2.LoadImage("./img/pig_run2_left.png");
	prr2.LoadImage("./img/pig_run2_right.png");
	prl3.LoadImage("./img/pig_run3_left.png");
	prr3.LoadImage("./img/pig_run3_right.png");
	ph.LoadImage("./img/pig_hook.png");

	SetVisible(true);
}


PigObject::~PigObject()
{
}


void PigObject::Draw()
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
			ph.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, iCurrentScreenX, iCurrentScreenY + 30, ph.GetWidth(), ph.GetHeight());
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


void PigObject::DoUpdate(int iCurrentTime)
{
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
			if (obj != NULL){
				if (CollsionDetection(obj)){
					direction = 2;
				}
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
			if (obj != NULL){
				if (CollsionDetection(obj)){
					direction = 1;
				}
			}
			
		}
		break;
	default:
		break;
	}
	m_mode = isHooked();
}


int PigObject::isHooked()
{
	HookObject * hook = dynamic_cast<HookObject*>(m_pEngine->GetDisplayableObject(0));
	//check if the hook has hooked the object
	double xcenter = hook->x1 + 1 / 2 * (hook->getLen1()) * SDL_cos((60 + hook->m_angle)*M_PI / 180);
	double ycenter = hook->y1 + 1 / 2 * (hook->getLen1()) * SDL_sin((60 + hook->m_angle)*M_PI / 180);
	if ((xcenter < m_iCurrentScreenX + m_iDrawWidth && xcenter > m_iCurrentScreenX) && (ycenter < m_iCurrentScreenY + m_iDrawHeight-30 && ycenter > m_iCurrentScreenY) && !hook->isHook){
		m_mode = 1;
		hook->isHook = true;
		hook->m_mode = 3;
		RedrawWholeScreen();
		hook->changeSpeed(type, m_SizeX);
		direction = 0;
	}
	

	switch (m_mode)
	{
	case 1:
		iCurrentScreenX -= hook->m_speedX;
		m_iCurrentScreenX = iCurrentScreenX;


		iCurrentScreenY -= hook->m_speedY;
		m_iCurrentScreenY = iCurrentScreenY;

		if ((iCurrentScreenX > hook->m_PosX - 1 || iCurrentScreenY < hook->m_PosX + 1) && iCurrentScreenY < hook->m_PosY + 1){
			m_mode = 2;
			hook->isHook = false;
			iCurrentScreenX = hook->m_PosX;
			iCurrentScreenY = hook->m_PosY;
			m_iCurrentScreenX = iCurrentScreenX;
			m_iCurrentScreenY = iCurrentScreenY;
		}
		break;
	case 2:
		//let m_iCurrentScreenX and m_iCurrentScreenY to the right top part
		if (m_iCurrentScreenX < 800){
			iCurrentScreenX += 10;
			m_iCurrentScreenX = iCurrentScreenX;
		}
		if (m_iCurrentScreenY > 0){
			iCurrentScreenY -= 5;
			m_iCurrentScreenY = iCurrentScreenY;
		}

		//add score
		if (m_iCurrentScreenX > 700){

			m_mode = 0;
			switch (type)
			{
			case 1: m_pEngine->score += 50; break;
			case 2: m_pEngine->score += 10; break;
			case 3: m_pEngine->score += 200; break;
			case 4: m_pEngine->score += score; break;
			default:
				break;
			}
			SetVisible(false);
			m_mode = 0;
		}
		break;
	default:
		break;
	}
	return m_mode;
}
