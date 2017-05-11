#include "WinStage.h"
#include "ScoreStage.h"

WinStage::WinStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
}


WinStage::~WinStage()
{
}


void WinStage::SetBackground()
{
	engine->FillBackground(0x000000);
	sprintf(buf, "You Passed all! :)");
	engine->DrawBackgroundString(120, 200, buf, 0xf4901e, NULL);
	sprintf(buf, "Score: %d  Level: %d", engine->score, engine->level);
	engine->DrawBackgroundString(120, 250, buf, 0xf4901e, NULL);
	sprintf(buf, "Well done %s", engine->name);
	engine->DrawBackgroundString(120, 300, buf, 0xf4901e, NULL);
	sprintf(buf, "Press space");
	engine->DrawBackgroundString(120, 460, buf, 0xffffff, NULL);
	engine->DrawBackgroundThickLine(0, 500, 800, 500, 0xffffff, 3);
}


void WinStage::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		engine->setState(new ScoreStage(engine));
		engine->SetupBackgroundBuffer();
		engine->Redraw(true);
		engine->DisplayResults();
	}
}
