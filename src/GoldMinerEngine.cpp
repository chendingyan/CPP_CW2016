#include "GoldMinerEngine.h"
#include "HookObject.h"
#include "HookableObject.h"
#include "GoldObject.h"
#include "StoneObject.h"
#include "DiamondObject.h"
#include "PigObject.h"
#include "header.h"
#include "templates.h"
using namespace std;

GoldMinerEngine::GoldMinerEngine()
	: m_State(0),
	score(0),
	Num_Of_Objects(0)
{
	bg_img.LoadImage("./img/background.jpg");
	start_button.LoadImage("./img/start.png");
	instruction_img.LoadImage("./img/instruction.jpg");
}


GoldMinerEngine::~GoldMinerEngine()
{
}


void GoldMinerEngine::SetupBackgroundBuffer()
{
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
			300, 300,
			start_button.GetWidth(), start_button.GetHeight());
		break;
		//playing
	case 1:
		//DrawStrings();
		FillBackground(0x8B4513);
		
		break;
		//pause
	case 2:
		break;
		//win
	case 3:
		break;
		//lose
	case 4:
		break;
		//set name
	case 5:
		break;
		//instruction
	case 6:
		instruction_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			instruction_img.GetWidth(), instruction_img.GetHeight());
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
		if (iX > 300 && iX < 500 && iY > 300 && iY < 400){
			m_State = 1;
			SetupBackgroundBuffer();
			Redraw(true);
		}
	case 1:
		InitialiseObjects();
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


void GoldMinerEngine::DrawStrings()
{
	UnDrawStrings();
	char buf[128];
	printf("score = %d\n", score);
	sprintf(buf, "Score: %d", score);
	DrawScreenString(600, 50, buf, 0xff00ff, NULL);
}
