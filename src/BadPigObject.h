#pragma once
#include "DynamicObject.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <fstream>
#include "Point.h"
#define NUM_PATH 500
#define POPSIZE 20      //number of path
#define MAXVALUE 1000000   //路径越短越好
#define N 200 //需要根据实际求得的路径值修正
class BadPigObject :
	public DynamicObject
{
public:
	BadPigObject(GoldMinerEngine *pEngine, int sizeX, int sizeY, int posX, int posY, int speed);
	~BadPigObject();
	ImageData prl1, prr1, prl2, prr2, prl3, prr3;//stands for pig_run_left and pig_run_right
	GoldMinerEngine * m_pEngine;
	int updown;
	int diamond_loc[2];
	int starttime;
	int score;
private:
	int direction;
	int num_of_diamond;
	int diamond_help;
	int offset;
	int min;
	int num_diamond;
	bool isfirst = false;
public:
	void Draw();
	void DoUpdate(int iCurrentTime);
	void DiamondSearchAlgorithm();
	int readDiamondPos();
private:
	unsigned seed;
	double pcross, pmutation;//the possibility of crossover and mutation
	int MaxEpoc;//the max number of evolution
	int rate; //the mutation rate
	string file;
	int genmax;
	
	vector<Point> diamonds;
	double **point_distance;
	int* group[POPSIZE];   //population
	int* BestRooting;
	double fitness[POPSIZE];
	double BestFitness;
	double BestValue;
public:
	void initDistMatrix();
	bool check(int pop, int num, int k);
	void InitColony();
	void CalFitness();
	void Select();
	void OXCross(int i);
	void Cross(double pc);
	void OnCVariation(int i);
	void Mutation(double pm);
	void OutPut();
	void work();
};

