#pragma once
#include <stdio.h>
#include <fstream>
#include <vector>
#include <fstream>
#include "Point.h"
#define NUM_PATH 500
#define POPSIZE 20      //number of path
using namespace std;
class FindPathAlgorithm
{
public:
	FindPathAlgorithm();
	~FindPathAlgorithm();

private:
	unsigned seed;
	double pcross, pmutation;//the possibility of crossover and mutation
	int MaxEpoc;//the max number of evolution
	int rate; //the mutation rate
	string file;
	int genmax;
	int num_cities;
	vector<Point> cities;
	double **point_distance;
	int* group[POPSIZE];   //population
	int* BestRooting;
	double fitness[POPSIZE];
	double BestFitness;
	double BestValue;
};

