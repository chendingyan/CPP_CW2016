#include "Point.h"


Point::Point(int id = 0, int x=0, int y=0)
	:id(id), xPos(x), yPos(y)
{
}


Point::~Point()
{
}


int Point::getx()
{
	return xPos;
}


int Point::gety()
{
	return yPos;
}


int Point::getid()
{
	return id;
}
