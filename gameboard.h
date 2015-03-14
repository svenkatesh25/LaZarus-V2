#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "doclib.h"
#include "gameboardobject.h"
#include "objectdirectory.h"
#include "player.h"
#include "zombie.h"
#include "pausemenu.h"
#include "game.h"

#include <QWidget>


/**
 * PauseMenu and Game are classes to be declared beforehand
 */
class PauseMenu;
class Game;

/**
 * @brief The GameBoard class
 * GameBoard is the class that handles the game itself. It spawn a player in the middle.
 * and spawns zombies every 1.5 seconds on the borders. It also handles all the keypress
 * events and killing zombies. The gameboard is made of various QLabels which are repainted
 * whenever a key is pressed or every 1.5 seconds.
 */
class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

    GameBoard(int row_size, int col_size, Game* parentGame);          //initializes GameBoard of a certain size

    void keyPressEvent(QKeyEvent *event);           //overloaded KeyPress function registers when you press certain keys
    void paintEvent(QPaintEvent *e);                //overloaded paintEvent function is called when repaint is called

    void setPaused(bool paused);
    void setDifficulty(int multiplier);

    QString getToParentGame();
    bool getToParentGameBool();
    Player* getPlayer1();
    int getScore();
    bool getGameOver();

    void setToParentGameBool(bool toParentGameBool);

signals:

public slots:
    void gbTimerAction();                           //timer action keep strack of several time related functions of this class
    void secTimerAction();

private:
    //internal function functions
    QLabel* interpretSprite(GameBoardObject* gbo);
    QLabel* reinterpretSprite(GameBoardObject* gbo); //doesn't create a new QLabel everytime

    //parentGame variables
    Game* parentGame;
    QString toParentGame;
    bool toParentGameBool;

    //board variables
    QLabel* gbLogo;
    QGridLayout* gbLogoLayout;
    GameBoardObject* board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    QLabel* boardLabel[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    //std::vector<QPixmap*> gbImages;
    std::vector<QMovie*> gbMovies;

    //player variables
    Player* player1;
    QLabel* player1Label;
    int score;
    void lineShoot();
    bool gunFired;
    int gunFiredReset;
    bool gunReloading;
    int gunReloadingReset;
    bool moved;
    int movedReset;
    void pickUpItem();

    //zombie variables
    //list data structures to hold zombies and their appropriate QLabel
    std::list<Zombie*> zlist;
    std::list<QLabel*> zlistLabel;
    int numZombies;
    void zombieMove();
    void createZombie();
    bool nextToPlayer(Zombie* z);
    bool checkZombie(std::list<Zombie*>::iterator zlistIT, std::list<QLabel*>::iterator zlistLabelIT);

    int row_size;
    int col_size;
    //so, col_size is the number of columns, and row_size is the number of rows
    int fov; //Field of View

    //reference objects
    QGridLayout* gbLayout;
    QTimer* gbTimer;
    int multiplier;
    QTimer* secTimer;
    int secTimerCounter;

    //variables associated with dying
    bool gameOver;

    //variables and functions associated with pausing
    void pause();
    bool paused;
    PauseMenu* pauseMenu;
};

#endif // GAMEBOARD_H
