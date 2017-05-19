#include "dot.h"
#include "sound.h"

Dot::Dot(void)
{
	this->squareSize = 50.0;
	this->points = 0;
	dotInit();
}
Dot::~Dot(void)
{

}
void Dot::dotInit()
{
	dot = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5,
		1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5,
		2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5,
		6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5,
		4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5,
		5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5,
		3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5,
		7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5,
		3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5,
		9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5,
		10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5,
		11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5,
		11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5,
		13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5,
		13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
}

bool Dot::dotEaten(int x, int y, float pacmanX, float pacmanY)
{
	if (x >= pacmanX - 16.0 *cos(359 * M_PI / 180.0) && x <= pacmanX + 16.0*cos(359 * M_PI / 180.0)){
		if (y >= pacmanY - 16.0*cos(359 * M_PI / 180.0) && y <= pacmanY + 16.0*cos(359 * M_PI / 180.0)){
			return true;
		}
	}
	return false;
	}

void Dot::drawDot(float pacmanX, float pacmanY){
	deque<float> temp;
	//check if the food has not been eaten
	for (int i = 0; i < dot.size(); i = i + 2) {
		if (!dotEaten(dot.at(i)*squareSize, dot.at(i + 1)*squareSize, pacmanX, pacmanY)) {
			temp.push_back(dot.at(i));
			temp.push_back(dot.at(i + 1));
		}
		else {
			playSound(2);
			points++;
		}
	}
	dot.swap(temp);

	//draw all the food avilable
	for (int j = 0; j < dot.size(); j = j + 2)
	{
		glPushMatrix();
		glTranslatef(dot.at(j)*squareSize, dot.at(j + 1)*squareSize, -1);
		glColor3f(1.0, 1.0, 1.0); glutSolidSphere(10, 30, 30);
		glColor3f(0, 0, 0); glutWireSphere(10.1, 5, 5); //검정선 보이게 10.1로
		glPopMatrix();
	}
	glEnd();
}

int Dot::getPoint()
{
	return this->points;
}