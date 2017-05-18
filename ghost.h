#ifndef _GHOST_H
#define _GHOST_H

#pragma comment(lib, "glut32.lib")

#include <vector>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Ghost
{
private:
	float squareSize;

public:
	float x, y;
	int id;

	Ghost(float x, float y, int id);
	~Ghost();

	void setGhost(float x, float y, int id);

	//Method to draw the monster character through consecutive circles algorithm
	void drawGhost(float r, float g, float b);

};
#endif