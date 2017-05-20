#include "map.h"

vector<float> obstaclesTop = {	2.5, 2.5, 2.5, 3.5, 2.5, 4.5, 2.5, 5.5, 3.5, 
								5.5, 4.5, 2.5, 4.5, 3.5, 5.5, 3.5, 5.5, 4.5,
								6.5, 1.5, 7.5, 1.5, 7.5, 2.5, 7.5, 3.5, 7.5,
								4.5, 8.5, 1.5, 9.5, 3.5, 9.5, 4.5, 10.5, 2.5,
								10.5, 3.5, 11.5, 5.5, 12.5, 2.5, 12.5, 3.5,
								12.5, 4.5, 12.5, 5.5 };																						//coordinates of the obstacles (divided into 3 for clarity)
vector<float> obstaclesMiddle = {	2.5, 7.5, 3.5, 7.5, 2.5, 8.5, 4.5, 10.5,
									4.5, 9.5, 5.5, 9.5, 5.5, 8.5, 5.5, 7.5, 5.5,
									6.5, 6.5, 6.5, 6.5, 8.5, 6.5, 9.5, 7.5, 8.5,
									8.5, 8.5, 8.5, 9.5, 9.5, 9.5, 9.5, 8.5, 9.5,
									7.5, 9.5, 6.5, 8.5, 6.5, 10.5, 9.5, 10.5,
									10.5, 11.5, 7.5, 12.5, 7.5, 12.5, 8.5 };
vector<float> obstaclesBottom = {	2.5, 10.5, 2.5, 11.5, 2.5, 12.5, 3.5, 12.5,
									5.5, 12.5, 6.5, 12.5, 6.5, 11.5, 8.5, 11.5,
									8.5, 12.5, 9.5, 12.5, 11.5, 12.5, 12.5, 12.5,
									12.5, 11.5, 12.5, 10.5 };

vector<float> border = { 0, 0, 15, 1, 15, 15, 14, 1, 0, 14, 15, 15, 1, 14, 0, 0 }; //coordinates of the border walls

Map::Map(void)
{
	squareSize = 50.0;
}

Map::~Map(void)
{

}
//Method to draw the floor of map
void Map::drawFloor()
{
    glPushMatrix();
    
    glColor3f(0, 0.2, 0.4);
    glTranslated(15.0/2*squareSize, 15.0/2*squareSize, -5);
    glScalef(1, 1, 0.01);
    glutSolidCube(squareSize*15);
    
    glPopMatrix();
}
//Method to draw the obstacle course and the walls
void Map::drawLabyrinth(){
	//Border1
	for (int i = 0; i < border.size(); i = i + 8)
	{
		glPushMatrix();
		glTranslatef((border.at(i)*squareSize + border.at(i + 2)*squareSize) / 2.0, (border.at(i + 1)*squareSize + border.at(i + 3)*squareSize) / 2.0, 25);
		glScalef(15, 1, 1); //Long x-axis cube
		glColor3f(1.0, 1.0, 1.0); glutSolidCube(50);
		glColor3f(0, 0, 0); glutWireCube(50);
		glPopMatrix();
	}
	//Border2
	for (int i = 4; i < border.size(); i = i + 8)
	{
		glPushMatrix();
		glTranslatef((border.at(i)*squareSize + border.at(i + 2)*squareSize) / 2.0, (border.at(i + 1)*squareSize + border.at(i + 3)*squareSize) / 2.0, 25);
        glScalef(1, 15, 1); //Long y-axis cube
		glColor3f(1.0, 1.0, 1.0); glutSolidCube(50);
		glColor3f(0, 0, 0); glutWireCube(50);
		glPopMatrix();
	}

	//Obstacles
	for (int j = 0; j < obstaclesBottom.size(); j = j + 2) {
		glPushMatrix();
		glTranslated(obstaclesBottom.at(j) * squareSize, obstaclesBottom.at(j + 1) * squareSize, 25);
		glColor3f(0, 0, 0);
		glutWireCube(50);
		glColor3f(1, 1, 1);
		glutSolidCube(50);
		glPopMatrix();

	}
	for (int k = 0; k < obstaclesMiddle.size(); k = k + 2) {
		glPushMatrix();
		glTranslated(obstaclesMiddle.at(k) * squareSize, obstaclesMiddle.at(k + 1) * squareSize, 25);
		glColor3f(0, 0, 0);
		glutWireCube(50);
		glColor3f(1, 1, 1);
		glutSolidCube(50);
		glPopMatrix();
	}

	for (int p = 0; p < obstaclesTop.size(); p = p + 2)
	{
		glPushMatrix();
		glTranslatef(obstaclesTop.at(p) * squareSize, obstaclesTop.at(p + 1) * squareSize, 25);
		glColor3f(0, 0, 0);
		glutWireCube(50);
		glColor3f(1, 1, 1);
		glutSolidCube(50);
		glPopMatrix();
	}
}