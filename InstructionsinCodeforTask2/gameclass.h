#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <QTimer>
// CHANGE - Timer is needed for ghost doubling event see https://doc.qt.io/qt-5/qtimerevent.html#QTimerEvent																																											 
#include <QObject>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "pacman.h"
#include "ghost.h"
#include "blinky.h"
#include "pinky.h"
#include "clyde.h"
#include "inky.h"

// CHANGE - Add global variable responsible for game termination																				  
class   GameLoop : public QGraphicsView
{
private:
    QGraphicsScene                          *scene;
    QGraphicsView                           *view;
    QGraphicsPixmapItem                     **map_pix;
    PacMan                                  *pacman;
    Blinky                                  *blinky;
    Pinky                                   *pinky;
    Clyde                                   *clyde;
    Inky                                    *inky;
    int                                     **map_int;
    QTimer                                  *timer_pacman;
    QTimer                                  *timer_blinky;
    QTimer                                  *timer_pinky;
    QTimer                                  *timer_clyde;
    QTimer                                  *timer_inky;
																// CHANGE - Add timer for doubling ghosts	
// CHANGE - Add room for multiple ghosts, at most 128 when the game is over																
public:
                                            GameLoop(char *file_name);
                                            ~GameLoop();
    void                                    ft_write_line_map(int *map, std::string str);
    void                                    ft_roll_game();
    void                                    ft_create_map();
    int                                     ft_check_file_inp(std::string str);
// CHANGE - Add ghost doubling function																													   
};

#endif // GAMECLASS_H
