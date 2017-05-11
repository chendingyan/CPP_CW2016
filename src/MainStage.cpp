#include "MainStage.h"
#include "PauseStage.h"
#include "BombObject.h"
MainStage::MainStage(GoldMinerEngine * engine)
	:StageClass(engine)
{
	label = 1;
}


MainStage::~MainStage()
{
}


void MainStage::SetBackground()
{
	//engine->tilex = 10 * (rand() % 50 + 10);//bombPosX;
	//engine->tiley = 10 * (rand() % 20 + 20);
	/*engine->tilex = 0;
	engine->tiley = 150;
	engine->tile_width = 60;*/
	engine->FillBackground(0x854e1f);
	engine->bg1.RenderImageWithMask(engine->GetBackground(),
		0, 0,
		0, 0,
		engine->GetScreenWidth(), GBK_Y);
	
	if (engine->level != 2 || engine->level!=3){
		int bombTile[3][3] = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } };

		stone_bomber.SetSize(3, 3);
		// Set up the tiles
		for (int x = 0; x < 3; x++){
			for (int y = 0; y < 3; y++){
				stone_bomber.SetValue(x, y, bombTile[x][y]);
			}
		}
		// Specify the screen x,y of top left corner
		stone_bomber.SetBaseTilesPositionOnScreen(engine->tilex, engine->tiley);
		printf("x = %d, y = %d\n", engine->tilex, engine->tiley);
		// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
		// to the background of this screen
		stone_bomber.DrawAllTiles(engine, engine->GetBackground(), 0, 0, 2, 2);
	}
	
} 


void MainStage::DrawStringsOnTheTop()
{
	char buff[128];
	char buf[36];
	// display scores, goal, remaining game time and game level on the screen
	sprintf(buf, "Score: %d", engine->score);
	engine->DrawScreenString(600, 10, buf, 0x000000, NULL);
	sprintf(buf, "Goal: %d", engine->goals[engine->level - 1]);
	engine->DrawScreenString(600, 50, buf, 0xffffff, NULL);
	engine->rem_time =engine->ini_time - (int)(engine->getiTick() - engine->rst_time) / 1000;
	sprintf(buff, "Time: %d", engine->rem_time);
	engine->DrawScreenString(30, 50, buff, 0xffffff, NULL);
	sprintf(buff, "Level: %d", engine->level);
	engine->DrawScreenString(30, 10, buff, 0x000000, NULL);
}


void MainStage::KeyPressed(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		// Go to state paused
		engine->setState(new PauseStage(engine));
		// Work out what this does. 
		engine->m_iPauseStarted =engine->GetTime();
		// Force redraw of background
		engine->SetupBackgroundBuffer();
		// Redraw the whole screen now
		engine->Redraw(true);
	}
	
}


void MainStage::Run()
{
	engine->BackgroundAnimation();
	if (engine->rem_time == 0){
		engine->OneRoundEnd();
	}
	// Only tell objects to move when not paused etc
	engine->UpdateAllObjects(engine->GetModifiedTime());
}


void MainStage::UndrawObjects()
{
	engine->BaseEngine::UndrawObjects();
}


void MainStage::DrawObjects()
{
	engine->BaseEngine::DrawObjects();
}
