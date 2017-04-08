#include "GoldMinerEngine.h"
#include "HookObject.h"
#include "HookableObject.h"
#include "GoldObject.h"
#include "StoneObject.h"
#include "DiamondObject.h"
#include "PigObject.h"
#include "header.h"
#include "templates.h"
#include <cstdlib>
#define TIMELIMIT 60
using namespace std;
const int goals[10] = { 200, 400, 700, 900, 1000, 1200, 1500, 3000, 3200, 3300 };
char default_name[50] = "Name";
GoldMinerEngine::GoldMinerEngine()
	: m_State(0),
	score(0),
	Num_Of_Objects(0),
	start_time(TIMELIMIT),
	level(1)
	, gold_num(3)
	, stone_num(5)
	, diamond_num(2)
	, levelTime(TIMELIMIT)
	, remaining_time(TIMELIMIT)
	, text_pointer(-1)
	, name_x(350)
	, name_y(520)
	, name_init(350)
	, obj_num(10)
	, gs_num(0)
	, restart_time(0)
	, pause_time(0)
{
	bg_img.LoadImage("./img/background-ppt.png");
	start_button.LoadImage("./img/start.jpg");
	score_button.LoadImage("./img/scores.jpg");
	instruction_img.LoadImage("./img/instruction.jpg");
	bg1.LoadImage("./img/bg1.png");
	bg2.LoadImage("./img/bg2.png");
	bg3.LoadImage("./img/bg3.png");
	bg4.LoadImage("./img/bg4.png");
	score_bg.LoadImage("./img/score_bk.jpg");
	gs_num = obj_num - diamond_num;
	bombPosX = 10 * (rand() % 50 + 10);
	bombPosY = 10 * (rand() & 20 + 20);
	tile_width = 64;
	/*default_name = (char*)malloc(sizeof(char) * 100);
	default_name = "Name";*/
	player_name = (char*)malloc(sizeof(char) * 100);
}


GoldMinerEngine::~GoldMinerEngine()
{
}


void GoldMinerEngine::SetupBackgroundBuffer()
{
	int bombtile[3][3] = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } };
	char text[20];

	switch (m_State)
	{
		//initial state
	case 0:
		bg_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			bg_img.GetWidth(), bg_img.GetHeight());
		start_button.RenderImage(this->GetBackground(),
			0, 0,
			80, 470,
			start_button.GetWidth(), start_button.GetHeight());
		score_button.RenderImage(this->GetBackground(),
			0, 0,
			420, 470,
			score_button.GetWidth(), score_button.GetHeight());
		break;
		//playing
	case 1:
		FillBackground(0x8B4513);
		bg1.RenderImage(this->GetBackground(), 0, 0, 0, 0, this->GetScreenWidth(), 100);
		bomb.SetSize(3, 3);
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				bomb.SetValue(i, j, bombtile[i][j]);
			}
		}
		bomb.SetBaseTilesPositionOnScreen(bombPosX, bombPosY);
		bomb.DrawAllTiles(this, this->GetBackground(), 0, 0, 2, 2);

		break;
		//pause
	case 2:
		break;
		//win
	case 3:
		break;
		//lose
	case 4:
		FillBackground(0x000000);
		sprintf(text, "Game Over!");
		DrawBackgroundString(370, 200, text, 0xffffff, NULL);
		break;
		//set name
	case 5:
		bg_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			bg_img.GetWidth(), bg_img.GetHeight());
		DrawBackgroundString(240, 470, "Enter Your Name", 0xffffff, NULL);
		if (text_pointer == -1){
			DrawBackgroundString(name_init, name_y, default_name, 0xffffff, NULL);
		}
		break;
		//instruction
	case 6:
		instruction_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			instruction_img.GetWidth(), instruction_img.GetHeight());
		break;
		//the goal before game
	case 7:
		//FillBackground(0x000000);
		score_bg.RenderImage(this->GetBackground(), 0, 0, 0, 0, score_bg.GetWidth(), score_bg.GetHeight());
		sprintf(text, "Level %d", level);
		DrawBackgroundString(400, 250, text, 0x00000, NULL);
		sprintf(text, "Goal: %d", goals[level - 1]);
		DrawBackgroundString(400, 320, text, 0x00000, NULL);
		sprintf(text, "Press Space to start!");
		DrawBackgroundString(400, 390, text, 0x00000, NULL);
		break;
		//show scoreboard
	case 8:
		score_bg.RenderImage(this->GetBackground(), 0, 0, 0, 0, score_bg.GetWidth(), score_bg.GetHeight());
		break;
	default:
		break;
	}

}


void GoldMinerEngine::MouseDown(int iButton, int iX, int iY)
{
	switch (m_State)
	{
	case 0:
		if (iX > 80 && iX < 330 && iY > 470 && iY < 557){
			m_State = 5;
			SetupBackgroundBuffer();
			Redraw(true);
		}
		if (iX>420 && iX < 708 && iY> 470 && iY < 557){
			m_State = 8;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			//DisplayResults();//for file use
		}
		break;
	default:
		break;
	}
}


int GoldMinerEngine::InitialiseObjects()
{
	DrawableObjectsChanged();
	DestroyOldObjects();
	CreateObjectArray(10);
	if (m_State == 1){
		StoreObjectInArray(0, new HookObject(this, 30, 10, 5, "right", 1));
		StoreObjectInArray(1, new GoldObject(this, 53, 47, 200, 200));
		StoreObjectInArray(2, new GoldObject(this, 50, 50, 630, 310));
		StoreObjectInArray(3, new GoldObject(this, 93, 95, 400, 280));
		StoreObjectInArray(4, new StoneObject(this, 50, 50, 330, 250));
		StoreObjectInArray(5, new DiamondObject(this, 67, 50, 300, 400));
		StoreObjectInArray(6, new PigObject(this, 49, 48, 700, 170, 1));
		StoreObjectInArray(9, NULL);
	}
	Num_Of_Objects = 6;

	return 0;
}





void GoldMinerEngine::changeBackground()
{
	int offset = m_iTick - start_time;
	if (offset < 3000){
		RenderImageHelper(bg1);
	}
	else if (offset >= 3000 && offset <6000){
		RenderImageHelper(bg2);
	}
	else if (offset >= 6000 && offset < 9000){
		RenderImageHelper(bg3);
	}
	else if (offset >= 9000 && offset < 12000){
		RenderImageHelper(bg4);
	}
	else{
		start_time = GetTime();
	}
	
}


void GoldMinerEngine::RenderImageHelper(ImageData& image)
{
	image.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, GetScreenWidth(), 100);
	Redraw(true);
}


//void GoldMinerEngine::InitialisePosition(int gold_num, int stone_num, int diamond_num)
//{
//	int item_num = 0;
//	int tempx, tempy;
//	int xdiff, ydiff;
//	int dis;
//	int angle = 0;
//	int index; 
//	double x, y;
//
//	//start point (centerx, centery)
//	int centerx = 10 * (rand() % 20 + 30);
//	int centery = 10 * (rand() % 10 + 30);
//
//	int xarray[20];
//	int yarray[20];
//	int 
//
//}


void GoldMinerEngine::DrawStringOnTop()
{
	char right[100];
	char left [100];
	switch (m_State)
	{
	case 1:
		sprintf(right, "Score: %d", score);
		DrawScreenString(600, 10, right, 0x000000, NULL);
		sprintf(right, "Goal: %d", goals[level - 1]);
		DrawScreenString(600, 50, right, 0xffffff, NULL);
		sprintf(left, "Level: %d", level);
		DrawScreenString(30, 10, left, 0x000000, NULL);
		remaining_time = start_time - (int)(m_iTick - restart_time) / 1000;
		sprintf(left, "Time: %d", remaining_time);
		DrawScreenString(30, 50, left, 0xffffff, NULL);
		break;
	case 2:
		start_time = remaining_time;
		sprintf(left, "GAME STOP!");
		DrawScreenString(30, 10, left, 0x000000, NULL);
		break;
	case 7:
		sprintf(left, "SCORES");
		DrawScreenString(50, 20, left, 0x000000, NULL);
	default:
		break;
	}
}


void GoldMinerEngine::KeyDown(int iKeyCode)
{
	if (m_State == 5){
		//set name
		SetName(iKeyCode);
	}
	switch (iKeyCode)
	{
	case SDLK_ESCAPE:
		SetExitWithCode(0);
		break;
	case SDLK_SPACE:
		switch (m_State){
		case 0:
			break;
		case 5:
			for (int i = 0; i < text_pointer; i++){
				player_name[i] = default_name[i];
			}
			player_name[text_pointer] = '\0';
			printf("hi %s\n", player_name);
			m_State = 6;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case 6:
			m_State = 7;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case 7:
			start_time = GetTime();
			m_State = 1;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case 1:
			m_State = 2;
			pause_time = GetTime();
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case 2:
			restart_time = GetTime();
			m_State = 1;
			IncreaseTimeOffset(pause_time - restart_time);
			break;
		case 3:
			m_State = 8;
			SetupBackgroundBuffer();
			Redraw(true);
			showScores();
			break;
		case 4:
			m_State = 8;
			SetupBackgroundBuffer();
			Redraw(true);
			showScores();
			break;
		case 8:
			reset();
			break;
		}
	default:
		break;
	}
}


void GoldMinerEngine::SetName(int iKeyCode)
{
	char ch[2];
	int char_width = 20;
	int temp = name_init;
	if (text_pointer == -1){
		text_pointer++;
		SetupBackgroundBuffer();
		Redraw(true);
	}
	//if someone delete the character
	if (iKeyCode == SDLK_BACKSPACE && text_pointer > 0){
		SetupBackgroundBuffer();
		text_pointer--;
		for (int i = 0; i < text_pointer; i++){
			sprintf(ch, "%c", default_name[i]);
			DrawBackgroundString(temp, name_y, ch, 0xff0000, NULL);
			temp += char_width;
		}
		name_x -= char_width;
		Redraw(true);
	}
	//input a character
	if (iKeyCode != SDLK_SPACE && iKeyCode != SDLK_BACKSPACE){
		default_name[text_pointer] = iKeyCode;
		sprintf(ch, "%c", iKeyCode);
		DrawBackgroundString(name_x, name_y, ch, 0xff0000, NULL);
		text_pointer++;
		name_x += char_width;
		Redraw(true);
	}
}


void GoldMinerEngine::reset()
{
	level = 1;
	m_State = 0;
	obj_num = 10;
	score = 0;
	remaining_time = TIMELIMIT;
	start_time = TIMELIMIT;
	restart_time = 0;
	diamond_num = 2;
	gold_num = 3;
	stone_num = 5;
	gs_num = obj_num - diamond_num;
	InitialiseObjects();
	SetupBackgroundBuffer();
	Redraw(true);
}


void GoldMinerEngine::showScores()
{
}

//override GameAction();
void GoldMinerEngine::GameAction()
{
	if (!IsTimeToAct()){
		return;
	}
	SetTimeOffset(25);
	switch (m_State)
	{
	case 1:
		changeBackground();
		if (remaining_time == 0){
			
		}
	default:
		break;
	}
}

//check which states to go when time is up
void GoldMinerEngine::checkStatus()
{
	//if (score >= goals[level - 1] && level < 10){
	//	//update level
	//}
	//else if (score >= goals[level - 1] && level == 10){
	//	m_State = 3;
	//	SetupBackgroundBuffer();
	//	Redraw(true);

	//}
	if (score >= goals[level - 1]){
		m_State = 3;
		SetupBackgroundBuffer();
		Redraw(true);
	}
	else{
		m_State = 4;
		SetupBackgroundBuffer();
		Redraw(true);

	}
}
