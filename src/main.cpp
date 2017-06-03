/*

3D & 2D Pacman
Original: https://github.com/patriciateroltolsa/Pacman
Updates: https://github.com/ekdud014/OSS_pacman

Original Copyright (C) Patricia Terol
Updates Copyright (C) Yeji Rha, Dayoung Park, Sojeong Lee, Seungyeon Lee

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Windows.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <glut.h>

using namespace std;

#include "sound.h"
#include "dot.h"
#include "ghost.h"
#include "map.h"
#include "pacman.h"

Ghost Blinky(10.5, 8.5, 1);
Ghost Inky(13.5, 1.5, 2);
Ghost Clyde(4.5, 6.5, 3);
Ghost Pinky(2.5, 13.5, 4);

Map map;
Pacman pacman;
Dot dot;

GLsizei ww, hh; //screen size

bool replay = false; //Check if starts a new game
bool over = true; //Check for the game to be over
bool win = false; //Check for win the game
bool callOnce = false; //Check call sound function once
bool* keyStates = new bool[256]; //Record of all keys pressed
bool showResult = false;//Check for show result or continue

float squareSize = 50.0; //Size of one square on the game
float xIncrement = 0; //X movement on pacman
float yIncrement = 0; //Y movement on pacman
float angle = 0; //The angle(degree) of pacman's mouth
float angle_Increment = 3; //The angle increment of pacman's mouth
float cam_angle = 90 * 3.14 / 180; //Camera angle according to pacman's movement
float xx = -20, yy = -3.2, zz = -30; //Camera viewer direction

//Light varialble
float light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
float light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; //White
float light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
float light0_position[] = { 1.0, -1.0, 1.0, 0.0 };


int rotation = 0; //Orientation of pacman 
int mode = 2; //Check Projection 1:Frustum 2:Ortho
int points = 0; //Total points collected
int died = 0;//Count died number of time

double viewer[] = { 0, 0, 1 }; //Initial viewer location

void viewerInit()
{
	viewer[0] = -30;
	viewer[1] = -10;
	viewer[2] = -30;

	xx = -21, yy = -3.2, zz = -30;
}

//Initializes the game with the appropiate information
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//Clear screen black

	//Reset all keys
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}

	loadingSounds();

	//Using light
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_COLOR_MATERIAL);//Set to use color of object
	glShadeModel(GL_SMOOTH);
}

//Method to update the position of the ghosts randomly
void updateGhost(Ghost *ghost)
{
	//Find the current position of the monster. x1,y1 : min range & x2,y2 : max range
	int x1Quadrant = (int)((ghost->x - (2 / squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
	int x2Quadrant = (int)((ghost->x + (2 / squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
	int y1Quadrant = (int)((ghost->y - (2 / squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
	int y2Quadrant = (int)((ghost->y + (2 / squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);

	//Move ghosts acording to its direction until he hits an obstacle
	switch (ghost->id)
	{
	case 1:
		if (!map.bitmap.at(x1Quadrant).at((int)ghost->y))
		{
			ghost->x -= 2 / squareSize;
		}
		else
		{
			int current = ghost->id;
			do
			{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;

	case 2:
		if (!map.bitmap.at(x2Quadrant).at((int)ghost->y))
		{
			ghost->x += 2 / squareSize;
		}
		else
		{
			int current = ghost->id;
			do
			{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;

	case 3:
		if (!map.bitmap.at((int)ghost->x).at(y1Quadrant))
		{
			ghost->y -= 2 / squareSize;
		}
		else
		{
			int current = ghost->id;
			do
			{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;

	case 4:
		if (!map.bitmap.at((int)ghost->x).at(y2Quadrant))
		{
			ghost->y += 2 / squareSize;
		}
		else
		{
			int current = ghost->id;
			do
			{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

//Method to set the pressed key
void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;

	//viewer change with keyboard input
	if (key == 'x') viewer[0] -= 1;
	if (key == 'X') viewer[0] += 1;
	if (key == 'y') viewer[1] -= 1;
	if (key == 'Y') viewer[1] += 1;
	if (key == 'z') viewer[2] -= 1;
	if (key == 'Z') viewer[2] += 1;

	glutPostRedisplay();
}

//Method to unset the released key
void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

//Method to reset all the variable necessaries to start the game again
void resetGame()
{
	over = false;

	xIncrement = 0;
	yIncrement = 0;
	rotation = 0;
	cam_angle = 90 * 3.14 / 180;
	points = 0;
	dot.setPoint(0);
	viewerInit();

	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}

	if (map.level == 1)
	{
		Blinky.setGhost(14, 14, 1); //This ghost is invisible. In other words, there are three ghosts.
		Inky.setGhost(1.5, 9.5, 2);
		Clyde.setGhost(6.5, 3.5, 3);
		Pinky.setGhost(9.5, 5.5, 4);

		map.mapInit1();
		dot.dotInit1();
	}
	else if (map.level == 2)
	{
		Blinky.setGhost(8.5, 8.5, 1);
		Inky.setGhost(11.5, 1.5, 2);
		Clyde.setGhost(3.5, 4.5, 3);
		Pinky.setGhost(2.5, 11.5, 4);

		map.mapInit2();
		dot.dotInit2();
	}
	else if (map.level == 3)
	{
		Blinky.setGhost(10.5, 8.5, 1);
		Inky.setGhost(13.5, 1.5, 2);
		Clyde.setGhost(4.5, 6.5, 3);
		Pinky.setGhost(2.5, 13.5, 4);

		map.mapInit3();
		dot.dotInit3();
	}

	if (died == 3)
	{
		showResult = true;
	}
	else
		showResult = false;

	if (!callOnce)
	{
		setSoundInit();
		callOnce = true;
	}
}

//Method to update the movement of the pacman according to the movement keys pressed
void keyOperations()
{
	//Get current position of pacman
	float left_top[2] = { (float)(1.18 + xIncrement) * squareSize, (float)(1.18 + yIncrement) * squareSize };
	float left_bottom[2] = { (float)(1.18 + xIncrement) * squareSize, (float)(1.82 + yIncrement) * squareSize };
	float right_top[2] = { (float)((1.82 + xIncrement) * squareSize), (float)((1.18 + yIncrement) * squareSize) };
	float right_bottom[2] = { (float)((1.82 + xIncrement) * squareSize), (float)((1.82 + yIncrement) * squareSize) };

	//Update according to keys pressed
	if (keyStates['a'] || keyStates['A']) //Rotate to left
	{
		keyStates['a'] = false;
		keyStates['A'] = false;

		cam_angle = cam_angle + 90 * 3.14 / 180;
		xx = 10 * sin(cam_angle) + viewer[0];
		zz = 10 * cos(cam_angle) + viewer[2];

		if (rotation == 1) //down direction
		{
			rotation = 0;
		}
		else if (rotation == 2) //Left direction
		{
			rotation = 1;
		}
		else if (rotation == 3) //Up direction
		{
			rotation = 2;
		}
		else if (rotation == 0) //Right direction
		{
			rotation = 3;
		}
	}

	if (keyStates['d'] || keyStates['D']) //rotate to right
	{
		keyStates['d'] = false;
		keyStates['D'] = false;

		cam_angle = cam_angle - 90 * 3.14 / 180;
		xx = 10 * sin(cam_angle) + viewer[0];
		zz = 10 * cos(cam_angle) + viewer[2];

		if (rotation == 1)
		{
			rotation = 2;
		}
		else if (rotation == 2)
		{
			rotation = 3;
		}
		else if (rotation == 3)
		{
			rotation = 0;
		}
		else if (rotation == 0)
		{
			rotation = 1;
		}
	}

	if (keyStates['s'] || keyStates['S']) //rotate to back
	{
		keyStates['s'] = false;
		keyStates['S'] = false;

		cam_angle = cam_angle + 180 * 3.14 / 180;
		xx = 10 * sin(cam_angle) + viewer[0];
		zz = 10 * cos(cam_angle) + viewer[2];

		if (rotation == 1)
		{
			rotation = 3;
		}
		else if (rotation == 2)
		{
			rotation = 0;
		}
		else if (rotation == 3)
		{
			rotation = 1;
		}
		else if (rotation == 0)
		{
			rotation = 2;
		}
	}

	if (keyStates['w'] || keyStates['W']) //go straight 
	{
		if (rotation == 0)
		{
			right_top[0] += 2;
			right_bottom[0] += 2;

			//Check if right moved location is obstacle
			int x2Quadrant = (int)((right_top[0]) / squareSize);
			bool isObstacle1 = map.bitmap.at(x2Quadrant).at((int)right_top[1] / squareSize);

			if (!isObstacle1)
			{
				x2Quadrant = (int)((right_bottom[0]) / squareSize);
				bool isObstacle2 = map.bitmap.at(x2Quadrant).at((int)right_bottom[1] / squareSize);

				if (!isObstacle2)
				{
					xIncrement += 2 / squareSize;

					//Camera direction set
					zz = viewer[2];
					xx = viewer[0] + 10;

					//Camera location set
					viewer[0] += 0.2;
					xx += 0.2;
				}
			}
		}
		else if (rotation == 1)
		{
			left_bottom[1] += 2;
			right_bottom[1] += 2;

			//Check if down moved location is obstacle
			int y1Quadrant = (int)((left_bottom[1]) / squareSize);
			bool isObstacle1 = map.bitmap.at((int)left_bottom[0] / squareSize).at(y1Quadrant);

			if (!isObstacle1)
			{
				y1Quadrant = (int)((right_bottom[1]) / squareSize);
				bool isObstacle2 = map.bitmap.at((int)right_bottom[0] / squareSize).at(y1Quadrant);

				if (!isObstacle2)
				{
					yIncrement += 2 / squareSize;

					zz = viewer[2] + 10;
					xx = viewer[0];

					viewer[2] += 0.2;
					zz += 0.2;
				}
			}
		}
		else if (rotation == 2)
		{
			left_top[0] -= 2;
			left_bottom[0] -= 2;

			//Check if left moved location is obstacle
			int x1Quadrant = (int)((left_top[0]) / squareSize);
			bool isObstacle1 = map.bitmap.at(x1Quadrant).at((int)left_top[1] / squareSize);

			if (!isObstacle1)
			{
				x1Quadrant = (int)((left_bottom[0]) / squareSize);
				bool isObstacle2 = map.bitmap.at(x1Quadrant).at((int)left_bottom[1] / squareSize);

				if (!isObstacle2)
				{
					xIncrement -= 2 / squareSize;

					zz = viewer[2];
					xx = viewer[0] - 10;

					viewer[0] -= 0.2;
					xx -= 0.2;
				}
			}
		}
		else
		{
			left_top[1] -= 2;
			right_top[1] -= 2;

			//Check if up moved location is obstacle
			int y1Quadrant = (int)((left_top[1]) / squareSize);
			bool isObstacle1 = map.bitmap.at((int)left_top[0] / squareSize).at(y1Quadrant);

			if (!isObstacle1)
			{
				y1Quadrant = (int)((right_top[1]) / squareSize);
				bool isObstacle2 = map.bitmap.at((int)right_top[0] / squareSize).at(y1Quadrant);

				if (!isObstacle2)
				{
					yIncrement -= 2 / squareSize;

					zz = viewer[2] - 10;
					xx = viewer[0];

					viewer[2] -= 0.2;
					zz -= 0.2;
				}
			}
		}
	}

	if (keyStates[27]) //ESC
	{
		exit(-1);
	}

	if (keyStates[' '])
	{
		if (!replay && over) //Go welcome screen
		{
			resetGame();
			replay = true;
		}
		else if (replay && over) //Restart the game
		{
			replay = false;
		}
	}

	glutPostRedisplay();
}

//Method to check if the game is over
void gameOver()
{
	int pacmanX = (int)(1.5 + xIncrement); // 1.5 : 1(count wall) + 0.5(location of center)
	int pacmanY = (int)(1.5 + yIncrement);

	if (pacmanX == (int)Blinky.x && pacmanY == (int)Blinky.y)
	{
		over = true;
	}
	if (pacmanX == (int)Inky.x && pacmanY == (int)Inky.y)
	{
		over = true;
	}
	if (pacmanX == (int)Clyde.x && pacmanY == (int)Clyde.y)
	{
		over = true;
	}
	if (pacmanX == (int)Pinky.x && pacmanY == (int)Pinky.y)
	{
		over = true;
	}

	//Points are different when you eat by level
	if (map.level == 1)
	{
		if (points == 55) //If you want check it works well, then modify 55 to smaller number
		{
			playSound(4);
			map.level = 2;
			resetGame(); //Go to Level 2
		}
	}
	else if (map.level == 2)
	{
		if (points == 74)
		{
			playSound(4);
			map.level = 3;
			resetGame(); //Go to Level 3
		}
	}
	else if (map.level == 3)
	{
		if (points == 106)
		{
			win = true;
			over = true;
		}
	}

	if (!over)
	{
		callOnce = false;
	}

}

//Method to display the results of the game at the ends
void resultScreen()
{
	viewerInit();
	glClearColor(0, 0.2, 0.4, 1.0);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	if (showResult)
	{
		if (win)
		{
			char* message = "*************************************";
			glRasterPos2f(170, 250);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "CONGRATULATIONS, YOU WON! ";
			glColor3f(1, 1, 1);
			glRasterPos2f(200, 300);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "*************************************";
			glRasterPos2f(170, 350);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "To start or restart the game, press the space key.";
			glRasterPos2f(170, 550);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
		}
		else
		{
			char* message = "*************************";
			glRasterPos2f(210, 250);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "SORRY, YOU LOST ... ";
			glColor3f(1, 1, 1);
			glRasterPos2f(250, 300);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "*************************";
			glRasterPos2f(210, 350);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "You got: ";
			glRasterPos2f(260, 400);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
			string result = to_string(points);
			message = (char*)result.c_str();
			glRasterPos2f(350, 400);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
			message = " points!";
			glRasterPos2f(385, 400);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

			message = "To start or restart the game, press the space key.";
			glRasterPos2f(170, 550);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
		}

		//Initialization pacman's life
		died = 0;
		pacman.life = 3;
	}
	else
	{
		char* message = " Continue? ";
		glRasterPos2f(320, 350);
		glColor3f(1, 1, 1);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	}
}

//Method to display the starting instructions
void welcomeScreen()
{
	viewerInit();
	glClearColor(0, 0.2, 0.4, 1.0); //Navy
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	char* message = "*************************************";
	glRasterPos2f(150, 200);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

	message = "PACMAN - by Patricia Terol";
	glColor3f(1, 1, 1);
	glRasterPos2f(225, 250);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

	message = "*************************************";
	glRasterPos2f(150, 300);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);

	message = "To control Pacman use A to go right, D to go left, W to go up and S to go down.";
	glRasterPos2f(50, 400);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);

	message = "To start or restart the game, press the space key.";
	glRasterPos2f(170, 450);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
}

//Methdo to reshape the game is the screen size changes
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (mode == 1)
	{
		glFrustum(-5, 5, 5, -5, 2, 20);
	}
	else if (mode == 2)
	{
		glOrtho(0, 750, 750, 0, -750, 750);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ww = w;
	hh = h;
}

void mainScreen()
{
	//3D and first person view
	mode = 1;
	reshape(ww, hh);
	gluLookAt(viewer[0], viewer[1], viewer[2], xx, yy, zz, 0, 1, 0);

	if (points == 1)
	{
		over = false;
	}

	gameOver();
	keyOperations();

	//Increaseing the degree of pacman's mouth
	angle += angle_Increment; //Angle's range is 0~45degree
	if (angle > 45) //Change the signal of angle_Increment
	{
		angle_Increment = -angle_Increment;
	}
	else if (angle < 0)
	{
		angle_Increment = -angle_Increment;
	}

	//Call the functions to draw
	if (replay)
	{
		if (!over)
		{
			glPushMatrix();
			glRotated(90, 1, 0, 0);
			glScalef(0.1, 0.1, 0.1);
			glTranslated(-375, -375, -5);
			map.drawFloor();
			map.drawLabyrinth();
			pacman.setPacman(1.5 + xIncrement, 1.5 + yIncrement, angle);
			dot.drawDot3D(pacman.x * squareSize, pacman.y * squareSize);
			points = dot.getPoint();
			pacman.drawPacman3D(rotation);

			updateGhost(&Blinky);
			updateGhost(&Inky);
			updateGhost(&Clyde);
			updateGhost(&Pinky);

			Blinky.drawGhost3D(1.0, 0.0, 0.0); //Red
			Inky.drawGhost3D(0.0, 1.0, 1.0); //Cyan
			Clyde.drawGhost3D(1.0, 0.3, 0.0); //Orange
			Pinky.drawGhost3D(1.0, 0.0, 0.6); //Magenta

			glPopMatrix();
			Sleep(10);

			if (died == 1)
			{
				pacman.life = 2;
			}
			if (died == 2)
			{
				pacman.life = 1;
			}
			if (died == 3)
			{
				pacman.life = 0;
			}
		}
		else
		{
			if (!win)
			{
				playSound(3);
			}
			else
			{
				playSound(5);
			}

			mode = 2;
			reshape(ww, hh);

			if (pacman.life == 3)
			{
				died = 1;
			}
			if (pacman.life == 2)
			{
				died = 2;
			}
			if (pacman.life == 1)
			{
				died = 3;
			}

			resultScreen();
		}
	}
	else
	{
		mode = 2;
		reshape(ww, hh);
		glLoadIdentity();
		welcomeScreen();
	}
}

void mapScreen()
{
	//Map & Information
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	mode = 2;
	reshape(ww, hh);
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); //Look vertically on side

	if (replay)
	{
		if (!over)
		{
			//Print score
			glPushMatrix();
			glColor3f(1, 1, 1);
			char *message = "score : ";
			glRasterPos2f(20, 60);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);

			string result = to_string(points);
			message = (char*)result.c_str();
			glRasterPos2f(80, 60);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
			glPopMatrix();

			//Print life
			glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			if (pacman.life >= 1)
			{
				glTranslatef(squareSize - 20, squareSize - 25, 60);
				pacman.drawLife();

				if (pacman.life >= 2)
				{
					glTranslatef(30, 0, 0);
					pacman.drawLife();

					if (pacman.life >= 3)
					{
						glTranslatef(30, 0, 0);
						pacman.drawLife();

					}
				}
			}
			glPopMatrix();
		}
	}

	glPushMatrix(); //Save root
	glScalef(0.3, 0.3, 0.3);
	glTranslated(1600, 50, 0);

	glPushMatrix();

	//Scaling by level
	if (map.level == 1)
	{
		glScalef(15.0 / 11.0, 15.0 / 11.0, 1); //11 X 11
	}
	else if (map.level == 2)
	{
		glScalef(15.0 / 13.0, 15.0 / 13.0, 1); //13 X 13
	}

	else if (map.level == 3)
	{
		glScalef(1, 1, 1); //15 X 15
	}

	gameOver();
	keyOperations();

	if (replay)
	{
		if (!over)
		{
			map.drawFloor();
			map.drawLabyrinth();
			pacman.setPacman(1.5 + xIncrement, 1.5 + yIncrement, angle);
			dot.drawDot2D(pacman.x * squareSize, pacman.y * squareSize);
			points = dot.getPoint();
			pacman.drawPacman2D(rotation);

			updateGhost(&Blinky);
			updateGhost(&Inky);
			updateGhost(&Clyde);
			updateGhost(&Pinky);

			if (map.level >= 2)
				Blinky.drawGhost2D(1.0, 0.0, 0.0);

			Inky.drawGhost2D(0.0, 1.0, 1.0);
			Clyde.drawGhost2D(1.0, 0.3, 0.0);
			Pinky.drawGhost2D(1.0, 0.0, 0.6);

			Sleep(10);
			playSound(1);
		}
	}

	glPopMatrix();
	glPopMatrix();
}

//Method to display the screen and its elements
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); //Black
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	mainScreen();
	mapScreen();
	
	glutSwapBuffers();
}

//Main functions that controls the running of the game
int main(int argc, char** argv)
{
	//Initialize and create the screen
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("PACMAN - by Patricia Terol");


	//Define all the control functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	//Run the game
	init();
	glutMainLoop();

	return 0;
}