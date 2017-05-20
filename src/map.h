#ifndef _MAP_H
#define _MAP_H

#pragma comment(lib, "glut32.lib")

#include <vector>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Map
{
private:
	float squareSize;

public:

	Map();
	~Map();

	//Method to draw the obstacle course, the floor and the walls
	void drawLabyrinth();
    void drawFloor();
};
#endif