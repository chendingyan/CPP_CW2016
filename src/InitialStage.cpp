#include "InitialStage.h"
#include "SetNameStage.h"
#include "ScoreStage.h"
InitialStage::InitialStage(GoldMinerEngine *engine)
	:StageClass(engine)
{
	
	
}


InitialStage::~InitialStage()
{
}

void InitialStage::SetBackground()
{
	engine->bg_img.RenderImage( engine->GetBackground(),
		0, 0,
		0, 0,
		engine->bg_img.GetWidth(), engine->bg_img.GetHeight());
	engine->start_button.RenderImage(engine->GetBackground(),
		0, 0,
		80, 470,
		engine->start_button.GetWidth(), engine->start_button.GetHeight());
	engine->score_button.RenderImage(engine->GetBackground(),
		0, 0,
		420, 470,
		engine->score_button.GetWidth(), engine->score_button.GetHeight());
}


void InitialStage::MousePressed(int iButton, int iX, int iY)
{
	// start game 
	if (iX>80 && iX< 330 && iY > 470 && iY < 557){
		engine->setState(new SetNameStage(engine));
		engine->SetupBackgroundBuffer();
		engine->Redraw(true);
	}
	// display the score
	if (iX>420 && iX < 708 && iY> 470 && iY < 557){
		engine->setState(new ScoreStage(engine));
		engine->SetupBackgroundBuffer();
		engine->Redraw(true);
		engine->DisplayResults();
	}
}
