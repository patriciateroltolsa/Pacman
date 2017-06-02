#include "map.h"

Map::Map()
{
	squareSize = 50.0;
	level = 1; // There are 3 levels
    blue[0]=0, blue[1]=0.2, blue[2]=0.4;
    black[0]=0, black[1]=0, black[2]=0;
}

Map::~Map()
{

}

void Map::mapInit1()
{
	//Fill the bitmap with the obstacles
	bitmap.clear();
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,	true, true,  true,  true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false,	true, true,  true,  true, true });
	bitmap.push_back({ true, false, true,  true,  true,  false, true,  false, true,  false,	true, true,  true,  true, true });
	bitmap.push_back({ true, false, false, true,  false, false, false, false, true,  false,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  false, false, false, true,  true,  false, false, false,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  true,  false, true,  true,  false, false, true,  true,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  false, false, false, true,  true,  false, false, false,	true, true,  true,  true, true });
	bitmap.push_back({ true, false, false, true,  false, false, false, false, true,  false,	true, true,  true,  true, true });
	bitmap.push_back({ true, false, true,  true,  true,  false, true,  false, true,  false,	true, true,  true,  true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,	true, true,  true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,	true, true,  true,  true, true });

	border = { 0, 0, 11, 1, 11, 11, 10, 1, 0, 10, 11, 11, 1, 10, 0, 0 }; //Coordinates of the border walls

	//Coordinates of the obstacles (divided into 3 for clarity)
	obstaclesTop = { 2.5, 2.5, 2.5, 3.5, 3.5, 3.5, 4.5, 1.5, 5.5, 1.5, 5.5, 2.5,
	                 6.5, 1.5, 7.5, 3.5, 8.5, 2.5, 8.5, 3.5 };

	obstaclesMiddle = { 2.5, 4.5, 2.5, 6.5, 4.5, 5.5, 4.5, 6.5, 5.5, 4.5, 5.5, 5.5,
	                    6.5, 5.5, 6.5, 6.5, 8.5, 4.5, 8.5, 6.5 };

	obstaclesBottom = { 2.5, 8.5, 3.5, 8.5, 5.5, 8.5, 5.5, 9.5, 7.5, 8.5, 8.5, 8.5 };
}

void Map::mapInit2()
{
	bitmap.clear();
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,   true,  true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false,  true,  true, true });
	bitmap.push_back({ true, false, true,  true,  false, true,  true,  true,  false, true,  true,  false,  true,  true, true });
	bitmap.push_back({ true, false, false, true,  false, true,  false, true,  false, true,  true,  false,  true,  true, true });
	bitmap.push_back({ true, true,  false, false, false, false, false, false, false, true,  false, false,  true,  true, true });
	bitmap.push_back({ true, true,  true,  false, true,  true,  true,  true,  false, false, false, true,   true,  true, true });
	bitmap.push_back({ true, false, false, false, false, true,  true,  false, false, true,  true,  true,   true,  true, true });
	bitmap.push_back({ true, true,  true,  false, true,  true,  true,  true,  false, false, false, true,   true,  true, true });
	bitmap.push_back({ true, true,  false, false, false, false, false, false, false, true,  false, false,  true,  true, true });
	bitmap.push_back({ true, false, false, true,  false, true,  false, true,  false, true,  true,  false,  true,  true, true });
	bitmap.push_back({ true, false, true,  true,  false, true,  true,  true,  false, true,  true,  false,  true,  true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false,  true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,   true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,   true,  true, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,   true,  true, true });

	border = { 0, 0, 13, 1, 13, 13, 12, 1, 0, 12, 13, 13, 1, 12, 0, 0 }; 

	obstaclesTop = { 2.5, 2.5, 2.5, 3.5, 3.5, 3.5, 4.5, 1.5, 5.5, 1.5, 5.5, 2.5,
					 7.5, 1.5, 7.5, 2.5, 8.5, 1.5, 9.5, 3.5, 10.5, 2.5, 10.5, 3.5 };

	obstaclesMiddle = { 2.5, 5.5, 2.5, 6.5, 2.5, 7.5, 3.5, 5.5, 3.5, 7.5,
						5.5, 4.5, 5.5, 5.5, 5.5, 6.5, 5.5, 7.5, 6.5, 5.5,
						6.5, 6.5, 7.5, 4.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5,
						9.5, 5.5, 9.5, 7.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5 };

	obstaclesBottom = { 2.5, 9.5, 2.5, 10.5, 3.5, 9.5, 3.5, 10.5, 4.5, 9.5,
						5.5, 11.5, 6.5, 9.5, 6.5, 10.5, 6.5, 11.5, 7.5, 11.5,
						8.5, 9.5, 9.5, 9.5, 9.5, 10.5, 10.5, 9.5, 10.5, 10.5 };
}

void Map::mapInit3()
{
	bitmap.clear();
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, false, true,  true,  true,  true,  false, true,  true,  false, true,  true,  true,  false, true });
	bitmap.push_back({ true, false, false, false, false, true,  false, true,  false, false, false, false, true,  false, true });
	bitmap.push_back({ true, false, true,  true,  false, false, false, false, false, true,  true,  false, false, false, true });
	bitmap.push_back({ true, false, false, true,  true,  false, true,  true,  true,  true,  false, false, true,  false, true });
	bitmap.push_back({ true, true,  false, false, false, false, true,  false, true,  true,  false, true,  true,  false, true });
	bitmap.push_back({ true, true,  true,  true,  true,  false, false, false, true,  false, false, false, false, false, true });
	bitmap.push_back({ true, true,  false, false, false, false, true,  false, true,  true,  false, true,  true,  false, true });
	bitmap.push_back({ true, false, false, true,  true,  false, true,  true,  true,  true,  false, false, true,  false, true });
	bitmap.push_back({ true, false, true,  true,  false, false, false, false, false, true,  true,  false, false, false, true });
	bitmap.push_back({ true, false, false, false, false, true,  false, true,  false, false, false, false, true,  false, true });
	bitmap.push_back({ true, false, true,  true,  true,  true,  false, true,  true,  false, true,  true,  true,  false, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true,  true });

	border = { 0, 0, 15, 1, 15, 15, 14, 1, 0, 14, 15, 15, 1, 14, 0, 0 }; 

	obstaclesTop = { 2.5, 2.5, 2.5, 3.5, 2.5, 4.5, 2.5, 5.5, 3.5,
	               	5.5, 4.5, 2.5, 4.5, 3.5, 5.5, 3.5, 5.5, 4.5,
	            	6.5, 1.5, 7.5, 1.5, 7.5, 2.5, 7.5, 3.5, 7.5,
					4.5, 8.5, 1.5, 9.5, 3.5, 9.5, 4.5, 10.5, 2.5,
					10.5, 3.5, 11.5, 5.5, 12.5, 2.5, 12.5, 3.5,
					12.5, 4.5, 12.5, 5.5 };

	obstaclesMiddle = { 2.5, 7.5, 3.5, 7.5, 2.5, 8.5, 4.5, 10.5,
						4.5, 9.5, 5.5, 9.5, 5.5, 8.5, 5.5, 7.5, 5.5,
						6.5, 6.5, 6.5, 6.5, 8.5, 6.5, 9.5, 7.5, 8.5,
						8.5, 8.5, 8.5, 9.5, 9.5, 9.5, 9.5, 8.5, 9.5,
						7.5, 9.5, 6.5, 8.5, 6.5, 10.5, 9.5, 10.5,
						10.5, 11.5, 7.5, 12.5, 7.5, 12.5, 8.5 };

	obstaclesBottom = { 2.5, 10.5, 2.5, 11.5, 2.5, 12.5, 3.5, 12.5,
						5.5, 12.5, 6.5, 12.5, 6.5, 11.5, 8.5, 11.5,
						8.5, 12.5, 9.5, 12.5, 11.5, 12.5, 12.5, 12.5,
						12.5, 11.5, 12.5, 10.5 };
}

//Method to draw the floor of map
void Map::drawFloor()
{
    glPushMatrix();
    glColor3fv(black);
    glTranslated(border.at(2) / 2 * squareSize, border.at(2) / 2 * squareSize, -5);
    glScalef(1, 1, 0.01);
    glutSolidCube(border.at(2));    
    glPopMatrix();
}

//Method to draw the obstacle course and the walls
void Map::drawLabyrinth()
{
	//Border1
	for (int i = 0; i < border.size(); i = i + 8)
	{
		glPushMatrix();

		//Calculate center of border
		float boderX = (border.at(i) * squareSize + border.at(i + 2)*squareSize) / 2.0;
		float boderY = (border.at(i + 1) * squareSize + border.at(i + 3) * squareSize) / 2.0;
		float boderZ = squareSize / 2.0;

		glTranslatef(boderX, boderY, boderZ);
		glScalef(border.at(2), 1, 1); //Long x-axis cube
		glColor3fv(blue);
		glutSolidCube(50);

		glPopMatrix();
	}

	//Border2
	for (int i = 4; i < border.size(); i = i + 8)
	{
		glPushMatrix();

		float boderX = (border.at(i) * squareSize + border.at(i + 2) * squareSize) / 2.0;
		float boderY = (border.at(i + 1) * squareSize + border.at(i + 3) * squareSize) / 2.0;
		float boderZ = squareSize / 2.0;

		glTranslatef(boderX, boderY, boderZ);
		glScalef(1, border.at(2)-1, 1); //Long y-axis cube
		glColor3fv(blue);
		glutSolidCube(50);

		glPopMatrix();
	}

	//Obstacles
	for (int j = 0; j < obstaclesBottom.size(); j = j + 2) 
	{
		glPushMatrix();

		//Calculate center of obstacle
		float obstacleX = obstaclesBottom.at(j) * squareSize;
		float obstacleY = obstaclesBottom.at(j + 1) * squareSize;
		float obstacleZ = squareSize / 2.0;

		glTranslated(obstacleX, obstacleY, obstacleZ);
		glColor3fv(blue);
		glutSolidCube(50);

		glPopMatrix();

	}

	for (int k = 0; k < obstaclesMiddle.size(); k = k + 2)
	{
		glPushMatrix();

		float obstacleX = obstaclesMiddle.at(k) * squareSize;
		float obstacleY = obstaclesMiddle.at(k + 1) * squareSize;
		float obstacleZ = squareSize / 2.0;

		glTranslated(obstacleX, obstacleY, obstacleZ);
		glColor3fv(blue);
		glutSolidCube(50);

		glPopMatrix();
	}

	for (int p = 0; p < obstaclesTop.size(); p = p + 2)
	{
		glPushMatrix();

		float obstacleX = obstaclesTop.at(p) * squareSize;
		float obstacleY = obstaclesTop.at(p + 1) * squareSize;
		float obstacleZ = squareSize / 2.0;

		glTranslated(obstacleX, obstacleY, obstacleZ);
		glColor3fv(blue) ;
		glutSolidCube(50);

		glPopMatrix();
	}
}
