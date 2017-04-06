#pragma once
#include "BaseEngine.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "BombObject.h"
class GoldMinerEngine :
	public BaseEngine
{
public:
	GoldMinerEngine();
	~GoldMinerEngine();
	void SetupBackgroundBuffer();
	void MouseDown(int iButton, int iX, int iY);
	int InitialiseObjects();
	int m_State; //Reveals the state of the game: 0-initial/1-playing/2-pause/3-win/4-lose/5-setname
	int score;
	int Num_Of_Objects;
	int starttime;
private:
	ImageData bg_img, start_button, instruction_img, bg1, bg2, bg3, bg4, score_button, score_bg;
public:
	void DrawStrings();
	void changeBackground();
	void RenderImageHelper(ImageData& image);
	int level;
	const int goals[10] = { 200, 400, 700, 900, 1000, 1200, 1500, 3000, 3200, 3300 };
	BombObject bomb;
	int bombPosX, bombPosY;
	int tile_width;
	void InitialisePosition(int gold_num, int stone_num, int diamond_num);
	int gold_num;
	int stone_num;
	int diamond_num;
	void DrawStringOnTop();
	int levelTime;
};

