#pragma once
class Point
{
public:
	Point(int id, int x, int y);
	~Point();
private:
	int id;
	int xPos;
	int yPos;
public:
	int getx();
	int gety();
	int getid();
};

