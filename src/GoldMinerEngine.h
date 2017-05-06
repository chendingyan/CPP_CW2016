#pragma once
#include "BaseEngine.h"
#include "BombObject.h"
#include "TileManager.h"
#include "JPGImage.h"
#include <string>
#include <cctype>
#define HOOKID 0
#define TOTAL_LEVEL 10
#define ROUND_TIME 40
#define GBK_Y 150
class GoldMinerEngine :
	public BaseEngine
{
public:
	GoldMinerEngine();
	~GoldMinerEngine();

	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void set_up(int stone_num, int gold_num, int diamond_num);
	void DrawStringsOnTop();
	// Get a reference to the current tile manager
	BombObject& GetTileManager() { return stone_bomber; }

	// States 
	enum State { stateInit, stateMain, statePaused, stateWin, stateIntro, stateGetName, stateGoal, stateLose, stateScore };
	int m_iPauseStarted;
	int score;
	void DrawObjects();
	void UndrawObjects();
	void KeyDown(int iKeyCode);
	void GameAction();
	void MouseDown(int iButton, int iX, int iY);
	void GetName(int iKeyCode);
	void OneRoundEnd();
	void UnDrawStrings();
	void StoreResults();
	void DisplayResults();
	int gs_num;
	int tilex;
	int tiley;
	int level;
	void GoldMinerEngine::ResetStableObjects(int obj_num, int diamond_num, int gold_num);
	void InitialiseLevelObjects(int pig_num, int map_mode);
	const static int goals[TOTAL_LEVEL];
	int obj_num;
	int tile_width;
	void UniformDistributed();
	int rst_time;
	State m_state;
	int ini_time;
	int rem_time;
	int name_x;
	int name_y;
	int name_inix;
	BombObject stone_bomber;
	int char_counter;
	int gold_num;
	int stone_num;
	int diamond_num;
private:
	void ResetAll();
	int l_tick;
	ImageData bg_img, start_button, score_button, instruction_img, bg1, bg2, bg3, bg4, score_bg;
	char name[50];
	void BackgroundAnimation(); 
	void RenderImgForBA(ImageData& image);
	void SetNextLevel();
};




