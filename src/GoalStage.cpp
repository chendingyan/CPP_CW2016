#include "GoalStage.h"
#include "MainStage.h"

GoalStage::GoalStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
}


GoalStage::~GoalStage()
{
}


void GoalStage::SetBackground()
{
	engine->FillBackground(0x000000);
	engine->score_bg.RenderImage(engine->GetBackground(), 0, 0, 0, 0, engine->score_bg.GetWidth(), engine->score_bg.GetHeight());
	engine->DrawBackgroundThickLine(0, 500, 800, 500, 0xffffff, 4);
	sprintf(buf, "Level %d", engine->level);
	engine->DrawBackgroundString(350, 360, buf, 0xf4901e, NULL);
	sprintf(buf, "Goal: %d", engine->goals[engine->level - 1]);
	engine->DrawBackgroundString(350, 410, buf, 0xf4901e, NULL);
	sprintf(buf, "Press space to start");
	engine->DrawBackgroundString(350, 460, buf, 0xffffff, NULL);
}


void GoalStage::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		engine->l_tick = engine->rst_time = engine->GetTime(); // get start/restart time
		engine->setState(new MainStage(engine));
		engine->SetupBackgroundBuffer();
		engine->Redraw(true);
	}
}
