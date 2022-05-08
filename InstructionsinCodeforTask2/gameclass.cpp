#include "gameclass.h"

int     GameLoop::ft_check_file_inp(std::string str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '4')
            return (1);
        i++;
    }
    return (0);
}

GameLoop::~GameLoop()
{
    delete scene;
    delete view;
    delete pacman;
    delete pinky;
    delete clyde;
    delete blinky;
    delete inky;
    delete timer_pacman;
    delete timer_blinky;
    delete timer_pinky;
    delete timer_clyde;
    delete timer_inky;
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            delete map_pix[i];
            delete map_int[i];
        }
    }
    delete []map_pix;
    delete []map_int;
// CHANGE - Delete ghosts
    delete timer_doubled_ghosts;
    for (int = 0; i < 128; i++){
        delete blinky[i];
        delete timer_blinky[i];
        delete pinky[i];
        delete timer_pinky[i];
        delete inky[i];
        delete timer_inky[i]
        delete clyde[i];
        delete timer_clyde[i];
    }
}

void    GameLoop::ft_roll_game()
{
    timer_blinky[0] = new QTimer();
    QObject::connect(timer_blinky[0], SIGNAL(timeout()), blinky[0], SLOT(ft_move_ghost()));
    QObject::connect(blinky[0], SIGNAL(deadGhostSignal()), this, SLOT(ghostIsDead()));
    timer_blinky->start(400);

    timer_pinky[0] = new QTimer();
    QObject::connect(timer_pinky, SIGNAL(timeout()), pinky, SLOT(ft_move_ghost()));
    QObject::connect(pinky[0], SIGNAL(deadGhostSignal()), this, SLOT(ghostIsDead()));
    timer_pinky->start(400);

    timer_clyde[0] = new QTimer();
    QObject::connect(timer_clyde, SIGNAL(timeout()), clyde, SLOT(ft_move_ghost()));
    QObject::connect(clyde[0], SIGNAL(deadGhostSignal()), this, SLOT(ghostIsDead()));
    timer_clyde->start(400);

    timer_inky[0] = new QTimer();
    QObject::connect(timer_inky, SIGNAL(timeout()), inky, SLOT(ft_move_ghost()));
    QObject::connect(inky[0], SIGNAL(deadGhostSignal()), this, SLOT(ghostIsDead()));
    timer_inky->start(400);

    timer_pacman = new QTimer();
    QObject::connect(timer_pacman, SIGNAL(timeout()), pacman, SLOT(ft_move()));
    timer_pacman->start(300);
    timer_clyde->start(400);

    timer_doubled_ghosts = new QTimer();
    QObject::connect(timer_doubled_ghosts, SIGNAL(timeout()), this, SLOT(ghostDouble()));
    timer_doubled_ghosts->start(30000);
    
    for (int i = 1; i < 128; i++){
        blinky[i] = NULL;
        timer_blinky[i] = NULL;
        pinky[i] = NULL;
        timer_pinky[i] = NULL;
        inky[i] = NULL;
        timer_inky[i] = NULL;
        clyde[i] = NULL;
        timer_clyde[i] = NULL;
    }
    
    
// CHANGE - Setup all slots excluding the ones in 0 position to NULL and assign slots in 0 position to corresponding individual objects
}

void    GameLoop::ft_create_map()
{
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            if (map_int[i][j] == 1)
            {
                map_pix[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
            if (map_int[i][j] == 3)
            {
                map_pix[i][j].setPixmap(QPixmap(":/pics/ball.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
            if (map_int[i][j] == 4)
            {
                map_pix[i][j].setPixmap(QPixmap(":/pics/energizer.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
        }
    }
}

void    GameLoop::ft_write_line_map(int *map, std::string str)
{
    for (int i = 0; i < size_y; i++)
        map[i] = str[i] - '0';
}
GameLoop::GameLoop(char *file_name)
{
    std::ifstream   input;
    std::string     temp;
    int             nb;

    map_int = new int *[size_x];
    map_pix = new QGraphicsPixmapItem *[size_x];
    for (int i = 0; i < size_x; i++)
    {
        map_int[i] = new int[size_y];
        map_pix[i] = new QGraphicsPixmapItem[size_y];
    }

    input.open(file_name);
    if (input.is_open())
    {
        nb = 0;
        while (std::getline(input, temp))
        {
            if (temp.length() != size_y)
            {
                std::cout << "File error.\n";
                exit(0);
            }
            if (ft_check_file_inp(temp))
            {
                std::cout << "File error.\n";
                exit(0);
            }
            ft_write_line_map(map_int[nb], temp);
            nb++;
        }
        if (nb != size_x)
        {
            std::cout << "File error.\n";
            exit(0);
        }
        input.close();
    }
    else
    {
        std::cout << "File missing: " << file_name << ".\n";
        exit(0);
    }
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    this->setScene(scene);
    ft_create_map();
    this->setStyleSheet("background-color:black;");
    pacman = new PacMan(map_int, map_pix, scene);
    pacman->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    pacman->setFocus();
    blinky = new Blinky(scene, map_int, pacman);
    pinky = new Pinky(scene, map_int, pacman);
    clyde = new Clyde(scene, map_int, pacman);
    inky = new Inky(scene, map_int, pacman);
    blinky->ft_set_friends(pinky, clyde, inky);
    pinky->ft_set_friends(blinky, clyde, inky);
    clyde->ft_set_friends(blinky, pinky, inky);
    inky->ft_set_friends(blinky, pinky, clyde);
}

// CHANGE - double the number of survived ghosts
void    GameLoop::ghostDouble()
{
  int numBlinkys = 0;
  int numPinkys = 0;
  int numInkys = 0;
  int numClydes = 0;
  for (int i = 0; i < 128; i++)
  {
    if (blinky[i] != NULL && !blinky[i]->GetGhostIsDead())
      numBlinkys++;
    if (pinky[i] != NULL && !pinky[i]->GetGhostIsDead())
      numPinkys++;
    if (inky[i] != NULL && !inky[i]->GetGhostIsDead())
      numInkys++;
    if (clyde[i] != NULL && !clyde[i]->GetGhostIsDead())
      numClydes++;
  }

  if (numBlinkys > 64 || numPinkys > 64 || numInkys > 64 || numClydes > 64 || (numBlinkys + numPinkys + numInkys + numClydes) > 128)
  {
    ft_set_is_game_lost(true);
  }
  else
  {
    auto numBlinkysLeft = numBlinkys;
    auto numPinkysLeft = numPinkys;
    auto numInkysLeft = numInkys;
    auto numClydesLeft = numClydes;
    for (int i = 0; i < 128; i++)
    {
      if (numBlinkysLeft <= 0)
        break;
      if (blinky[i] == NULL || blinky[i]->GetGhostIsDead())
      {
        if (timer_blinky[i] != NULL)
        {
          timer_blinky[i]->stop();
        }

        timer_blinky[i] = new QTimer();
        blinky[i] = new Blinky(scene, map_int, pacman);
        QObject::connect(timer_blinky[i], SIGNAL(timeout()), blinky[i], SLOT(ft_move_ghost()));
        QObject::connect(blinky[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostIsDead()));
        timer_blinky[i]->start(400);
        numBlinkysLeft--;
      }
    }
    for (int i = 0; i < 128; i++)
    {
      if (numPinkysLeft <= 0)
        break;
      if (pinky[i] == NULL || pinky[i]->GetGhostIsDead())
      {
        if (timer_pinky[i] != NULL)
        {
          timer_pinky[i]->stop();
        }

        timer_pinky[i] = new QTimer();
        pinky[i] = new Pinky(scene, map_int, pacman);
        QObject::connect(timer_pinky[i], SIGNAL(timeout()), pinky[i], SLOT(ft_move_ghost()));
        QObject::connect(pinky[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostIsDead()));
        timer_pinky[i]->start(400);
        numPinkysLeft--;
      }
    }
    for (int i = 0; i < 128; i++)
    {
      if (numInkysLeft <= 0)
        break;
      if (inky[i] == NULL || inky[i]->GetGhostIsDead())
      {
        if (timer_inky[i] != NULL)
        {
          timer_inky[i]->stop();
        }

        timer_inky[i] = new QTimer();
        inky[i] = new Inky(scene, map_int, pacman);
        QObject::connect(timer_inky[i], SIGNAL(timeout()), inky[i], SLOT(ft_move_ghost()));
        QObject::connect(inky[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
        timer_inky[i]->start(400);
        numInkysLeft--;
      }
    }
    for (int i = 0; i < 128; i++)
    {
      if (numClydesLeft <= 0)
        break;
      if (clyde[i] == NULL || clyde[i]->GetGhostIsDead())
      {
        if (timer_clyde[i] != NULL)
        {
          timer_clyde[i]->stop();
        }

        timer_clyde[i] = new QTimer();
        clyde[i] = new Clyde(scene, map_int, pacman);
        QObject::connect(timer_clyde[i], SIGNAL(timeout()), clyde[i], SLOT(ft_move_ghost()));
        QObject::connect(clyde[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
        timer_clyde[i]->start(400);
        numClydesLeft--;
      }
    }
  }
  
}

void GameLoop::ghostDied()
{
  
}