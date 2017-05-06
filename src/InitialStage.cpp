#include "InitialStage.h"


InitialStage::InitialStage(GoldMinerEngine *engine)
	:StageClass(engine)
{
	
	bg_img.LoadImage("./img/background-ppt.png");
	start_button.LoadImage("./img/start.jpg");
	score_button.LoadImage("./img/scores.jpg");
}


InitialStage::~InitialStage()
{
}

void InitialStage::SetBackground()
{
	bg_img.RenderImage( engine->GetBackground(),
		0, 0,
		0, 0,
		bg_img.GetWidth(), bg_img.GetHeight());
	start_button.RenderImage(engine->GetBackground(),
		0, 0,
		80, 470,
		start_button.GetWidth(), start_button.GetHeight());
	score_button.RenderImage(engine->GetBackground(),
		0, 0,
		420, 470,
		score_button.GetWidth(), score_button.GetHeight());
}
