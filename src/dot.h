#ifndef _DOT_H
#define _DOT_H

#pragma comment(lib, "glut32.lib")

#include <deque>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Dot
{
private:
	float squareSize;
	int points;
	deque <float> dot;

public:
	float x, y;

	Dot();
	~Dot();

	void dotInit();

	//Method to check if the food has been eaten
	bool dotEaten(int x, int y, float pacmanX, float pacmanY);

	//Method to draw all the food left and delete the ate one
	void drawDot(float pacmanX, float pacmanY);

	int getPoint();

};
#endif