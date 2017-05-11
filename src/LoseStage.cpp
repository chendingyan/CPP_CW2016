#include "LoseStage.h"
#include "ScoreStage.h"

LoseStage::LoseStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
}


LoseStage::~LoseStage()
{
}


void LoseStage::SetBackground()
{
	engine->FillBackground(0x000000);
	sprintf(buf, "Game End");
	engine->DrawBackgroundString(120, 200, buf, 0xf4901e, NULL);
	sprintf(buf, "Score: %d  Level: %d", engine->score, engine->level);
	engine->DrawBackgroundString(120, 250, buf, 0xf4901e, NULL);
	sprintf(buf, "Well done %s", engine->name);
	engine->DrawBackgroundString(120, 300, buf, 0xf4901e, NULL);
	sprintf(buf, "Press space");
	engine->DrawBackgroundString(120, 460, buf, 0xffffff, NULL);
	engine->DrawBackgroundThickLine(0, 500, 800, 500, 0xffffff, 3);
}


void LoseStage::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		engine->setState(new ScoreStage(engine));
		engine->SetupBackgroundBuffer();
		engine->Redraw(true);
		engine->DisplayResults();
	}
	
}
