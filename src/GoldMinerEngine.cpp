
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
#include "InitialStage.h"
#include "MainStage.h"
#include "PauseStage.h"
#include "WinStage.h"
#include "IntroStage.h"
#include "SetNameStage.h"
#include "GoalStage.h"
#include "LoseStage.h"
#include "ScoreStage.h"
using namespace std;
// goals for each level (10 in total)
const int GoldMinerEngine::goals[] = { 200, 400, 800, 1000, 1200, 1500, 1800, 2200, 2800, 3000 };
char default_name[50] = "Name";
GoldMinerEngine::GoldMinerEngine()
	: BaseEngine(6)
	, obj_num(10) //object number
	, level(1)
	, score(0)
	, ini_time(ROUND_TIME) // game time
	, rem_time(ROUND_TIME) // remaining time
	, rst_time(0)
	, diamond_num(2)
	, gold_num(3)
	, stone_num(5)
	, l_tick(0)	
	, char_counter(-1)// used in set name
	, name_x(300)
	, name_inix(320)
	, name_y(520)
	, stage(new InitialStage(this))
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
	
	gs_num = obj_num - diamond_num; //gs_num is the sum of gold and stone number
	tilex = 10 * (rand() % 50 + 10);//bombPosX;
	tiley = 10 * (rand() % 20 + 20);
	tile_width = 60;
}


GoldMinerEngine::~GoldMinerEngine()
{
}


void GoldMinerEngine::SetupBackgroundBuffer(void){
	stage->SetBackground();
}


int GoldMinerEngine::InitialiseObjects(){
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	
	CreateObjectArray(100);
	/*tilex = 0;
	tiley = 150;
	tile_width = 60;*/
	int tx = tilex + (1.5*tile_width);
	int ty = tiley + (1.5*tile_width);
	printf("tx = %d, ty = %d", tx, ty);
	StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 10, 5, "right", 1, 0));
	int randomx = 70 * rand() % 10;
	int randomy = 50 * (rand() % 4 + 6);
	InitialisePosition(stone_num, gold_num,diamond_num);
	StoreObjectInArray(16, new PigObject(this, 49, 48, randomx, randomy, 1));
	randomx = 50 * (rand() % 12);
	randomy = 50 * (rand() % 3 + 6);
	StoreObjectInArray(17, new PigObject(this, 49, 48, randomx, randomy, 1));
	
	randomx = 70 * rand() % 10;
	randomy = 50 * (rand() % 4 + 6);
	//StoreObjectInArray(30, new BadPigObject(this, 40, 35, randomx+100, randomy, 1));
	return 0;
}

/*Initialize the position of all the stable objects
Uniform distribution algorithm
*/
void GoldMinerEngine::InitialisePosition(int stone_num, int gold_num, int diamond_num){
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


	//Use helpx and helpy array to store all the coordinates of object
	//To make it more distribution, we random number in a uniform distribution way

	
	int randwidth = 600;
	while (randwidth > 0 && item_number < obj_num){
		tempx = rand() % (randwidth+100);
		tempy = 10 * (rand() % 30 + 25);
		while (tempx < randwidth){
			tempx = rand() % (randwidth+100);
			tempy = 10 * (rand() % 30 + 25);
		}

		helpx[item_number] = tempx;
		helpy[item_number] = tempy;
		item_number++;
		randwidth -= (randwidth / obj_num);
	}
	/* Make the disribution more uniform*/
	for (int i = 0; i < obj_num; i++){
		x = (double)(cos(angle*M_PI / 180) * 40);
		y = (double)(sin(angle* M_PI / 180) * 40);
		xlist[i] = (int)(helpx[i]);
		if (helpy[i] > 250 && helpy[i] < 500){
			ylist[i] = (int)(y + helpy[i]);
		}
		else{
			ylist[i] = (int)(helpy[i]);
		}
		
		angle += (int)(360 /obj_num);
	}
	
	// add all the stable objects in
	if (level != 1){
		for (index = 1; index <= stone_num; index++){
			StoreObjectInArray(index, new StoneObject(this, 50, 50, xlist[index], ylist[index]));   // stone
		}

		for (index; index <= gs_num - 2; index++){
			StoreObjectInArray(index, new GoldObject(this, 50, 50, xlist[index], ylist[index]));   // gold
		}

		for (index; index <= gs_num; index++){
			StoreObjectInArray(index, new GoldObject(this, 60, 61, xlist[index], ylist[index])); //big-gold
		}

		for (index; index <= obj_num; index++){
			StoreObjectInArray(index, new DiamondObject(this, 67, 50, xlist[index], ylist[index]));   // diamond
		}
	}
	else{
		StoreObjectInArray(1, new StoneObject(this, 50, 50, 30, 500));
		StoreObjectInArray(2, new StoneObject(this, 50, 50, 320, 180));
		StoreObjectInArray(3, new StoneObject(this, 50, 50, 670, 300));
		StoreObjectInArray(4, new StoneObject(this, 50, 50, 100, 190));
		StoreObjectInArray(5, new StoneObject(this, 50, 50, 310, 470));
		StoreObjectInArray(6, new GoldObject(this, 53, 47, 500, 500));
		StoreObjectInArray(7, new GoldObject(this, 50, 50, 40, 200));
		StoreObjectInArray(8, new GoldObject(this, 60, 61, 100, 290));
		StoreObjectInArray(9, new DiamondObject(this, 76, 50, 160, 320));
		StoreObjectInArray(10, new DiamondObject(this, 76, 50, 400, 220));
	}
	
}

void GoldMinerEngine::MouseDown(int iButton, int iX, int iY){
	stage->MousePressed(iButton, iX, iY);
}

void GoldMinerEngine::DrawStringsOnTop(){
	stage->DrawStringsOnTheTop();
}


/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void GoldMinerEngine::KeyDown(int iKeyCode)
{
	stage->KeyPressed(iKeyCode);
}


/* Overridden GameAction to ensure that objects use the modified time */
void GoldMinerEngine::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;

	// Don't act for another 1 tick - this is a difference from the base class
	SetTimeToAct(25);

	stage->Run();
}


// display background animation, depending on the time
void GoldMinerEngine::BackgroundAnimation(){
	int diff = m_iTick - l_tick;
	if (diff <= 3000){
		RenderImageHelper(bg1);
	}
	else if (diff> 3000 && diff <= 4000){
		RenderImageHelper(bg2);
	}
	else if (diff > 4000 && diff <= 6500){
		RenderImageHelper(bg3);
	}
	else if (diff > 6500 && diff <= 8000){
		RenderImageHelper(bg4);
	}
	else{
		l_tick = GetTime();
	}
}

// render the images for backgroung animation
void GoldMinerEngine::RenderImageHelper(ImageData& image){
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
			stage = new WinStage(this);
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			StoreResults();
		}
	}
	else{  // game end
		stage = new LoseStage(this);
		SetupBackgroundBuffer();
		Redraw(true);
		StoreResults();
	}
}

void GoldMinerEngine::SetNextLevel(){
	// reset to next level
	level++;
	int randomx, randomy;
	int tx, ty;
	switch (level)
	{
	case 2:
		//ResetStableObjects(10, 10, 0);  // three para are obs_num, diamond_num and gold_num
		//InitialiseLevelObjects(1, 0);
		this->obj_num = 10;
		this->gold_num = 0;
		this->diamond_num = 10;
		this->stone_num = obj_num - gold_num - diamond_num;
		this->gs_num = obj_num - diamond_num;
		DrawableObjectsChanged();
		CreateObjectArray(100);
		tx = tilex + (1.5*tile_width);
		ty = tiley + (1.5*tile_width);
		StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 10, 5, "right", 1,1));
		StoreObjectInArray(1, new DiamondObject(this, 76, 50, 40, 200));
		StoreObjectInArray(2, new DiamondObject(this, 76, 50, 100, 290));
		StoreObjectInArray(3, new DiamondObject(this, 76, 50, 160, 320));
		StoreObjectInArray(4, new DiamondObject(this, 76, 50, 400, 220));
		StoreObjectInArray(5, new DiamondObject(this, 76, 50, 470, 240));
		StoreObjectInArray(6, new DiamondObject(this, 76, 50, 570, 420));
		StoreObjectInArray(7, new DiamondObject(this, 76, 50, 550, 200));
		StoreObjectInArray(50, new BadPigObject(this, 40, 35, 400, 300, 1));
		break;
	case 3:
		this->obj_num = 11;
		this->gold_num = 3;
		this->diamond_num = 5;
		this->stone_num = obj_num - gold_num - diamond_num;
		this->gs_num = obj_num - diamond_num;
		DrawableObjectsChanged();
		CreateObjectArray(100);
		tx = tilex + (1.5*tile_width);
		ty = tiley + (1.5*tile_width);
		StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 10, 5, "right", 1, 1));
		StoreObjectInArray(1, new StoneObject(this, 50, 50, 30, 500));
		StoreObjectInArray(2, new StoneObject(this, 50, 50, 320, 180));
		StoreObjectInArray(3, new StoneObject(this, 50, 50, 670, 300));
		StoreObjectInArray(4, new GoldObject(this, 50, 50, 100, 190));
		StoreObjectInArray(5, new GoldObject(this, 50, 50, 310, 470));
		StoreObjectInArray(6, new GoldObject(this, 53, 47, 500, 500));
		StoreObjectInArray(7, new DiamondObject(this, 76, 50, 40, 200));
		StoreObjectInArray(8, new DiamondObject(this, 76, 50, 100, 290));
		StoreObjectInArray(9, new DiamondObject(this, 76, 50, 160, 320));
		StoreObjectInArray(10, new DiamondObject(this, 76, 50, 400, 220));
		StoreObjectInArray(11, new DiamondObject(this, 76, 50, 470, 240));
		StoreObjectInArray(50, new BadPigObject(this, 40, 35, 400, 300, 1));
		break;
	case 4:
		ResetStableObjects(13, 5, 4);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(2, 0);
		break;
	case 5:
		obj_num = 20;
		gs_num = 0;
		InitialiseLevelObjects(30, 1); // PIG MODE
		break;
	case 6:
		ResetStableObjects(11, 4, 4);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(2, 0);
		break;
	case 7:
		ResetStableObjects(9, 4, 5);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		tx = 50 * (rand() % 12);
		ty = 50 * (rand() % 5 + 5);
		//StoreObjectInArray(50, new BadPigObject(this, 40, 35, randomx + 100, randomy, 1));
		break;
	case 8:
		ResetStableObjects(8, 5, 3);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
		tx = 50 * (rand() % 12);
		ty = 50 * (rand() % 5 + 5);
		//StoreObjectInArray(50, new BadPigObject(this, 40, 35, randomx + 100, randomy, 1));
	case 9:
		ResetStableObjects(14, 0, 12);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
		tx = 50 * (rand() % 12);
		ty = 50 * (rand() % 5 + 5);
		//StoreObjectInArray(50, new BadPigObject(this, 40, 35, randomx + 100, randomy, 1));
	case 10:
		ResetStableObjects(12, 2, 3);  // three para are obs_num, diamond_num and gold_num
		InitialiseLevelObjects(0, 0);
		break;
	default:
		break;
	}
	rem_time = ROUND_TIME;
	rst_time = 0;
	stage = new GoalStage(this);
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
	int randomx;
	int randomy;
	if (map_mode == 0){
		InitialisePosition(stone_num, gold_num, diamond_num);
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
	
	StoreObjectInArray(HOOKID, new HookObject(this, tx, ty, 30, 10, 5, "right", 1,0));
	

}


// reset all back to the initial value 
void GoldMinerEngine::ResetAll(){
	printf("Reset\n");
	obj_num = 10;
	level = 1;
	stage = new GoalStage(this);
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
void GoldMinerEngine::SetName(int iKeyCode){
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
		
		char_counter++;
		name_x += font_width;
		Redraw(true);
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
	stage->UnDrawStrings();
}


void GoldMinerEngine::UndrawObjects()
{
	stage->UndrawObjects();
}

void GoldMinerEngine::DrawObjects()
{
	stage->DrawObjects();
}

void GoldMinerEngine::setState(StageClass * iSC)
{
	this->stage = iSC;
}


int GoldMinerEngine::getiTick()
{
	return m_iTick;
}


char * GoldMinerEngine::getName()
{
	return default_name;
}


StageClass * GoldMinerEngine::getStage()
{
	return stage;
}

//
//BombObject& GoldMinerEngine::GetTileManager()
//{
//	//TODO: insert return statement here
//	return stage->GetTileManager();
//}
