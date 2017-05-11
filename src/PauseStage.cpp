#include "PauseStage.h"
#include "MainStage.h"

PauseStage::PauseStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
	label = 2;
}


PauseStage::~PauseStage()
{
}


void PauseStage::SetBackground()
{
}


void PauseStage::DrawStringsOnTheTop()
{
	char buff[128];
	engine->ini_time = engine->rem_time;  // record the time when game is paused
	sprintf(buff, "GAME STOP");
	engine->DrawScreenString(30, 10, buff, 0x000000, NULL);
}


void PauseStage::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		engine->rst_time = engine->GetTime();
		// Go to state main
		engine->setState(new MainStage(engine));
		// Work out what this does. It will be hard to notice any difference without these, but there is one. Hint: watch the positions and sizes of the objects
		engine->IncreaseTimeOffset(engine->m_iPauseStarted - engine->rst_time);
	}
}


void PauseStage::UnDrawStrings()
{
}


void PauseStage::UndrawObjects()
{
	engine->BaseEngine::UndrawObjects();
}


void PauseStage::DrawObjects()
{
	engine->BaseEngine::DrawObjects();
}
