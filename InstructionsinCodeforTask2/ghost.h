#ifndef GHOST_H
#define GHOST_H

#include "pacman.h"

class   Ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    int             d;
    int             i_pos;
    int             j_pos;
    int             i_x;
    int             i_y;
    int             flag;
    int             i_exit;
    int             j_exit;
    int             direction;
    int             map_path[size_x][size_y];
    int             x_dir[4] = { 1, -1, 0, 0 };
    int             y_dir[4] = { 0, 0, 1, -1 };
    PacMan          *pacman;
    QGraphicsScene  *scene;

    bool            ghostIsDead;
// CHANGE - Add flag to show that this ghost has been killed
public:
    void            ft_clear_map();
    void            ft_restore_path();
    void            ft_set_direction();
    virtual void    ft_find_pacman() = 0;
    virtual void    ft_find_path() = 0;
    int             ft_check_intersect();
    int             ft_set_direction_near();
    int             ft_get_i_pos();
    int             ft_get_j_pos();
    int             ft_check_move(int i_pos, int j_pos);
    virtual void    ft_set_default() = 0;
    virtual void    ft_calculate_point() = 0;
                    Ghost();
public slots:
    virtual void    ft_move_ghost() = 0;
};

#endif // GHOST_H
