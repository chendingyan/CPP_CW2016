#include "HookableObject.h"
#include "HookObject.h"


HookableObject::HookableObject(GoldMinerEngine * pEngine, int sizeX, int sizeY, int posX, int posY)
	:DisplayableObject(pEngine),
	m_pEngine(pEngine),
	m_mode(0),
	m_SizeX(sizeX),
	m_SizeY(sizeY),
	m_PosX(posX),
	m_PosY(posY)
{
}


HookableObject::~HookableObject()
{
}


int HookableObject::isHooked()
{
	HookObject * hook = dynamic_cast<HookObject*>(m_pEngine->GetDisplayableObject(HOOKID));
	//check if the hook has hooked the object
	double xcenter = hook->x1 + 1 / 2 * (hook->getLen1()) * SDL_cos((60 + hook->m_angle)*M_PI / 180);
	double ycenter = hook->y1 + 1 / 2 * (hook->getLen1()) * SDL_sin((60 + hook->m_angle)*M_PI / 180);
	if ((xcenter < m_iCurrentScreenX + m_iDrawWidth && xcenter > m_iCurrentScreenX) && (ycenter < m_iCurrentScreenY + m_iDrawHeight && ycenter > m_iCurrentScreenY) && !hook->isHook){
		m_mode = 1;
		hook->isHook = true;
		hook->m_mode = 3;
		RedrawWholeScreen();
		hook->changeSpeed(type, m_SizeX);
	}

	switch (m_mode)
	{
	case 1:
		iCurrentScreenX -= hook->m_speedX;
		m_iCurrentScreenX = iCurrentScreenX;


		iCurrentScreenY -= hook->m_speedY;
		m_iCurrentScreenY = iCurrentScreenY;

		if ((iCurrentScreenX >= hook->m_PosX - 3 || iCurrentScreenX <= hook->m_PosX + 3) && iCurrentScreenY <= hook->m_PosY + 1){
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


void HookableObject::Draw()
{
}


void HookableObject::DoUpdate(int iCurrentTime)
{
	BombDetection();
}


void HookableObject::BombDetection()
{
	DisplayableObject * object = m_pEngine->GetDisplayableObject(HOOKID);
	HookObject * hook = dynamic_cast<HookObject *>(object);

	if (hook->explode == 1){
		for (int i = 1; i < 50; i++){
			HookableObject * object = dynamic_cast<HookableObject*>(m_pEngine->GetDisplayableObject(i));
			if (object != NULL){
				int dx = object->m_PosX+ m_SizeX/2 - m_pEngine->tilex - 60;
				int dy = object->m_PosY+ m_SizeY/2 - m_pEngine->tiley - 60;
				if (dx * dx + dy *dy < 60 * 60){
					//SetVisible(false);
					m_pEngine->StoreObjectInArray(i, NULL);
				}
			}
		}
		
	}
}
