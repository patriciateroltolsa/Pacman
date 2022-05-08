#include "pacman.h"
#include <iostream>

void    PacMan::ft_update_scene()
{
    static int flag;

    if (points == 50)
    {
        map_int[15][9] = 6;
        if (!flag)
        {
            map_pix[15][9].setPixmap(QPixmap(":/pics/cherries.png"));
            scene->addItem(&(map_pix[15][9]));
            flag = 1;
        }
    }
    if (map_int[i_pos][j_pos] == 6)
    {
        score += 200;
        map_int[i_pos][j_pos] = 0;
        scene->removeItem(&(map_pix[15][9]));
        flag = 0;
    }
    if (map_int[i_pos][j_pos] == 3)
    {
        map_int[i_pos][j_pos] = 0;
        score += 10;
        points++;
        scene->removeItem(&(map_pix[i_pos][j_pos]));
    }
    if (map_int[i_pos][j_pos] == 4)
    {
        scared = 1;
        map_int[i_pos][j_pos] = 0;
        scene->removeItem(&(map_pix[i_pos][j_pos]));
    }
}

int     PacMan::ft_scared_state()
{
    return (scared);
}

void    PacMan::ft_set_scared()
{
    scared = !scared;
}

int     PacMan::ft_get_score()
{
    return (score);
}

void    PacMan::ft_print_score()
{
    text->setDefaultTextColor(0x00ffffff);
    text->setFont(QFont("times", 15));
    text->setPlainText("SCORE: " + QString::number(score) + "\t\tLIVES: " + QString::number(lives));
    text->setPos(10 , HEIGHT - 30);
}

void    PacMan::ft_incr_score()
{
    score += 100;
}

void    PacMan::ft_set_lives()
{
// CHANGE - Pacman is immortal
    lives--;
}

PacMan::PacMan(int **map_i, QGraphicsPixmapItem **map_p, QGraphicsScene *sc)
{
    i_pos = 15;
    score = 0;
    points = 0;
    j_pos = 9;
    counter = 0;
    direction = 0;
    map_int = map_i;
    map_pix = map_p;
    scene = sc;
    scared = 0;
    lives = 3;
    text = new QGraphicsTextItem();
    message = new QGraphicsTextItem();
    this->setPixmap(QPixmap(":/pics/pacman_left.png"));
    this->setPos(j_pos * 32, i_pos * 32);
    scene->addItem(this);
    scene->addItem(text);
    ft_print_score();
}

int     PacMan::ft_get_direction()
{
    return (direction);
}

void    PacMan::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
     {
        this->direction = 3;
        this->setPixmap(QPixmap(":/pics/pacman_left.png"));
     }
     if (event->key() == Qt::Key_Right)
     {
        this->direction = 4;
         this->setPixmap(QPixmap(":/pics/pacman_right.png"));
     }
     if (event->key() == Qt::Key_Down)
     {
        this->direction = 2;
        this->setPixmap(QPixmap(":/pics/pacman_down.png"));
     }
     if (event->key() == Qt::Key_Up)
     {
        this->direction = 1;
        this->setPixmap(QPixmap(":/pics/pacman_up.png"));
     }
}

int     PacMan::ft_get_point()
{
    return (points);
}

void    PacMan::ft_move()
{   
    static int flag;

    ft_print_score();
    if (points == 149 && !flag)
    {
        message->setDefaultTextColor(0x00ff00ff);
        message->setFont(QFont("times", 40));
        message->setPlainText("YOU WIN");
        message->setPos(60, HEIGHT / 2 - 30);
        scene->addItem(message);
        scene->removeItem(this);
        scene->removeItem(text);
        flag = 1;
    }
    if (lives <= 0 && !flag)
    {
        message->setDefaultTextColor(0x00ff00ff);
        message->setFont(QFont("times", 60));
        message->setPlainText("YOU LOST");
        message->setPos(80, HEIGHT / 2);
        scene->addItem(message);
        scene->removeItem(this);
        scene->removeItem(text);
        flag = 1;
    }
    ft_update_scene();
    if (direction == 1)
    {
        if (i_pos == 0)
        {
           if (ft_check_move(size_x - 1, j_pos))
               i_pos = size_x - 1;
        }
        else
            if (ft_check_move(i_pos - 1, j_pos))
                i_pos--;
    }
    if (direction == 2)
    {
        if (i_pos == size_x - 1)
        {
            if (ft_check_move(0, j_pos))
                i_pos = 0;
        }
        else
            if (ft_check_move(i_pos + 1, j_pos))
                i_pos++;
    }
    if (direction == 3)
    {
        if (j_pos == 0)
        {
            if (ft_check_move(i_pos, size_y - 1))
                j_pos = size_y - 1;
        }
        else
            if (ft_check_move(i_pos, j_pos - 1))
                j_pos--;
    }
    if (direction == 4)
    {
        if (j_pos == size_y - 1)
        {
            if (ft_check_move(i_pos, 0))
                j_pos = 0;
        }
        else
            if (ft_check_move(i_pos, j_pos + 1))
                j_pos++;
    }
    this->setPos(j_pos * 32, i_pos * 32);
}

int     PacMan::ft_get_pacman_i(void)
{
    return (i_pos);
}

int     PacMan::ft_get_pacman_j(void)
{
    return (j_pos);
}

int     PacMan::ft_check_move(int i_pos, int j_pos)
{
    if (map_int[i_pos][j_pos] == 1)
        return (0);
    return (1);
}

void    PacMan::ft_set_defaut()
{
    i_pos = 15;
    j_pos = 9;

    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}
