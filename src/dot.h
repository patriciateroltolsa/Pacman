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
	float x, y; // Coordinate of dots

	Dot();
	~Dot();

	void dotInit1();
	void dotInit2();
	void dotInit3();

	//Method to check if the food has been eaten
	bool dotEaten(int x, int y, float pacmanX, float pacmanY);

	//Method to draw all the food left and delete the ate one
	void drawDot2D(float pacmanX, float pacmanY);
	void drawDot3D(float pacmanX, float pacmanY);

	int getPoint();

	void setPoint(int n);

};
#endif