#pragma once
#include "DisplayableObject.h"
#include "header.h"
#include "templates.h"
#include "GoldMinerEngine.h"
#include <string>
using namespace std;

class HookObject :
	public DisplayableObject
{
public:
	HookObject(GoldMinerEngine * pEngine, int angle, int len1, int len2, string direction, int rotatespeed);
	~HookObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void Hook(int angle);
	void Rotate();
	void Pull();
	void Back();// 0-nothing, 1-gold, 2-stone...
	void changeSpeed(int type, int size);
	int m_angle;
	int m_mode; // 0-rotate/1-pull/2-nothingback/3-getback
	int m_PosX;
	int m_PosY;
	int m_len1;
	int m_len2;
	string m_direction; // "left" or "right"
	int rotate_speed;
	double m_speedX;
	double m_speedY;
	double initial_speedX;
	double initial_speedY;
	double iCurrentScreenX, iCurrentScreenY;
	double static_angle;
	bool isHook;
	double x1, x2, x3, x4, y1, y2, y3, y4;
	int getLen1();
	int getLen2();
	double speedParameter;
	
};

