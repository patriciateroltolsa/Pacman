#ifndef _PACMAN_H
#define _PACMAN_H

#pragma comment(lib, "glut32.lib")

#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Pacman
{
private:
	float squareSize;
public:
	float x, y;
	float mouth_angle;

	Pacman();
	~Pacman();

	void setPacman(float x, float y, float angle);

	//Method to draw the pacman character through consicutive circle algorithm
	void drawPacman(float rotation);

};
#endif
