#include "HookObject.h"
#include "BombObject.h"
#include "MainStage.h"

HookObject::HookObject(GoldMinerEngine * pEngine, int loc_x, int loc_y, int angle = 30, int len1 = 20, int len2 = 20, string direction = "left", int rotatespeed = 3, int label = 0)
	:DisplayableObject(pEngine),
	m_pEngine(pEngine),
	m_angle(angle),
	m_mode(0),
	m_PosX(0),
	m_PosY(0),
	m_len1(len1),
	m_len2(len2),
	m_direction(direction),
	rotate_speed(rotatespeed),
	m_speedX(0),
	m_speedY(0),
	initial_speedX(0),
	initial_speedY(0),
	static_angle(0),
	isHook(false),
	speedParameter(1)
	, explode(0)
	, explode_x(0)
	, explode_y(0)
	, t_value(20)
	, mloc_x(loc_x)
	, mloc_y(loc_y)
	, bomblabel(label)
{
	m_iCurrentScreenX = m_iPreviousScreenX = iCurrentScreenX = m_PosX = GetEngine()->GetScreenWidth() / 2;	//set the hook at the middle of the width
	m_iCurrentScreenY = m_iPreviousScreenY = iCurrentScreenY = m_PosY = 150;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	SetVisible(true);

}


HookObject::~HookObject()
{
}


void HookObject::Draw()
{
	switch (m_mode)
	{
	case 0: //rotate
		Hook(m_angle);
		break;
	case 1:
		Hook(static_angle);
		GetEngine()->DrawThickLine(m_PosX, m_PosY, iCurrentScreenX, iCurrentScreenY, 0xffffff, 3, GetEngine()->GetSDLSurface());
		break;
	case 2:

	case 3:
		Hook(static_angle);
		GetEngine()->DrawThickLine(m_PosX, m_PosY, iCurrentScreenX, iCurrentScreenY, 0xffffff, 3, GetEngine()->GetSDLSurface());
		break;
	default:
		break;
	}
	
	//detect if the hook hooked bomb
	StageClass * stage = m_pEngine->getStage();
	if (stage->label == 1 && bomblabel == 0){
		BombObject &bomb = dynamic_cast<MainStage *>(stage)->GetTileManager();
		int length = bomb.GetTileHeight();
		int xDiff = abs(iCurrentScreenX - mloc_x);
		int yDiff = abs(iCurrentScreenY - mloc_y);

		if (explode == 0 && (xDiff*xDiff + yDiff*yDiff < (length / 2 + 20)*(length / 2 + 20))){
			explode = 1;
			m_mode = 2;
			explode_x = iCurrentScreenX;
			explode_y = iCurrentScreenY;
		}

		// tile animation
		if (explode == 1 && t_value > 5){
			t_value -= 1;
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					bomb.UpdateTile(m_pEngine, i, j, t_value);
				}
			}
		}

		if (t_value == 5){
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					bomb.UpdateTile(m_pEngine, i, j, -1);
				}
			}
			t_value = -1;
			explode = -1;
		}

	}
	
	StoreLastScreenPositionForUndraw();
}


void HookObject::DoUpdate(int iCurrentTime)
{
	GetEngine()->UpdateMouseInfo();
	if (m_mode == 0 && (GetEngine()->IsKeyPressed(SDLK_DOWN) || GetEngine()->GetCurrentButtonStates() == 1)) {
		m_mode = 1;
		//RedrawWholeScreen();
		//the speed should differ from angle
		static_angle = m_angle;
		initial_speedX = -(5 * SDL_sin((static_angle - 30) * M_PI / 180));
		initial_speedY = 5 * SDL_cos((static_angle - 30) * M_PI / 180);
	}
	switch (m_mode)
	{
	case 0: Rotate(); break;
	case 1: Pull(); break;
	case 2: Back(); break;
	case 3: Back(); break;
	default:
		break;
	}
	RedrawWholeScreen();

}


void HookObject::Hook(int angle)
{
	//angle is the angle between right hook and horizontal line
	//(x1,y1) is the left middle point of the hook
	x1 = iCurrentScreenX - m_len1 * SDL_cos((60 - angle) * M_PI / 180);
	y1 = iCurrentScreenY + m_len1 * SDL_sin((60 - angle) * M_PI / 180);
	//(x2,y2) is the right middle point of the hook  
	x2 = iCurrentScreenX + m_len1 * SDL_cos(angle * M_PI / 180);
	y2 = iCurrentScreenY + m_len1 * SDL_sin(angle * M_PI / 180);
	//(x3,y3) is the left bottom point of the hook
	x3 = x1 + m_len2 * SDL_sin((30 - angle) * M_PI / 180);
	y3 = y1 + m_len2 * SDL_cos((30 - angle) * M_PI / 180);
	//(x4,y4) is the right bottom point of the hook
	x4 = x2 + m_len2 * SDL_cos((60 + angle) * M_PI / 180);
	y4 = y2 + m_len2 * SDL_sin((60 + angle) * M_PI / 180);
	//draw hook with 4 lines
	m_iCurrentScreenX = iCurrentScreenX;
	m_iCurrentScreenY = iCurrentScreenY;
	GetEngine()->DrawThickLine(m_iCurrentScreenX, m_iCurrentScreenY, x1, y1, 0xffffff, 5, GetEngine()->GetSDLSurface());
	GetEngine()->DrawThickLine(m_iCurrentScreenX, m_iCurrentScreenY, x2, y2, 0xffffff, 5, GetEngine()->GetSDLSurface());
	GetEngine()->DrawThickLine(x1, y1, x3, y3, 0xffffff, 5, GetEngine()->GetSDLSurface());
	GetEngine()->DrawThickLine(x2, y2, x4, y4, 0xffffff, 5, GetEngine()->GetSDLSurface());
}


void HookObject::Rotate()
{
	if (m_direction == "left"){
		m_angle += rotate_speed;
		//change direction
		if (m_angle == 120){
			m_direction = "right";
		}
	}
	else if (m_direction == "right"){
		m_angle -= rotate_speed;
		if (m_angle == -60){
			m_direction = "left";
		}
	}
}


void HookObject::Pull()
{
	iCurrentScreenX += initial_speedX;
	iCurrentScreenY += initial_speedY;

	if (iCurrentScreenX < 50 || iCurrentScreenX > 750 || iCurrentScreenY > 550){
		m_mode = 2; //get nothing and back
		//Back(true);
		RedrawWholeScreen();
	}
	speedParameter = 1;
}

void HookObject::Back()
{
	m_speedX = initial_speedX * speedParameter;
	m_speedY = initial_speedY * speedParameter;
	iCurrentScreenX -= m_speedX;
	iCurrentScreenY -= m_speedY;

	//in case the vibration
	if ((iCurrentScreenX > m_PosX - 1 || iCurrentScreenX < m_PosX + 1) && iCurrentScreenY < m_PosY + 1){
		m_mode = 0;
		iCurrentScreenX = m_PosX;
		iCurrentScreenY = m_PosY;
		m_angle = static_angle;
	}
	
}

int HookObject::getLen1()
{
	return m_len1;
}


int HookObject::getLen2()
{
	return m_len2;
}

void HookObject::changeSpeed(int type, int size)
{
	speedParameter = 1;
	if (type == 0){
		speedParameter = 2;
	}
	else if (type == 1){
		speedParameter = 1.2-  size/100;
	}
	else if (type == 2){
		speedParameter = 0.3;
	}
	else if (type == 3){
		speedParameter = 0.8;
	}
	else if (type == 4){
		speedParameter = 0.5;
	}
}
