#include "SetNameStage.h"
#include "IntroStage.h"

SetNameStage::SetNameStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
}


SetNameStage::~SetNameStage()
{
}


void SetNameStage::SetBackground()
{
	engine->bg_img.RenderImage(engine->GetBackground(),
		0, 0,
		0, 0,
		engine->bg_img.GetWidth(), engine->bg_img.GetHeight());
	engine->DrawBackgroundString(240, 470, "Enter Your Name(Press space to go)", 0xffffff, NULL);
	if (engine->char_counter == -1){
		engine->DrawBackgroundString(engine->name_inix, engine->name_y, engine->getName(), 0xf4901e, NULL);
	}
}


void SetNameStage::KeyPressed(int iKeyCode)
{
	engine->SetName(iKeyCode);
	if (iKeyCode == SDLK_SPACE){
		for (int i = 0; i < engine->char_counter; i++){
			char * name = engine->getName();
			engine->name[i] = name[i];
		}
		engine->name[engine->char_counter] = '\0';
		//Go to state main
		engine->setState(new IntroStage(engine));
		// Force redraw of background
		engine->SetupBackgroundBuffer();
		// Redraw the whole screen now
		engine->Redraw(true);
	}
}
