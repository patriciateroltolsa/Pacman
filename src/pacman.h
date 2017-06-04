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
	float x, y; // Coordinate of pacman
	float mouth_angle;
	float life; //Left life of game

	Pacman();
	~Pacman();

	void setPacman(float x, float y, float angle);

	void drawPacman2D(float rotation);
	void drawPacman3D(float rotation);

	void drawLife();

};
#endif
