#include "IntroStage.h"
#include "GoalStage.h"

IntroStage::IntroStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
}


IntroStage::~IntroStage()
{
}


void IntroStage::SetBackground()
{
	engine->instruction_img.RenderImage(engine->GetBackground(),
		0, 0,
		0, 0,
		engine->instruction_img.GetWidth(), engine->instruction_img.GetHeight());;
}


void IntroStage::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		engine->setState(new GoalStage(engine));
		engine->SetupBackgroundBuffer();
		engine->Redraw(true);
	}
	
}
