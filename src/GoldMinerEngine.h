#pragma once
#include "BaseEngine.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
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
private:
	ImageData bg_img, start_button, instruction_img;
public:
	void DrawStrings();
};

