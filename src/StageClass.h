#pragma once
#include "templates.h"
#include "header.h"
#include "GoldMinerEngine.h"
#include "JPGImage.h"
class GoldMinerEngine;
class ImageData;

class StageClass
{
public:
	StageClass(GoldMinerEngine *engine);
	~StageClass();
	virtual void SetBackground();
	GoldMinerEngine * engine;
};

