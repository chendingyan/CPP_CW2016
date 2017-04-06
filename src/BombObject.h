#pragma once
#include "TileManager.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"

class BombObject :
	public TileManager
{
public:
	BombObject();
	~BombObject();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
private:
	ImageData bomb;
};

