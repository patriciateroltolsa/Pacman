#include "ghost.h"

Ghost::Ghost(float x, float y, int id)
{
	this->x = x;
	this->y = y;
	this->id = id;
	squareSize = 50.0;
}

Ghost::~Ghost(void)
{

}

void Ghost::setGhost(float x, float y, int id)
{
	this->x = x;
	this->y = y;
	this->id = id;
}

//Method to draw the monster character through consecutive circles algorithm
void Ghost::drawGhost(float r, float g, float b){

	glPushMatrix();
	glColor3f(r, g, b);
	glTranslated(this->x*squareSize, this->y*squareSize, 0);
	glScaled(1, 1, 2);
	glutSolidSphere(16, 10, 10);

	glPopMatrix();

	//glEnd();
	//    //draw body
	//    glRectf((positionX*squareSize) - 17, positionY*squareSize, (positionX*squareSize) + 15, (positionY*squareSize) + 15);
	//    glBegin(GL_POINTS);
	//    glColor3f(0, 0.2, 0.4);
	//    //draw eyes and legs
	//    glVertex2f((positionX*squareSize) - 11, (positionY*squareSize) + 14); //legs
	//    glVertex2f((positionX*squareSize) - 1, (positionY*squareSize) + 14); //legs
	//    glVertex2f((positionX*squareSize) + 8, (positionY*squareSize) + 14); //legs
	//    glVertex2f((positionX*squareSize) + 4, (positionY*squareSize) - 3); //eyes
	//    glVertex2f((positionX*squareSize) - 7, (positionY*squareSize) - 3); //eyes
	//    glEnd();
}