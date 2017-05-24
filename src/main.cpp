/*
	3D & 2D Pacman
	Original: https://github.com/patriciateroltolsa/Pacman
	Updates: https://github.com/ekdud014/OSS_pacman
	Original Copyright (C) Patricia Terol
	Updates Copyright (C) Yeji Na, Dayoung Park, Sojeong Lee, Seungyeon Lee
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
bool replay = false; //check if starts a new game
bool over = true; //check for the game to be over
float squareSize = 50.0; //size of one square on the game
float xIncrement = 0; // x movement on pacman
float yIncrement = 0; // y movement on pacman
int rotation = 0; // orientation of pacman
float angle = 0; // the angle(degree) of pacman's mouth
float angle_Increment = 3;

float xx=-20, yy=-3.2, zz=-30;

bool callOnce = false; // call function once

vector<vector<bool>> bitmap; // 2d image of which squares are blocked and which are clear for pacman to move in
bool* keyStates = new bool[256]; // record of all keys pressed
int points = 0; // total points collected
GLdouble viewer[] = { 0, 0, 1 }; // initial viewer location

void viewerInit()
{
    viewer[0] = -30;
    viewer[1] = -5.0;
    viewer[2] = -30;
    xx=-21, yy=-3.2, zz=-30;
}

//Initializes the game with the appropiate information
void init()
{
    //clear screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    
    //reset all keys
    for (int i = 0; i < 256; i++)
    {
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
void updateGhost(Ghost *ghost)
{
    //find the current position of the monster
    int x1Quadrant = (int)((ghost->x - (2 / squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    int x2Quadrant = (int)((ghost->x + (2 / squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    int y1Quadrant = (int)((ghost->y - (2 / squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    int y2Quadrant = (int)((ghost->y + (2 / squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    
    //move him acording to its direction until he hits an obstacle
    switch (ghost->id)
    {
        case 1:
            if (!bitmap.at(x1Quadrant).at((int)ghost->y))
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
            if (!bitmap.at(x2Quadrant).at((int)ghost->y))
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
            if (!bitmap.at((int)ghost->x).at(y1Quadrant))
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
            if (!bitmap.at((int)ghost->x).at(y2Quadrant))
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
    
    Blinky.setGhost(10.5, 8.5, 1);
    Inky.setGhost(13.5, 1.5, 2);
    Clyde.setGhost(4.5, 6.5, 3);
    Pinky.setGhost(2.5, 13.5, 4);
    
    points = 0;
    dot.setPoint(0);
    
    for (int i = 0; i < 256; i++)
    {
        keyStates[i] = false;
    }
    
    dot.dotInit();
}

//Method to update the movement of the pacman according to the movement keys pressed
void keyOperations()
{
    //get current position
    float x = (1.5 + xIncrement) * squareSize;
    float y = (1.5 + yIncrement) * squareSize;
    
    //update according to keys pressed
    if (keyStates['a'])
    {
        x -= 2;
        int x1Quadrant = (int)((x - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at(x1Quadrant).at((int)y / squareSize))
        {
            xIncrement -= 2 / squareSize;
            rotation = 2;
            
            //camera direction set
            zz=viewer[2];
            xx = viewer[0] - 10;
            
            //camera location set
            viewer[0] -= 0.2;
            xx -=0.2;
        }
    }
    if (keyStates['d'])
    {
        x += 2;
        int x2Quadrant = (int)((x + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at(x2Quadrant).at((int)y / squareSize))
        {
            xIncrement += 2 / squareSize;
            rotation = 0;
            
            //camera direction set
            zz=viewer[2];
            xx = viewer[0] +10;
            
            //camera location set
            viewer[0] += 0.2;
            xx +=0.2;

        }
    }
    if (keyStates['w'])
    {
        y -= 2;
        int y1Quadrant = (int)((y - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at((int)x / squareSize).at(y1Quadrant))
        {
            yIncrement -= 2 / squareSize;
            rotation = 3;
            
            //camera direction set
            zz=viewer[2] - 10;
            xx = viewer[0];
            
            //camera location set
            viewer[2] -= 0.2;
            zz -=0.2;
        }
    }
    if (keyStates['s'])
    {
        y += 2;
        int y2Quadrant = (int)((y + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at((int)x / squareSize).at(y2Quadrant))
        {
            yIncrement += 2 / squareSize;
            rotation = 1;
            
            //camera direction set
            zz=viewer[2] + 10;
            xx = viewer[0];
            
            //camera location set
            viewer[2] += 0.2;
            zz +=0.2;
        }
    }
    if (keyStates[' '])
    {
        if (!replay && over)
        {
            resetGame();
            replay = true;
        }
        else if (replay && over)
        {
            replay = false; 
        }
    }
}

//Method to check if the game is over
void gameOver()
{
    int pacmanX = (int)(1.5 + xIncrement);
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
    if (points == 106)
    {
        over = true;
    }
    if (!over)
    {
        callOnce = false;
    }
}

//Method to display the results of the game at the ends
void resultsDisplay()
{
    viewerInit();
    
    if (!callOnce)
    {
        setSoundInit();
        callOnce = true;
    }
    
    if (points == 106)
    {
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
    else
    {
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
void welcomeScreen()
{
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
void display()
{
    glViewport(0, 0, ww/2, hh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5, 5, 5, -5, 2, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Left screen(3D and first person view)
    glLoadIdentity();
    gluLookAt(viewer[0], viewer[1], viewer[2], xx, yy, zz, 0, 1, 0);
    
    if (points == 1)
    {
        over = false;
    }
    
    keyOperations();
    
    gameOver();
    
    //Increaseing the degree of pacman's mouth
    angle += angle_Increment; //angle's range is 0~45degree
    if (angle > 45) //change the signal of angle_Increment
    {
        angle_Increment = -angle_Increment;
    }
    else if (angle < 0)
    {
        angle_Increment = -angle_Increment;
    }
    
    //call the functions to draw
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
            
            glPopMatrix();
            //Sleep(10);
            playSound(1);
        }
        else
        {
            glLoadIdentity();
            gluLookAt(0, 0, 10, 0.7, 0, 0, 0, 1, 0);
            glPushMatrix();
            glScalef(0.1, 0.1, 0.1);
            glTranslated(-75, -350, -1);
            playSound(3);
            resultsDisplay();
            glPopMatrix();
        }
    }
    else
    {
        glLoadIdentity();
        gluLookAt(0, 0, 10, 2, 0, 0, 0, 1, 0);
        glPushMatrix();
        glScalef(0.1, 0.1, 0.1);
        glTranslated(-50, -300, -1);
        welcomeScreen();
        glPopMatrix();
    }
    
    //Right screen(2D(Actually draw 3D, so I think it may be modified) and third person view)
    glPushMatrix(); //Save root
    
    glViewport(ww/2, 0, ww, hh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 750 * 2, 750, 0, -750, 750);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); //Fixed the viewer
    
    if (points == 1)
    {
        over = false;
    }
    
    keyOperations();
    
    gameOver();
    
    
    if (replay)
    {
        if (!over)
        {
            map.drawFloor();
            map.drawLabyrinth();
            pacman.setPacman(1.5 + xIncrement, 1.5 + yIncrement, angle);
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
            
            //Sleep(10);
            playSound(1);
        }
    }
    
    
    glPopMatrix(); //Go to Root
    
    glutSwapBuffers();
}

//Methdo to reshape the game is the screen size changes
void reshape(int w, int h)
{
    ww = w;
    hh = h;
}


//Main functions that controls the running of the game
int main(int argc, char** argv)
{
    //initialize and create the screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750 * 2, 750);
    glutInitWindowPosition(0, 0);
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
