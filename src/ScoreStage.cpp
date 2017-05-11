#include "ScoreStage.h"


ScoreStage::ScoreStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
}


ScoreStage::~ScoreStage()
{
}


void ScoreStage::SetBackground()
{
	engine->score_bg.RenderImage(engine->GetBackground(),
		0, 0,
		0, 0,
		engine->score_bg.GetWidth(), engine->score_bg.GetHeight());
}


void ScoreStage::DrawStringsOnTheTop()
{
	char buff[128];
	sprintf(buff, "SCORES");
	engine->DrawScreenString(50, 20, buff, 0x000000, NULL);
}


void ScoreStage::KeyPressed(int iKeyCode)
{
	engine->ResetAll();
}
