#include "pacman.h"

Pacman::Pacman()
{
	this->squareSize = 50.0;
	this->x = 0;
	this->y = 0;
	this->mouth_angle = 0.0;
}

Pacman::~Pacman()
{

}

void Pacman::setPacman(float x, float y, float angle)
{
	this->x = x;
	this->y = y;
	this->mouth_angle = angle;
}

void Pacman::drawPacman(float rotation)
{
	float x, y;

	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);

	/*for (int k = 0; k < 32; k++) //k is the length of the diameter
	{
		x = (float)k / 2.0 * cos((30 + 90 * rotation) * M_PI / 180.0) + (this->x*squareSize);
		y = (float)k / 2.0* sin((30 + 90 * rotation) * M_PI / 180.0) + (this->y*squareSize);
		
		for (int i = 30; i < 330; i++)
		{
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos((i + 90 * rotation) * M_PI / 180.0) + (this->x*squareSize);
			y = (float)k / 2.0* sin((i + 90 * rotation) * M_PI / 180.0) + (this->y*squareSize);
			glVertex2f(x, y);
		}
	}*/

	//Improved double for statement with one for statement
	for (int i = 0+mouth_angle; i < 360-mouth_angle; i++) //mouth_angle's range is 0~45degree
	{
		glVertex2f(this->x*squareSize, this->y*squareSize);
		x = 16 * cos((i + 90 * rotation) * M_PI / 180.0) + (this->x*squareSize);
		y = 16 * sin((i + 90 * rotation) * M_PI / 180.0) + (this->y*squareSize);
		glVertex2f(x, y);
	}

	glEnd();
}
