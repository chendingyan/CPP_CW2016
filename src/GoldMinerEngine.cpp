#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"
#include "GoldObject.h"
#include "DiamondObject.h"
#include "StoneObject.h"
#include "HookObject.h"
#include "PigObject.h"
#include "BadPigObject.h"
#include <iostream>
#include <fstream> 
#include <list>
#include "JPGImage.h"

// goals for each level (10 in total)
const int GoldMinerEngine::goals[] = { 150, 200, 400, 600, 800, 1200, 1500, 2000, 2300, 3000 };
char default_name[50] = "Name";

using namespace std;
GoldMinerEngine::GoldMinerEngine()
	: BaseEngine(6)
	, obj_num(10) //object number
	, level(1)
	, score(0)
	, m_state(stateInit)
	, ini_time(ROUND_TIME) // game time
	, rem_time(ROUND_TIME) // remaining time
	, rst_time(0)
	, diamond_num(2)
	, gold_num(3)
	, stone_num(5)
	, l_tick(0)	
	, char_counter(-1)
{
	bg_img.LoadImage("./img/background-ppt.png");
	start_button.LoadImage("./img/start.jpg");
	score_button.LoadImage("./img/scores.jpg");
	instruction_img.LoadImage("./img/instruction.png");
	bg1.LoadImage("./img/bg1.png");
	bg2.LoadImage("./img/bg2.png");
	bg3.LoadImage("./img/bg3.png");
	bg4.LoadImage("./img/bg4.png");
	score_bg.LoadImage("./img/score_bk.jpg");

	name_x = name_inix = 350;
	name_y = 520;
   
	gs_num = obj_num - diamond_num; //gs_num is the sum of gold and stone number
	tilex = 10 * (rand() % 50 + 10);//bombPosX;
	tiley = 10 * (rand() % 20 + 20);
	tile_width = 60;
}


GoldMinerEngine::~GoldMinerEngine()
{
}


void GoldMinerEngine::SetupBackgroundBuffer(void){

	// set up bomb
	int bucket[3][3] = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } };
	char buf[20];
	switch (m_state)
	{
	case GoldMinerEngine::stateInit:
		bg_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			bg_img.GetWidth(), bg_img.GetHeight());
		start_button.RenderImage(this->GetBackground(),
			0, 0,
			80, 470,
			start_button.GetWidth(), start_button.GetHeight());
		score_button.RenderImage(this->GetBackground(),
			0, 0,
			420, 470,
			score_button.GetWidth(), score_button.GetHeight());
		break;
	case GoldMinerEngine::stateGetName:
		bg_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			bg_img.GetWidth(), bg_img.GetHeight());
		DrawBackgroundString(240, 470, "Enter Your Name", 0xffffff, NULL);
		if (char_counter == -1){
			DrawBackgroundString(name_inix, name_y, default_name, 0xf4901e, NULL);
		}
		break;
	case GoldMinerEngine::stateIntro:
		instruction_img.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			instruction_img.GetWidth(), instruction_img.GetHeight());;
		break;
	case GoldMinerEngine::stateMain:
		FillBackground(0x854e1f);
		bg1.RenderImageWithMask(this->GetBackground(),
			0, 0,
			0, 0,
			GetScreenWidth(), GBK_Y);
		stone_bomber.SetSize(3, 3);
		// Set up the tiles
		for (int x = 0; x < 3; x++){
			for (int y = 0; y < 3; y++){
				stone_bomber.SetValue(x, y, bucket[x][y]);
			}
		}
		// Specify the screen x,y of top left corner
		stone_bomber.SetBaseTilesPositionOnScreen(tilex, tiley);
		// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
		// to the background of this screen
		stone_bomber.DrawAllTiles(this, this->GetBackground(), 0, 0, 2, 2);
		//printf("get tile value %d\n", m_oTiles.GetValue(150,450));
		break;
	case GoldMinerEngine::statePaused:
		break;
	case GoldMinerEngine::stateGoal:
		FillBackground(0x000000);
		score_bg.RenderImage(this->GetBackground(), 0, 0, 0, 0, score_bg.GetWidth(), score_bg.GetHeight());
		DrawBackgroundThickLine(0, 500, 800, 500, 0xffffff, 4);
		sprintf(buf, "Level %d", level);
		DrawBackgroundString(350, 360, buf, 0xf4901e, NULL);
		sprintf(buf, "Goal: %d", goals[level-1]);
		DrawBackgroundString(350, 410, buf, 0xf4901e, NULL);
		sprintf(buf, "Press space to start");
		DrawBackgroundString(350, 460, buf, 0xffffff, NULL);
		break;
	case GoldMinerEngine::stateScore:
		score_bg.RenderImage(this->GetBackground(),
			0, 0,
			0, 0,
			score_bg.GetWidth(), score_bg.GetHeight());
		break;
	case GoldMinerEngine::stateWin:
		FillBackground(0x000000);
		sprintf(buf, "You Passed all! :)");
		DrawBackgroundString(120, 200, buf, 0xf4901e, NULL);
		sprintf(buf, "Score: %d  Level: %d", score, level);
		DrawBackgroundString(120, 250, buf, 0xf4901e, NULL);
		sprintf(buf, "Well done %s", name);
		DrawBackgroundString(120, 300, buf, 0xf4901e, NULL);
		sprintf(buf, "Press space");
		DrawBackgroundString(120, 460, buf, 0xffffff, NULL);
		DrawBackgroundThickLine(0, 500, 800, 500, 0xffffff, 3);
		break;
	case GoldMinerEngine::stateLose:
		FillBackground(0x000000);
		sprintf(buf, "Game End");
		DrawBackgroundString(120, 200, buf, 0xf4901e, NULL);
		sprintf(buf, "Score: %d  Level: %d", score, level);
		DrawBackgroundString(120, 250, buf, 0xf4901e, NULL);
		sprintf(buf, "Well done %s", name);
		DrawBackgroundString(120, 300, buf, 0xf4901e, NULL);
		sprintf(buf, "Press space");
		DrawBackgroundString(120, 460, buf, 0xffffff, NULL);
		DrawBackgroundThickLine(0, 500, 800, 500, 0xffffff,3);
		break;
	default:
		break;
	}
}


int GoldMinerEngine::InitialiseObjects(){
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	printf("!!!!\n");
	/*if (m_state == stateMain){
		
	}
		*/
	CreateObjectArray(100);
	//StoreObjectInArray(0, new GoldObject(this, 53, 47, 200, 200));
	//StoreObjectInArray(1, new GoldObject(this, 50, 50, 630, 310));
	//	StoreObjectInArray(2, new GoldObject(this, 93, 95, 400, 280));
	//	StoreObjectInArray(3, new StoneObject(this, 50, 50, 330, 250));
	//	StoreObjectInArray(4, new DiamondObject(this, 67, 50, 300, 400));
	//	StoreObjectInArray(5, new PigObject(this, 49, 48, 700, 170, 1));
	//	int tx = tilex + (1.5*tile_width);
	//	int ty = tiley + (1.5*tile_width);
	//	StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 20, 10, "right", 1));
	int tx = tilex + (1.5*tile_width);
	int ty = tiley + (1.5*tile_width);
	int randomx = 70 * rand() % 10;
	int randomy = 50 * (rand() % 4 + 6);
	set_up(stone_num, gold_num,diamond_num);
	StoreObjectInArray(16, new PigObject(this, 49, 48, randomx, randomy, 1));
	randomx = 50 * (rand() % 12);
	randomy = 50 * (rand() % 3 + 6);
	StoreObjectInArray(17, new PigObject(this, 49, 48, randomx, randomy, 1));
	StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 10, 5, "right", 1));
	randomx = 70 * rand() % 10;
	randomy = 50 * (rand() % 4 + 6);
	StoreObjectInArray(30, new BadPigObject(this, 40, 35, randomx, randomy, 1));
	return 0;
}

/*Initialize the position of all the stable objects
Uniform distribution algorithm
*/
void GoldMinerEngine::set_up(int stone_num, int gold_num, int diamond_num){
	int item_number = 0;
	int tempx;
	int tempy;
	int xdiff;
	int ydiff;
	int dis;
	int angle = 0;
	int index;
	double x;
	double y;


	// Choose a random point at the center of the screen as a start point
	int centerx = 10 * (rand() % 20 + 30);
	int centery = 10 * (rand() % 10 + 30);
	
	/* Use these to store random x and y location of the stable objects
		also add the start point into the array*/
	int xlist[20]; 
	int ylist[20];
	int helpx[20] = { centerx };
	int helpy[20] = { centery };

	/* Assume all the stable objects are in the biggest size (100*100, the stone size) and
	each object is a circle with radius of 100.Then generate obj_num-1 random numbers 
	(excluding the center point, which will also be a coordination for a stable object). 
	They are center of the circles which are disjoint from the current center circle*/

	while (item_number < obj_num - 1){
		tempx = 10 * (rand() % 50 + 10);
		tempy = 10 * (rand() % 10 + 30);
		xdiff = tempx - centerx;
		ydiff = tempy - centery;
		if ((xdiff*xdiff + ydiff*ydiff) >= 200 * 200){
			item_number++;
			helpx[item_number] = tempx;
			helpy[item_number] = tempy;
		}
	}
	
	/* Make the disribution more uniform*/
	for (int i = 0; i < obj_num; i++){
		x = (double)(cos(angle*M_PI / 180) * 100);
		y = (double)(sin(angle* M_PI / 180) * 100);
		xlist[i] = (int)(x + helpx[i]);
		ylist[i] = (int)(y + helpy[i]);
		angle += (int)(360 /obj_num);
	}
	
	// add all the stable objects in
	for (index = 1; index <= stone_num; index++){
		StoreObjectInArray(index, new StoneObject(this, 50, 50, xlist[index], ylist[index]));   // stone
	}

	for (index; index <= gs_num-2; index++){
		StoreObjectInArray(index, new GoldObject(this, 50, 50, xlist[index], ylist[index]));   // gold
	}

	for (index; index <= gs_num; index++){
		StoreObjectInArray(index, new GoldObject(this, 60, 61, xlist[index], ylist[index])); //big-gold
	}

	for (index; index <= obj_num; index++){
		StoreObjectInArray(index, new DiamondObject(this, 67, 50, xlist[index], ylist[index]));   // diamond
	}
}

void GoldMinerEngine::MouseDown(int iButton, int iX, int iY){
	switch (m_state)
	{
	case GoldMinerEngine::stateInit:	
		// start game 
		if (iX>80 && iX< 330 && iY > 470 && iY < 557){
				m_state = stateGetName;
				// Force redraw of background
				SetupBackgroundBuffer();
				// Redraw the whole screen now
				Redraw(true);
		}
		// display the score
		if (iX>420 && iX < 708 && iY> 470 && iY < 557){
			m_state = stateScore;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			DisplayResults();
		}
		break;
	
	default:
		break;
	}
	
}

void GoldMinerEngine::DrawStringsOnTop(){
	char buff[128];
	switch (m_state)
	{
	case GoldMinerEngine::stateInit:		
		break;
	case GoldMinerEngine::stateGetName:
		break;
	case GoldMinerEngine::stateMain:
		char buf[36];
		// display scores, goal, remaining game time and game level on the screen
		sprintf(buf, "Score: %d", score);
		DrawScreenString(600,10 , buf, 0x000000, NULL);
		sprintf(buf, "Goal: %d", goals[level-1]);
		DrawScreenString(600, 50, buf, 0xffffff, NULL);
		rem_time = ini_time - (int)(m_iTick - rst_time) / 1000; 
		sprintf(buff, "Time: %d",rem_time);
		DrawScreenString(30, 50, buff, 0xffffff, NULL);
		sprintf(buff, "Level: %d", level);
		DrawScreenString(30, 10, buff, 0x000000, NULL);
		break;
	case GoldMinerEngine::statePaused:
		ini_time = rem_time;  // record the time when game is paused
		sprintf(buff, "GAME STOP");
		DrawScreenString(30, 10, buff, 0x000000, NULL);
		break;
	case GoldMinerEngine::stateScore:
		sprintf(buff, "SCORES");
		DrawScreenString(50, 20, buff, 0x000000, NULL);
		break;
	case GoldMinerEngine::stateLose:
		break;
	}

}


/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void GoldMinerEngine::KeyDown(int iKeyCode)
{
	if (m_state == stateGetName){
		GetName(iKeyCode);
	}

	// NEW SWITCH on current state
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		switch (m_state)
		{
		case stateInit:
			break;
		case stateGetName:
			for (int i = 0; i < char_counter; i++){
				name[i] = default_name[i];
			}
			name[char_counter] = '\0';
			printf("Hi! %s\n", name);  // Print user name
			 //Go to state main
			m_state = stateIntro;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case stateIntro:
			m_state = stateGoal;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case stateGoal:
			l_tick = rst_time = GetTime(); // get start/restart time
			m_state = stateMain;
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		case stateMain:
			// Go to state paused
			m_state = statePaused;
			// Work out what this does. 
			m_iPauseStarted = GetTime();
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case statePaused:
			rst_time = GetTime();
			// Go to state main
			m_state = stateMain;
			// Work out what this does. It will be hard to notice any difference without these, but there is one. Hint: watch the positions and sizes of the objects
			IncreaseTimeOffset(m_iPauseStarted - rst_time);
			break;
		case stateLose:			
			m_state = stateScore;
			SetupBackgroundBuffer();
			Redraw(true);
			DisplayResults();
			break;
		case stateWin:
			m_state = stateScore;
			SetupBackgroundBuffer();
			Redraw(true);
			DisplayResults();
			break;
		case stateScore:
			ResetAll();
			break;
			
		} // End switch on current state
		break; // End of case SPACE
	}
}


/* Overridden GameAction to ensure that objects use the modified time */
void GoldMinerEngine::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;

	// Don't act for another 1 tick - this is a difference from the base class
	SetTimeToAct(25);

	// NEW SWITCH - different from the base class
	switch (m_state)
	{
	case stateInit:
	case statePaused:
		break;
	case stateGoal:
		break;
	case stateMain:  
		// display background animation
		BackgroundAnimation();	
		if (rem_time == 0){
			OneRoundEnd();
		}
		// Only tell objects to move when not paused etc
		UpdateAllObjects(GetModifiedTime());		
		break;
	}
}


// display background animation, depending on the time
void GoldMinerEngine::BackgroundAnimation(){
	int diff = m_iTick - l_tick;
	if (diff <= 3000){
		RenderImgForBA(bg1);
	}
	else if (diff> 3000 && diff <= 4000){
		RenderImgForBA(bg2);
	}
	else if (diff > 4000 && diff <= 6500){
		RenderImgForBA(bg3);
	}
	else if (diff > 6500 && diff <= 8000){
		RenderImgForBA(bg4);
	}
	else{
		l_tick = GetTime();
	}
}

// render the images for backgroung animation
void GoldMinerEngine::RenderImgForBA(ImageData& image){
	image.RenderImageWithMask(this->GetBackground(),
		0, 0,
		0, 0,
		GetScreenWidth(), GBK_Y);
	Redraw(true);
}



/* change and set to next level or show the result 
when one round ended*/
void GoldMinerEngine::OneRoundEnd(){
	if (score >= goals[level-1]){  // if score >= goal, go to next level
		if (level < TOTAL_LEVEL){  // if levels are not finished
			SetNextLevel();
		}
		else{  // if all the levels are finished
			m_state = stateWin;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			StoreResults();
		}
	}
	else{  // game end
		m_state = stateLose;
		SetupBackgroundBuffer();
		Redraw(true);
		StoreResults();
	}
}

void GoldMinerEngine::SetNextLevel(){
	// reset to next level
	level++;
	switch (level)
	{
	case 2:
		ResetStableObjects(12, 2, 4);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(1, 0);
		break;
	case 3:
		ResetStableObjects(15, 0, 5);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(3, 0);
		break;
	case 4:
		ResetStableObjects(13, 3, 4);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(2, 0);
		break;
	case 5:
		obj_num = 20;
		gs_num = 0;
		InitialiseLevelObjects(20, 1); // PIG MODE
		break;
	case 6:
		ResetStableObjects(11, 3, 4);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(2, 0);
		break;
	case 7:
		ResetStableObjects(11, 2, 5);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
	case 8:
		ResetStableObjects(8, 8, 3);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
	case 9:
		ResetStableObjects(14, 2, 12);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
	case 10:
		ResetStableObjects(12, 0, 3);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
	default:
		break;
	}
	rem_time = ROUND_TIME;
	rst_time = 0;
	m_state = stateGoal;
	SetupBackgroundBuffer();
	Redraw(true);
}


// change the number of the stable objects, be ready for the next level
void GoldMinerEngine::ResetStableObjects(int obj_num, int diamond_num, int gold_num){
	this->obj_num = obj_num;
	this->gold_num = gold_num;
	this->diamond_num = diamond_num;
	this->stone_num = obj_num - gold_num - diamond_num;
	this->gs_num = obj_num - diamond_num;
}


// reset objects (used for different level)
void GoldMinerEngine::InitialiseLevelObjects(int pig_num, int map_mode){
	DrawableObjectsChanged();
	CreateObjectArray(100);
	
	tilex = 10 * (rand() % 50 + 10);
	tiley = 10 * (rand() % 15 + 25);
	int tx = tilex + (1.5*tile_width);
	int ty = tiley + (1.5*tile_width);
	int randomx = 50*(rand() % 12);
	int randomy = 50*(rand() % 5 + 5);
	if (map_mode == 0){
		set_up(stone_num, gold_num, diamond_num);
		for (int i = 0; i < pig_num; i++){
			randomx = 50 * (rand() % 12);
			randomy = 50 * (rand() % 5 + 5);
			StoreObjectInArray(obj_num + 1 + i, new PigObject(this, 50, 50, randomx, randomy, 1));
		}
	}
	else if (map_mode == 1){ // all are pigs;
		for (int i = 0; i < pig_num; i++){
			randomx = 50 * (rand() % 12);
			randomy = 50 * (rand() % 5 + 5);
			StoreObjectInArray(i, new PigObject(this, 50, 50, randomx, randomy, 1));
		}
	}
	
	StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 10, 5, "right", 1));
	randomx = 50 * (rand() % 12);
	randomy = 50 * (rand() % 5 + 5);
	StoreObjectInArray(50, new BadPigObject(this, 40, 35, randomx, randomy, 1));

}


// reset all back to the initial value 
void GoldMinerEngine::ResetAll(){
	printf("Reset\n");
	obj_num = 10;
	level = 1;
	m_state = stateGoal;
	score = 0;
	rem_time = ROUND_TIME;
	ini_time = ROUND_TIME;
	rst_time = 0;
	diamond_num = 2;
	gold_num = 3;
	stone_num = 5;
	gs_num = obj_num - diamond_num;
	l_tick = 0;
	InitialiseObjects();
	SetupBackgroundBuffer();
	Redraw(true);
}


// for user name input
void GoldMinerEngine::GetName(int iKeyCode){
	char buf[2];
	int font_width = 20;
	int helper_x = name_inix;
	if (char_counter == -1){
		char_counter++;
		SetupBackgroundBuffer();
		Redraw(true);	
	}
	// handle the deletion
	if (char_counter > 0 && iKeyCode == SDLK_BACKSPACE){	
		SetupBackgroundBuffer();
		char_counter--;
		for (int i = 0; i < char_counter; i++){
			sprintf(buf, "%c", default_name[i]);
			DrawBackgroundString(helper_x, name_y, buf, 0xf4901e, NULL);
			helper_x += font_width;
		}			
		name_x -= font_width;
		Redraw(true);	
	}
	// handlet the input
	if (iKeyCode != SDLK_SPACE && iKeyCode != SDLK_BACKSPACE){
		default_name[char_counter] = iKeyCode;
		sprintf(buf, "%c", iKeyCode);	
		DrawBackgroundString(name_x, name_y, buf, 0xf4901e, NULL);
		Redraw(true);
		char_counter++;
		name_x += font_width;
	}
	
}



// store the game results
void GoldMinerEngine::StoreResults(){
	ofstream ofs;
	ofs.open("score.txt",ofstream::out | ofstream::app);
	if (char_counter == 0){
		ofs << "Unknown:   " << score << "-   " << level << endl;
	}
	else{
		ofs << string(name) <<":   "<< score << "-   " << level << endl;
	}
	ofs.close();
}


// for mark comparation
bool comp(const string& first, const string& second){
	size_t pos = first.find(":");
	size_t pos2 = first.find("-");
	int fs = stoi(first.substr(pos+1, pos2 - pos));
	pos = second.find(":");
	pos2 = second.find("-");
	int ss = stoi(second.substr(pos+1, pos2 - pos));
	return(fs > ss);
}


void GoldMinerEngine::DisplayResults(){

	list<string> score_list;
	list<string>::iterator it;

	// read all the info from the file and store into the score list
	string line;
	ifstream mfile;
	mfile.open("score.txt", ifstream::in);
	if (mfile.is_open()){
		while (getline(mfile, line)){
			score_list.push_back(line);
		}
		mfile.close();
	}
	else{
		cout << "Can not open the file" << endl;
	}

	// if there is no history
	if (score_list.empty()){
		return;
	}

	score_list.sort(comp);

	int start_x = 180;
	int start_y = 280;
	int i = 0;
	string data;   // raw data from the file
	string ddata;   // display data 
	char buff[8];
	ofstream ofs;
	ofs.open("score.txt", ofstream::out);
	
	// print out the results in a specific format
	DrawBackgroundString(180, 220,"TOP Ten (Name Score Level)", 0xfb8e18);
	for (it = score_list.begin(); it != score_list.end(); ++it){
		if (start_x < 600){
			if (start_y < 570){
				ddata = "";
				i++;
				sprintf(buff, "%d: ", i);
				DrawBackgroundString(start_x - 40, start_y, buff, 0xfb8e18);

				data = (*it);
				ofs << data << endl;  // output and store the top ten

				size_t posf = data.find(":");
				ddata += data.substr(0, posf);  // get the name
				size_t poss = data.find("-");
				ddata += data.substr(posf + 1, poss - posf - 1);  // get the score
				ddata += data.substr(poss + 1); // get the level
				DrawBackgroundString(start_x, start_y, ddata.c_str(), 0x000000);
				start_y += 60;
			}
			else{
				start_y = 280;
				start_x += 300;
			}
		}
		else{
			ofs.close();
			return;
		}
	}
}

void GoldMinerEngine::UnDrawStrings()
{
	if (m_state != statePaused)
		// Clear the top of the screen, since we about to draw text on it.
		CopyBackgroundPixels(0, 0, GetScreenWidth(), 100);
}


void GoldMinerEngine::UndrawObjects()
{
	if (m_state == stateMain || m_state == statePaused){ // Not in initialise state
		BaseEngine::UndrawObjects();
	}
}

void GoldMinerEngine::DrawObjects()
{
	if (m_state == stateMain || m_state == statePaused) // Not in initialise state
		BaseEngine::DrawObjects();
}