#include "pacman.h"

Pacman::Pacman()
{
	this->squareSize = 50.0;
	this->x = 0;
	this->y = 0;
	this->mouth_angle = 0.0;
	this->life = 3;
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

void Pacman::drawPacman2D(float rotation)
{
	float x, y; //Coordinate of pacman

	glBegin(GL_LINES);

	glColor3f(1.0, 1.0, 0.0); //Yellow

	//Improved double for statement with one for statement
	for (int i = 0 + mouth_angle; i < 360 - mouth_angle; i++) //Mouth_angle's range is 0~45degree
	{
		glVertex2f(this->x*squareSize, this->y*squareSize);
		x = 16 * cos((i + 90 * rotation) * M_PI / 180.0) + (this->x*squareSize);
		y = 16 * sin((i + 90 * rotation) * M_PI / 180.0) + (this->y*squareSize);
		glVertex2f(x, y);
	}

	glEnd();
}

void Pacman::drawLife()
{
	int x, y; //Coordinate of life

	glBegin(GL_LINES);

	glColor3f(1.0, 1.0, 0.0); 

	for (int k = 0; k < 32; k++)
	{
		x = (float)k / 2.5 * cos((30) * M_PI / 180.0);
		y = (float)k / 2.5* sin((30) * M_PI / 180.0);
		for (int i = 30; i < 330; i++)
		{
			glVertex2f(x, y);
			x = (float)k / 2.5 * cos((i)* M_PI / 180.0);
			y = (float)k / 2.5 * sin((i)* M_PI / 180.0);
			glVertex2f(x, y);
		}
	}

	glEnd();
}



void Pacman::drawPacman3D(float rotation)
{
	glPushMatrix();

	glColor3f(1.0, 1.0, 0.0); 
	glTranslatef(this->x*squareSize, this->y*squareSize, -10);
	glutSolidSphere(15, 50, 50);

	glPopMatrix();
}
