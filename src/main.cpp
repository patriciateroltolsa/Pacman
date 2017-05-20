// Author: Patricia Terol
// Course: CSE 2050
// Project: assign10

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

bool replay = false; //check if starts a new game
bool over = true; //check for the game to be over
float squareSize = 50.0; //size of one square on the game
float xIncrement = 0; // x movement on pacman
float yIncrement = 0; // y movement on pacman
int rotation = 0; // orientation of pacman

vector<vector<bool>> bitmap; // 2d image of which squares are blocked and which are clear for pacman to move in 
bool* keyStates = new bool[256]; // record of all keys pressed 
int points = 0; // total points collected
GLdouble viewer[] = { 0, 0, 1 }; // initial viewer location

void viewerInit()
{
	viewer[0] = 0;
	viewer[1] = 0;
	viewer[2] = 1;
}

//Initializes the game with the appropiate information 
void init(void){
	//clear screen
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	//reset all keys
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
	//fill the bitmap with the obstacles
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
	bitmap.push_back({ true, true, true, true, true, false, false, false, true, false, false, false, false, false, true });
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });

	loadingSounds();
}

//Method to update the position of the monsters randomly
void updateGhost(Ghost *ghost){
	//find the current position of the monster
	int x1Quadrant = (int)((ghost->x - (2 / squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
	int x2Quadrant = (int)((ghost->x + (2 / squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
	int y1Quadrant = (int)((ghost->y - (2 / squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
	int y2Quadrant = (int)((ghost->y + (2 / squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);

	//move him acording to its direction until he hits an obstacle
	switch (ghost->id)
	{
	case 1:
		if (!bitmap.at(x1Quadrant).at((int)ghost->y)){
			ghost->x -= 2 / squareSize;
		}
		else {
			int current = ghost->id;
			do{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;
	case 2:
		if (!bitmap.at(x2Quadrant).at((int)ghost->y)){
			ghost->x += 2 / squareSize;
		}
		else {
			int current = ghost->id;
			do{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;
	case 3:
		if (!bitmap.at((int)ghost->x).at(y1Quadrant)){
			ghost->y -= 2 / squareSize;
		}
		else {
			int current = ghost->id;
			do{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;
	case 4:
		if (!bitmap.at((int)ghost->x).at(y2Quadrant)){
			ghost->y += 2 / squareSize;
		}
		else {
			int current = ghost->id;
			do{
				ghost->id = (rand() % 4) + 1;
			} while (current == (int)ghost->id);
		}
		break;
	default:
		break;
	}

	//printf("%f %f\n", ghost.x, ghost.y);

	glutPostRedisplay();
}

//Method to set the pressed key
void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;

	//The direction the camera looks
	if (key == 'x') viewer[0] -= 0.1;
	if (key == 'X') viewer[0] += 0.1;
	if (key == 'y') viewer[1] -= 0.1;
	if (key == 'Y') viewer[1] += 0.1;
	if (key == 'z') viewer[2] -= 0.1;
	if (key == 'Z') viewer[2] += 0.1;
	printf("viewer : %f, %f, %f\n", viewer[0], viewer[1], viewer[2]);

    printf("ddd");
    
	glutPostRedisplay();
}

//Method to unset the released key
void keyUp(unsigned char key, int x, int y){
	keyStates[key] = false;
}

//Method to reset all the variable necessaries to start the game again
void resetGame(){
	over = false;
	xIncrement = 0;
	yIncrement = 0;
	rotation = 0;

	Blinky.setGhost(10.5, 8.5, 1);
	Inky.setGhost(13.5, 1.5, 2);
	Clyde.setGhost(4.5, 6.5, 3);
	Pinky.setGhost(2.5, 13.5, 4);

	points = 0;
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
	dot.dotInit();
}

//Method to update the movement of the pacman according to the movement keys pressed
void keyOperations(){
	//get current position
	float x = (1.5 + xIncrement) * squareSize;
	float y = (1.5 + yIncrement) * squareSize;
	//update according to keys pressed
	if (keyStates['a']){
		x -= 2;
		int x1Quadrant = (int)((x - 25.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x1Quadrant).at((int)y / squareSize)){
			xIncrement -= 2 / squareSize;
			rotation = 2;
		}
	}
	if (keyStates['d']){
		x += 2;
		int x2Quadrant = (int)((x + 25.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x2Quadrant).at((int)y / squareSize)){
			xIncrement += 2 / squareSize;
			rotation = 0;
		}
	}
	if (keyStates['w']){
		y -= 2;
		int y1Quadrant = (int)((y - 25.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)x / squareSize).at(y1Quadrant)){
			yIncrement -= 2 / squareSize;
			rotation = 3;
		}
	}
	if (keyStates['s']){
		y += 2;
		int y2Quadrant = (int)((y + 25.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)x / squareSize).at(y2Quadrant)){
			yIncrement += 2 / squareSize;
			rotation = 1;
		}
	}
	if (keyStates[' ']){
		if (!replay && over){
			resetGame();
			replay = true;
		}
		else if (replay && over){
			replay = false;
		}
	}
}

//Method to check if the game is over
void gameOver(){
	int pacmanX = (int)(1.5 + xIncrement);
	int pacmanY = (int)(1.5 + yIncrement);

	if (pacmanX == (int)Blinky.x && pacmanY == (int)Blinky.y){
		over = true;
	}
	if (pacmanX == (int)Inky.x && pacmanY == (int)Inky.y){
		over = true;
	}
	if (pacmanX == (int)Clyde.x && pacmanY == (int)Clyde.y){
		over = true;
	}
	if (pacmanX == (int)Pinky.x && pacmanY == (int)Pinky.y){
		over = true;
	}
	if (points == 106){
		over = true;
	}
}

//Method to display the results of the game at the ends
void resultsDisplay(){

	viewerInit();

	if (points == 106){
		//Won
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
	else {
		//Lost
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
}

//Method to display the starting instructions
void welcomeScreen(){
	viewerInit();
	glClearColor(0, 0.2, 0.4, 1.0);
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

//Method to display the screen and its elements
void display(){

	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);

	if (points == 1){
		over = false;
	}
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gameOver();
	if (replay){
		if (!over){
            map.drawFloor();
			map.drawLabyrinth();
			pacman.setPacman(1.5 + xIncrement, 1.5 + yIncrement);
			dot.drawDot(pacman.x * squareSize, pacman.y * squareSize);
			points = dot.getPoint();
			pacman.drawPacman(rotation);

			updateGhost(&Blinky);
			updateGhost(&Inky);
			updateGhost(&Clyde);
			updateGhost(&Pinky);

			Blinky.drawGhost(1.0, 0.0, 0.0); //red
			Inky.drawGhost(0.0, 1.0, 1.0); //cyan
			Clyde.drawGhost(1.0, 0.3, 0.0); //orange
			Pinky.drawGhost(1.0, 0.0, 0.6); //magenta

			Sleep(10);
			playSound(1);
			}
		else {
			playSound(3);
			resultsDisplay();
		}
	}
	else {
		welcomeScreen();
	}
	glutSwapBuffers();
}

//Methdo to reshape the game is the screen size changes
void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glOrtho(0, 750, 750, 0, -750, 750);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Main functions that controls the running of the game
int main(int argc, char** argv){
	//initialize and create the screen
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(500, 50);
	glutCreateWindow("PACMAN - by Patricia Terol");

	//define all the control functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	//run the game
	glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
	return 0;
}

