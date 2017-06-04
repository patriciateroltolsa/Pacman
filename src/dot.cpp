#include "dot.h"
#include "sound.h"

Dot::Dot()
{
	this->squareSize = 50.0;
	this->points = 0;
}

Dot::~Dot()
{

}

void Dot::dotInit1()
{
	dot = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5,
			2.5, 1.5, 2.5, 5.5, 2.5, 7.5, 2.5, 9.5, 3.5, 1.5, 3.5, 2.5, 3.5, 4.5, 3.5, 5.5, 3.5, 6.5,
			3.5, 7.5, 3.5, 9.5, 4.5, 2.5, 4.5, 3.5, 4.5, 4.5, 4.5, 7.5, 4.5, 8.5, 4.5, 9.5, 5.5, 3.5,
			5.5, 6.5, 5.5, 7.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 7.5, 6.5, 8.5, 6.5, 9.5, 7.5, 1.5,
			7.5, 2.5, 7.5, 4.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 8.5, 1.5, 8.5, 5.5, 8.5, 7.5,
			8.5, 9.5, 9.5, 1.5, 9.5, 2.5, 9.5, 3.5, 9.5, 4.5, 9.5, 5.5, 9.5, 6.5, 9.5, 7.5, 9.5, 8.5,
			9.5, 9.5, };
}

void Dot::dotInit2()
{
	dot = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5,
			1.5, 10.5, 1.5, 11.5, 2.5, 1.5, 2.5, 4.5, 2.5, 8.5, 2.5, 11.5, 3.5, 1.5, 3.5, 2.5, 3.5,
			4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 11.5, 4.5, 2.5, 4.5, 3.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5,
			7.5, 4.5, 8.5, 4.5, 10.5, 4.5, 11.5, 5.5, 3.5, 5.5, 8.5, 5.5, 9.5, 5.5, 10.5, 6.5, 1.5,
			6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 7.5, 6.5, 8.5, 7.5, 3.5, 7.5, 8.5, 7.5, 9.5, 7.5, 10.5,
			8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 6.5, 8.5, 7.5, 8.5, 8.5, 8.5, 10.5, 8.5, 11.5,
			9.5, 1.5, 9.5, 2.5, 9.5, 4.5, 9.5, 6.5, 9.5, 8.5, 9.5, 11.5, 10.5, 1.5, 10.5, 4.5, 10.5,
			8.5, 10.5, 11.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5,
			7.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, };
}

void Dot::dotInit3()
{
	dot = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5,
			1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5,
			1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5,
			3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5,
			12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5,
			6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5,
			7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5,
			8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5,
			11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5,
			11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5,
			6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5,
			9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5,
			7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
}

//Check the dot eaten if the dot coordinate is in the range of pacman coordinate
bool Dot::dotEaten(int x, int y, float pacmanX, float pacmanY)
{
	if (x >= pacmanX - 16.0 * cos(359 * M_PI / 180.0) && x <= pacmanX + 16.0 * cos(359 * M_PI / 180.0))
	{
		if (y >= pacmanY - 16.0 * cos(359 * M_PI / 180.0) && y <= pacmanY + 16.0 * cos(359 * M_PI / 180.0))
		{
			return true;
		}
	}

	return false;
}

//Method to draw all the left dot and delete the eaten one
void Dot::drawDot2D(float pacmanX, float pacmanY)
{
	deque<float> temp; //Store remian dot

	//Check if the dot has not been eaten
	for (int i = 0; i < dot.size(); i = i + 2) 
	{
		bool checkEaten = dotEaten(dot.at(i) * squareSize, dot.at(i + 1) * squareSize, pacmanX, pacmanY);
		
		if (!checkEaten)
		{
			temp.push_back(dot.at(i));
			temp.push_back(dot.at(i + 1));
		}
		else
		{
			playSound(2); //2 : Dot eating sound
			points++;
		}
	}

	dot.swap(temp);
	glPointSize(2.0);
	
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0); //White
	
	//Draw all the dot avilable
	for (int j = 0; j < dot.size(); j = j + 2)
	{
		glVertex2f(dot.at(j) * squareSize, dot.at(j + 1) * squareSize);
	}

	glEnd();
}

void Dot::drawDot3D(float pacmanX, float pacmanY)
{
	deque<float> temp; 

	for (int i = 0; i < dot.size(); i = i + 2)
	{
		bool checkEaten = dotEaten(dot.at(i) * squareSize, dot.at(i + 1) * squareSize, pacmanX, pacmanY);
		if (!checkEaten)
		{
			temp.push_back(dot.at(i));
			temp.push_back(dot.at(i + 1));
		}
		else
		{
			playSound(2);
			points++;
		}
	}

	dot.swap(temp);

	for (int j = 0; j < dot.size(); j = j + 2)
	{
		glPushMatrix(); 
		glTranslatef(dot.at(j) * squareSize, dot.at(j + 1) * squareSize, -1);
		glColor3f(1.0, 1.0, 1.0); //White
		glutSolidSphere(3, 10, 10);
		glPopMatrix();
	}
	glEnd();
}

int Dot::getPoint()
{
	return this->points;
}

void Dot::setPoint(int n)
{
	this->points = n;
}