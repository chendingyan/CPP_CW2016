#include "StageClass.h"


StageClass::StageClass(GoldMinerEngine *engine)
	: engine(engine)
	, label(0)
{
	
}


StageClass::~StageClass()
{
}




void StageClass::SetBackground()
{
}


void StageClass::MousePressed(int iButton, int iX, int iY)
{

}


void StageClass::DrawStringsOnTheTop()
{
}


void StageClass::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE){
		engine->SetExitWithCode(0);
	}
}


void StageClass::Run()
{
}


void StageClass::UnDrawStrings()
{
	engine->CopyBackgroundPixels(0, 0, engine->GetScreenWidth(), 100);
}


void StageClass::UndrawObjects()
{
}


void StageClass::DrawObjects()
{
}

//
//BombObject & StageClass::GetTileManager()
//{
//	//TODO: insert return statement here
//	return stone_bomber;
//}
