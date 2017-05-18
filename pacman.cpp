#include "pacman.h"

Pacman::Pacman(void)
{
	this->squareSize = 50.0;
	this->x = 0;
	this->y = 0;
}

Pacman::~Pacman(void)
{

}

void Pacman::setPacman(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Pacman::drawPacman(float rotation)
{
	int x, y;
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	for (int k = 0; k < 32; k++){
		x = (float)k / 2.0 * cos((30 + 90 * rotation) * M_PI / 180.0) + (this->x*squareSize);
		y = (float)k / 2.0* sin((30 + 90 * rotation) * M_PI / 180.0) + (this->y*squareSize);
		for (int i = 30; i < 330; i++){
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos((i + 90 * rotation) * M_PI / 180.0) + (this->x*squareSize);
			y = (float)k / 2.0* sin((i + 90 * rotation) * M_PI / 180.0) + (this->y*squareSize);
			glVertex2f(x, y);
		}
	}
	glEnd();
}