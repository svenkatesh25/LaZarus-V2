#include "gameboard.h"

/**
 * @brief GameBoard::GameBoard is the default constructor
 * @param parent is the QWidget to link the parent's QWidget to this
 */
GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{

}

/**
 * @brief GameBoard::~GameBoard is the default destructor for the game
 */
GameBoard::~GameBoard()
{

}

/**
 * @brief GameBoard::GameBoard is the main constructor for the gameboard
 * @param row_size is the amount of rows on the gameboard
 * @param col_size is the amount of columns on the gameboard
 * @param parentGame is the Game* that allows for the GameBoard to invoke commands on the Game
 * //Directory
    //1. Initialization and setting of misc internal variables
    //2. Initialization of player1 and related settings
    //3. Manipulates internal timers
    //4. sets the focus to this widget
    //5. Add all necessary images to a QPixmap array
    //5.1 Add all necessary movies to a QMovie array
    //6. Create gbo objects
    //7. Add sprites for gbo objects to layout
    //8. Add sprites for player
    //9. set the layout
 */
GameBoard::GameBoard(int row_size, int col_size, Game* parentGame)
{
    //1. Initialization and setting of misc internal variables
    this->row_size = row_size; //number of rows
    this->col_size = col_size; //number of cols
    this->parentGame = parentGame;
    gbLayout = new QGridLayout();
    numZombies = 0;
    paused = false;
    pauseMenu = new PauseMenu(this);
    fov = 5; //fov is the field of view on every side of player
    toParentGame = "";
    toParentGameBool = false;
    gameOver = false;

    //2. Initialization of player1 and related settings
    player1 = new Player("Frank", row_size/2, col_size/2);      //EDIT PHASE DELTA
    gunFired = false;
    gunFiredReset = -1;
    gunReloading = false;
    gunReloadingReset = -1;
    moved = false;
    movedReset = 0;
    score = 0;

    //3. Manipulates internal timers
    gbTimer = new QTimer();
    multiplier = 2;
    connect(gbTimer, SIGNAL(timeout()), this, SLOT(gbTimerAction()));
    gbTimer->start(750*multiplier);
    secTimer = new QTimer();
    secTimerCounter = 0;
    connect(secTimer, SIGNAL(timeout()), this, SLOT(secTimerAction()));
    secTimer->start(100);

    //4. sets the focus to this widget
    this->setFocus();

    //5. Add all necessary images to a QPixmap array
    /*
    gbImages.push_back(new QPixmap(":/images/Down Arrow.png"));
    gbImages.push_back(new QPixmap(":/images/Left arrow.png"));
    gbImages.push_back(new QPixmap(":/images/Right Arrow.png"));
    gbImages.push_back(new QPixmap(":/images/Up Arrow.png"));
    gbImages.push_back(new QPixmap(":/images/Gray.jpg"));               //used for gray tiles.  4
    gbImages.push_back(new QPixmap(":/images/Dana 1.jpg"));             //used for zombies. 5
    gbImages.push_back(new QPixmap(":/images/Black.jpg"));              //used for blocking tiles. 6.
    gbImages.push_back(new QPixmap(":/images/LaZarus.png"));
    */

    //5.1 Add all necessary movies to a QMovie array
    gbMovies.push_back(new QMovie(":/images/Player Down - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Player Left - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Player Right - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Player Up - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie Down - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie Left - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie Right - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie Up - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Gray Tile - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Wall - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie2 Down - Copy.gif"));//10
    gbMovies.push_back(new QMovie(":/images/Zombie2 Left - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie2 Right - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Zombie2 Up - Copy.gif"));
    gbMovies.push_back(new QMovie(":/images/Item.gif")); //14
        //each Movie must be started, so the code iterates through the vector and performs each command
    for (auto i = gbMovies.begin(); i != gbMovies.end(); i++)
    {
        (*i)->start();
    }

    //6. Create gbo objects
    for (int j = 0; j < col_size; j++)
    {
        for (int i = 0; i < row_size; i++)
        {
            board[i][j] = new GameBoardObject("gray tile", i, j, true);
        }
    }
        //sets gbo objects as walls
    board[9][4]->setPass(false);
    board[9][4]->setSprite("black wall");
    board[9][5]->setPass(false);
    board[9][5]->setSprite("black wall");
    board[9][6]->setPass(false);
    board[9][6]->setSprite("black wall");
    board[9][7]->setPass(false);
    board[9][7]->setSprite("black wall");
    board[8][7]->setPass(false);
    board[8][7]->setSprite("black wall");

    //7. Add sprites for gbo objects to layout
    //column then row
    for (int j = 0; j < col_size; j++)
    {
        for (int i = 0; i < row_size; i++)
        {
            //might need to put in a function to modify i and j for actually inputting them into the layout
            gbLayout->addWidget(interpretSprite(board[i][j]), 20+(20*i), 20*j);
            //qDebug() << j << "and" << i;
        }
    }

    //8. Add sprites for player
    interpretSprite(player1);
    gbLayout->addWidget(player1Label, 20*player1->getgboRow(), 20*player1->getgboCol());

    //Not currently necessary
    //adds sprites for all zombies to gb Layout
    //for (int i = 0; i < numZombies; i++)
    //{
    //    gbLayout->addWidget(interpretSprite(*zlist.begin()), 20+(20*((*zlist.begin())->getgboRow())), 20*((*zlist.begin())->getgboCol()));
    //}

    //9. set the layout
    this->setLayout(gbLayout);
}

//function to interpret KeyPressEvents. Arrow keys move character. WASD turns character. Space shoot a gun at zombies
/**
 * @brief GameBoard::keyPressEvent
 * @param event is the key press event that gets passed to this function to enable the keys
 *
 * Function to interpret key press events, does different things based on the key pressed
 * Key W: Turns the character to face up
 * Key A: Turns the character to face left
 * Key S: Turns the character to face down
 * Key D: Turns the character to face right
 * Key Up Arrow: Moves character up and faces them up
 * Key Left Arrow: Moves character left and faces them left
 * Key Down Arrow: Moves character down and faces them down
 * Key Right Arrow: Moves character right and faces them right
 * Key Space: Shoots gun
 * Key R: Reloads gun
 * Key V: Picks up crowns on ground
 * Key P: Pauses game
 * Function then repaints the board
 */
void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if (paused == false)
    {

        switch (event->key())
        {
        case Qt::Key_W:
            player1->setSprite("Player Up");                                        //look up
            break;
        case Qt::Key_A:
            player1->setSprite("Player Left");                                      //look left
            break;
        case Qt::Key_S:
            player1->setSprite("Player Down");                                      //look down
            break;
        case Qt::Key_D:
            player1->setSprite("Player Right");                                     //look right
            break;
        /**
          Arrow Keys will also set bool moved to true. When moved is
          true, the player cannot move. moved is reset according to a
          variable in player. Currently set at .2 seconds.
          */
        case Qt::Key_Right:
            if (player1->getgboCol() != col_size - 1 && board[player1->getgboRow()][player1->getgboCol() + 1]->getLeftPass())
            {
                if (moved == false)
                {
                    player1->setgboCol(player1->getgboCol()+1);//move to the right
                    moved = true;
                    movedReset = secTimerCounter + (10*player1->getMvmntRate());
                }
            }
            player1->setSprite("Player Right");                                     //look right
            break;
        case Qt::Key_Left:
            if (player1->getgboCol() != 0 && board[player1->getgboRow()][player1->getgboCol() - 1]->getRightPass())
            {
                if (moved == false)
                {
                    player1->setgboCol(player1->getgboCol()-1);                         //move to the left
                    moved = true;
                    movedReset = secTimerCounter + (10*player1->getMvmntRate());
                }
            }
            player1->setSprite("Player Left");                                      //look left
            break;
        case Qt::Key_Up:
            if (player1->getgboRow() != 0 && board[player1->getgboRow()-1][player1->getgboCol()]->getDownPass())
            {
                if (moved == false)
                {
                    player1->setgboRow(player1->getgboRow()-1);                         //move to the up
                    moved = true;
                    movedReset = secTimerCounter + (10*player1->getMvmntRate());
                }
            }
            player1->setSprite("Player Up");                                        //look up
            break;
        case Qt::Key_Down:
            if (player1->getgboRow() != row_size - 1 && board[player1->getgboRow()+1][player1->getgboCol()]->getUpPass())               //EDIT PHASE DELTA
            {
                if (moved == false)
                {
                    player1->setgboRow(player1->getgboRow()+1);                         //move down
                    moved = true;
                    movedReset = secTimerCounter + (10*player1->getMvmntRate());
                }
            }
            player1->setSprite("Player Down");                                      //look down
            break;
            /**
              Similarly, The gun can only be fired according to the fire rate
              of the gun equipped. Currently set at 1 shoot per .1 second.
              Gun can also not be fired while reloading
              */
        case Qt::Key_Space:
            if (gunFired == false && gunReloading == false)
            {
                if (player1->getEquippedGun()->getType() == "pistol")
                {
                    lineShoot();
                }
            }
            break;
        case Qt::Key_P:
            pause();
            break;
        case Qt::Key_R:
            /**
              Reloads the gun as long as the player is not already
              reloading. gunReloading is the bool that controls this .
               gunReloading is also reset according to an internal variable
               of gun. Currently set at 1 second.
              */
            if (gunReloading == false)
            {
                if (player1->reload() == true)
                {
                    gunReloading = true;
                    gunReloadingReset = secTimerCounter + (10*player1->getEquippedGun()->getReloadTime());
                }
            }
            break;
        case Qt::Key_V:
            pickUpItem();
            break;
        default:
            QWidget::keyPressEvent(event);
        }

        //calls the paintEvent to repaint the board
        repaint();
        QCoreApplication::processEvents();
        return;
    }
}

//paint event is called in every repaint
/**
 * @brief GameBoard::paintEvent
 * @param e is the event that this paintEvent is called for
 *
 * function to repaint the board after gbTimerAction finishes or KeyPressEvent finishes.
 * Adds the QLabels to the board again.
    //DIRECTORY
    //1. reinterpret the board and add the labels to the layout
    //2. reinterpret zombies and add to layout
    //3. reinterpret player and add to Layout
    //4. sets the layout
 */
void GameBoard::paintEvent(QPaintEvent *e)
{
    //1. reinterpret the board and add the labels to the layout
    for (int j = 0; j < col_size; j++)
    {
        for (int i = 0; i < row_size; i++)
        {
            gbLayout->addWidget(reinterpretSprite(board[i][j]), 20+(20*i), 20*j);
        }
    }

    //2. reinterpret zombies and add to layout
    //j is here to add the correct QLabel every time
    auto j = zlistLabel.begin();
    for (auto i = zlist.begin(); i != zlist.end(); i++)
    {
        gbLayout->addWidget(*j, 20+(20*((*i)->getgboRow())), 20*((*i)->getgboCol()));
        ++j;
    }

    //3. reinterpret player and add to Layout
    reinterpretSprite(player1);
    gbLayout->addWidget(player1Label, 20+(20*player1->getgboRow()), 20*player1->getgboCol());

    //4. sets the layout
    this->setLayout(gbLayout);
}

/**
 * @brief GameBoard::setPaused
 * @param paused is an internal bool variable that when true stops
 * all key press events and timers
 *
 * function to stop all keypressevents and qtimers. Allows user to stop
 * and restart the game at will
 */
void GameBoard::setPaused(bool paused)
{
    this->paused = paused;
}

/**
 * @brief GameBoard::setDifficulty
 * @param multiplier is an int variable to change how often the gbTimer
 * calls gbTimerAction
 *
 * Function to modify how fast gbTimer calls gbTimer action and to
 * change how score is increased
 *
 * stops timer and restarts under new setting
 */
void GameBoard::setDifficulty(int multiplier)
{
    gbTimer->stop();
    gbTimer->start(500*multiplier);
    this->multiplier = multiplier;
}

/**
 * @brief GameBoard::getToParentGame
 * @return
 *
 * function to return the QString toParentGame. Given Game
 * QStrings to display
 */
QString GameBoard::getToParentGame()
{
    return toParentGame;
}

/**
 * @brief GameBoard::getToParentGameBool
 * @return
 *
 * function to tell Game when it is appropriate to display the
 * QString toParentGame
 */
bool GameBoard::getToParentGameBool()
{
    return toParentGameBool;
}

/**
 * @brief GameBoard::getPlayer1
 * @return
 *
 * function to return the pointer to Player1 so various other objects can
 * manipulate it
 */
Player* GameBoard::getPlayer1()
{
    return player1;
}

/**
 * @brief GameBoard::getGameOver
 * @return
 *
 * function to tell Game when it is GameOver so it can pull up the
 * GameOver menu
 */
bool GameBoard::getGameOver()
{
    return gameOver;
}

/**
 * @brief GameBoard::setToParentGameBool
 * @param toParentGameBool is the bool that tell the Game pointer when
 * to display the QString toParentGame
 *
 * sets toParentGameBool
 */
void GameBoard::setToParentGameBool(bool toParentGameBool)
{
    this->toParentGameBool = toParentGameBool;
}

/**
 * @brief GameBoard::gbTimerAction
 *
 * Function to invoke various GameBoard events such as moving zombies,
 * creating zombies, checking if the Player is dead, regenerating Player health,
 * and giving the Player extra ammo. Repaints when done.
    //DIRECTORY
    //1) Checks if the game is paused
    //2) lets all zombies move
    //3) Sets a max number of zombies on the board and if that is not met, creates a zombie
    //4) if the player dies, closes game window and displays "Game Over"
    //5) since player1 is now definately alive, increment its health if its not at 100
    //6) Gives the player extra ammo at a 1% chance. Used if the player runs out of ammo and wants to survive
    //7) repaint the board after the timer actions
 *
 */
void GameBoard::gbTimerAction()
{

    //1) Checks if the game is paused
    if (paused == false)
    {
        //2) lets all zombies move
        zombieMove();


        //3) Sets a max number of zombies on the board and if that is not met, creates a zombie
        if (numZombies < .4*row_size*col_size)
        {
            createZombie();
        }

        //4) if the player dies, closes game window and displays "Game Over"
        if (!player1->isAlive())
        {
            gameOver = true;
            gbTimer->stop();
            secTimer->stop();
        }

        //5) since player1 is now definately alive, increment its health if its not at 100
        if (player1->getHP() < 100)
        {
            player1->mutHP(1);
        }

        //6) Gives the player extra ammo at a 1% chance. Used if the player runs out of ammo and wants to survive
        if (rand() % 100 < 1)
        {
            player1->pushBackInventory(new Item(".44 Magnum Ammo", 10));
        }

        //7) repaint the board after the timer actions
        repaint();
        QCoreApplication::processEvents();
        return;
    }
}

/**
 * @brief GameBoard::secTimerAction
 *
 * Function to invoke various processes of GameBoard such as
 * reseting bools gunFired, gunReloading, and Moved. Also tells Player
 * if they are out of ammo and updates the score
 *
    //Directory
    //1) checks is paused is true or not. If not, increment action's counter
    //2) Resets gunFired if conditions are met
    //3) Resets gunReloading if conditions are met. Will display a message to the game if so.
    //4) Resets moved if conditions are met
    //5) tells Player they must reload if no ammo left
    //6) updates score
 */
void GameBoard::secTimerAction()
{
    //1) checks is paused is true or not. If not, increment action's counter
    if (paused == false)
    {
    ++secTimerCounter;

    //2) Resets gunFired if conditions are met
    if (gunFired == true && gunFiredReset == secTimerCounter)
    {
        gunFired = false;
    }

    //3) Resets gunReloading if conditions are met. Will display a message to the game if so.
    if (gunReloading == true && gunReloadingReset == secTimerCounter)
    {
        gunReloading = false;
        toParentGame = "Gun Reloaded";
        toParentGameBool = true;
    }

    //4) Resets moved if conditions are met
    if (moved == true && movedReset == secTimerCounter)
    {
        moved = false;
    }

    //5) tells Player they must reload if no ammo left
    if (player1->getEquippedGun()->getCurrentMagazine() == 0 && toParentGameBool == false && toParentGame != "Press 'R' to Reload")
    {
        toParentGame = "Press 'R' to Reload";
        toParentGameBool = true;
    }

    //6) updates score
    if (secTimerCounter % 10 == 0)
    {
        score += 20/multiplier;
    }
    }
}

/**
 * @brief GameBoard::interpretSprite
 * @param gbo is the gameBoardObject who the QLabel is made for
 * @return
 *
 * Function to create a new QLabel for a new GameBoardObject.
 * Creates one specifically for each different type of gameBoardObject.
 *
 * The QLabel to be made is dependent on the std::string Sprite of the
 * gbo passed in
 */
QLabel* GameBoard::interpretSprite(GameBoardObject* gbo)
{
    if (gbo->getSprite() == "gray tile")
    {
        boardLabel[gbo->getgboRow()][gbo->getgboCol()] = new QLabel();
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setScaledContents(true);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMovie(gbMovies[8]);
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }
    else if (gbo->getSprite() == "gold tile")
    {
        boardLabel[gbo->getgboRow()][gbo->getgboCol()] = new QLabel();
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setScaledContents(true);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMovie(gbMovies[14]);
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }
    else if (gbo->getSprite() == "black wall")
    {
        boardLabel[gbo->getgboRow()][gbo->getgboCol()] = new QLabel();
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMovie(gbMovies[9]);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setScaledContents(true);
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }
    else if (gbo->getSprite() == "zombie")
    {
        //is a zombie is interpreted, add a QLabel* to the list of QLabel*
        zlistLabel.push_back(new QLabel());

        //sets options of the last QLabel*
        auto it = zlistLabel.end();
        --it;
        (*it)->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        (*it)->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        (*it)->setMovie(gbMovies[4]);
        (*it)->setScaledContents(true);

        return *it;
    }
    else if (gbo->getSprite() == "zombie2")
    {
        //is a zombie is interpreted, add a QLabel* to the list of QLabel*
        zlistLabel.push_back(new QLabel());

        //sets options of the last QLabel*
        auto it = zlistLabel.end();
        --it;
        (*it)->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        (*it)->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        (*it)->setMovie(gbMovies[10]);
        (*it)->setScaledContents(true);

        return *it;
    }
    else if (gbo->getSprite() == "Player Down")
    {
        player1Label = new QLabel();
        player1Label->setMaximumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMinimumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMovie(gbMovies[0]);
        player1Label->setScaledContents(true);
        return player1Label;
    }
    else if (gbo->getSprite() == "Player Left")
    {
        player1Label = new QLabel();
        player1Label->setMaximumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMinimumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMovie(gbMovies[1]);
        player1Label->setScaledContents(true);
        return player1Label;
    }
    else if (gbo->getSprite() == "Player Right")
    {
        player1Label = new QLabel();
        player1Label->setMaximumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMinimumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMovie(gbMovies[2]);
        player1Label->setScaledContents(true);
        return player1Label;
    }
    else if (gbo->getSprite() == "Player Up")
    {
        player1Label = new QLabel();
        player1Label->setMaximumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMinimumSize(LABEL_SIZE, LABEL_SIZE);
        player1Label->setMovie(gbMovies[3]);
        player1Label->setScaledContents(true);
        return player1Label;
    }
    else
    {
        //just in case, we will always return something
        boardLabel[gbo->getgboRow()][gbo->getgboCol()] = new QLabel();
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setStyleSheet("QLabel { background-color : white; color : white; }");
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }

    //just in case
    return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
}

/**
 * @brief GameBoard::reinterpretSprite
 * @param gbo is the gameBoardObject who's respective QLabel will be updated
 * @return
 *
 * function to reset options on a gameBoardObject. Called by repaint.
 * Doesn't need to do much, but its a good safeguard in case I do need to update certain
 * features of QLabels
 *
 */
QLabel* GameBoard::reinterpretSprite(GameBoardObject* gbo)
{
    if (gbo->getSprite() == "gray tile")
    {
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMovie(gbMovies[8]);

        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }
    else if (gbo->getSprite() == "gold tile")
    {
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMovie(gbMovies[14]);
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }
    else if (gbo->getSprite() == "black wall")
    {
        boardLabel[gbo->getgboRow()][gbo->getgboCol()]->setMovie(gbMovies[9]);
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }
    else if (gbo->getSprite() == "zombie")
    {
        return (*(--zlistLabel.end()));
    }
    else if (gbo->getSprite() == "zombie2")
    {
        return (*(--zlistLabel.end()));
    }
    else if (gbo->getSprite() == "Player Down")
    {
        player1Label->setMovie(gbMovies[0]);

        return player1Label;
    }
    else if (gbo->getSprite() == "Player Left")
    {
        player1Label->setMovie(gbMovies[1]);

        return player1Label;
    }
    else if (gbo->getSprite() == "Player Right")
    {
        player1Label->setMovie(gbMovies[2]);
        return player1Label;
    }
    else if (gbo->getSprite() == "Player Up")
    {
        player1Label->setMovie(gbMovies[3]);

        return player1Label;
    }
    else
    {
        return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
    }

    return boardLabel[gbo->getgboRow()][gbo->getgboCol()];
}

/**
 * @brief GameBoard::getScore
 * @return
 *
 * Function to return internal score variable so it may be displayed
 * in game
 */
int GameBoard::getScore()
{
    return score;
}

/**
 * @brief GameBoard::lineShoot
 *
 * Function to shoot zombies. Shoots in straight line. Will stop once it
 * hits the boundaries, a zombie, or a wall. Can miss zombies and go on
 * to the next one. Accuracy is currently set at 80%.
 *
 * Has to implement similar lines of code four times for the different
 * directions a player can face.
 */
void GameBoard::lineShoot()
{   
    //sets some internal variables
    int xShoot = player1->getgboCol();
    int yShoot = player1->getgboRow();
    int gunAcc = player1->getEquippedGun()->getAccuracy();

    //sets the bool gunFired to true and tells program when it should be reset
    gunFired = true;
    gunFiredReset = secTimerCounter + (10*player1->getEquippedGun()->getFiringRate());

    //if there is no ammo left in the gone, exits function
    if (player1->getEquippedGun()->useAmmo() == false)
    {
        return;
    }

    //if the player is facing down, shoot down
    if (player1->getSprite() == "Player Down")
    {
        //increment xShoot because you can't shoot the square you're on
        yShoot++;
        //finds first zombie to shoot by incrementing xShoot until a zombie is found or end`
        while (yShoot < row_size)      //EDIT PHASE DELTA
        {
            //goes through iterators of zlist and zlistLabel to figure out if the bullet hit a zombie by comparing coordinates
            auto itLabel = zlistLabel.begin();
            for (auto i = zlist.begin(); i != zlist.end();i++)
            {
                int randAcc = rand() % 100;
                //if the bullet hits a zombie, damages zombie, and calls checkZombie, which may kill zombie
                if ((*i)->getgboRow() == yShoot && (*i)->getgboCol() == xShoot && randAcc < gunAcc)
                {
                    (*i)->damaged(player1->getEquippedGun()->getPower());
                    checkZombie(i, itLabel);
                    return;
                }
                ++itLabel;
            }
            //checks if the bullet has hit un impassable object
            if (board[yShoot][xShoot]->getUpPass() == false)
            {
                return;
            }
            yShoot++;
        }
    }

    //if the player is facing left, shoot left
    else if (player1->getSprite() == "Player Left")
    {
        //increment yShoot because you can't shoot the square you're on
        xShoot--;
        //finds first zombie to shoot by decrementing yShoot until a zombie is found or end
        while (xShoot > -1)            //-1 makes sure the bullet does not go into a negative region
        {
            auto itLabel = zlistLabel.begin();
            for (auto i = zlist.begin(); i != zlist.end();i++ )
            {
                int randAcc = rand() % 100;
                //if the bullet hits a zombie, damages zombie, and calls checkZombie, which may kill zombie
                if ((*i)->getgboRow() == yShoot && (*i)->getgboCol() == xShoot && randAcc < gunAcc)
                {
                    (*i)->damaged(player1->getEquippedGun()->getPower());
                    checkZombie(i, itLabel);
                    return;
                }
                ++itLabel;
            }
            //checks if the bullet has hit un impassable object
            if (board[yShoot][xShoot]->getRightPass() == false)
            {
                return;
            }
            xShoot--;
        }
    }

    //if the player is facing right, shoot right
    else if (player1->getSprite() == "Player Right")
    {
        //increment yShoot because you can't shoot the square you're on
        xShoot++;
        //finds first zombie to shoot by decrementing yShoot until a zombie is found or end
        while (xShoot < col_size)          //EDIT PHASE DELTA
        {
            auto itLabel = zlistLabel.begin(); //EDIT ALPHA
            for (auto i = zlist.begin(); i != zlist.end();i++ )
            {
                int randAcc = rand() % 100;
                //if the bullet hits a zombie, damages zombie, and calls checkZombie, which may kill zombie
                if ((*i)->getgboRow() == yShoot && (*i)->getgboCol() == xShoot && randAcc < gunAcc)
                {
                    (*i)->damaged(player1->getEquippedGun()->getPower());
                    checkZombie(i, itLabel);
                    return;
                }
                ++itLabel;
            }
            //checks if the bullet has hit un impassable object
            if (board[yShoot][xShoot]->getLeftPass() == false)
            {
                return;
            }
            xShoot++;
        }
    }

    //if the player is facing up, shoot up
    if (player1->getSprite() == "Player Up")
    {
        //increment yShoot because you can't shoot the square you're on
        yShoot--;
        //finds first zombie to shoot by incrementing xShoot until a zombie is found or end
        while (yShoot > -1)        //-1 makes sure the bullet does not travel into a negative region
        {
            auto itLabel = zlistLabel.begin(); //EDIT ALPHA
            for (auto i = zlist.begin(); i != zlist.end();i++ )
            {
                int randAcc = rand() % 100;
                //if the bullet hits a zombie, damages zombie, and calls checkZombie, which may kill zombie
                if ((*i)->getgboRow() == yShoot && (*i)->getgboCol() == xShoot && randAcc < gunAcc)
                {
                    (*i)->damaged(player1->getEquippedGun()->getPower());
                    checkZombie(i, itLabel);
                    return;
                }
                ++itLabel;
            }
            //checks if the bullet has hit un impassable object
            if (board[yShoot][xShoot]->getDownPass() == false)
            {
                return;
            }
            yShoot--;
        }
    }
}

/**
 * @brief GameBoard::pickUpItem
 *
 * Function for the player to pick up an item if there is a crown in
 * front of them. Adds it to the players inventory and removes it from the ground's
 * Also resets the ground's sprite to "gray tile" so there is no longer
 * a symbol of a crown.
 *
 *
 * Once again, code has 4 similar implmentations based on which way the player faces
 */
void GameBoard::pickUpItem()
{
    int tempRow = player1->getgboRow();
    int tempCol = player1->getgboCol();

    //Once again, code has 4 similar implmentations based on which way the player faces

    if (player1->getSprite() == "Player Down" && tempRow != row_size-1)
    {
        if (board[tempRow+1][tempCol]->getDroppedItems().empty() != true)
        {
           player1->pushBackDroppedItems(board[tempRow+1][tempCol]->getDroppedItems()[0]);
            board[tempRow+1][tempCol]->getDroppedItems().pop_back();
            board[tempRow+1][tempCol]->setSprite("gray tile");
        }
    }

    else if (player1->getSprite() == "Player Left" && tempCol != 0)
    {
        if (board[tempRow][tempCol-1]->getDroppedItems().empty() != true)
        {
            player1->pushBackDroppedItems(board[tempRow][tempCol-1]->getDroppedItems()[0]);
            board[tempRow][tempCol-1]->getDroppedItems().pop_back();
            board[tempRow][tempCol-1]->setSprite("gray tile");
        }
    }

    else if (player1->getSprite() == "Player Right" && tempCol != col_size-1)
    {
        if (board[tempRow][tempCol+1]->getDroppedItems().empty() != true)
        {
            player1->pushBackDroppedItems(board[tempRow][tempCol+1]->getDroppedItems()[0]);
            board[tempRow][tempCol+1]->getDroppedItems().pop_back();
            board[tempRow][tempCol+1]->setSprite("gray tile");
        }
    }

    else if (player1->getSprite() == "Player Up" && tempRow != 0)
    {
        if (board[tempRow-1][tempCol]->getDroppedItems().empty() != true)
        {
            player1->pushBackInventory(board[tempRow-1][tempCol]->getDroppedItems()[0]);
            board[tempRow-1][tempCol]->getDroppedItems().pop_back();
            board[tempRow-1][tempCol]->setSprite("gray tile");
        }
    }
}

//lets all zombies move towards player
/**
 * @brief GameBoard::zombieMove
 *
 * Function that iterates through all zombies to move them.
 * It first checks if the zombie is next to the player.
 * If so, does damage. If not, moves the zombie randomly towards the player.
 *
 * Uses a random int to determine which direction to go.
 */
void GameBoard::zombieMove()
{
    //Iterate through all zombies
    for (auto i = zlist.begin(); i != zlist.end(); i++)
    {
        //if zombie is next to player, spend move damaging player
        if (nextToPlayer(*i))
        {
            player1->damaged((*i)->getDamage());
        }

        //else, move towards player in a random direction
        else
        {
            int randChoice = rand() % 2;
            if ((*i)->getgboRow() == player1->getgboRow())
            {
                randChoice = 0;
            }
            if ((*i)->getgboCol() == player1->getgboCol())
            {
                randChoice = 1;
            }

            //1 means move vertically
            //0 means move horizontally

            //zombie moves up up
            if ((*i)->getgboRow() > player1->getgboRow())
            {
                if (randChoice == 1 && board[(*i)->getgboRow() - 1][(*i)->getgboCol()]->getDownPass())
                {
                    (*i)->setgboRow((*i)->getgboRow() - 1);
                }
            }
            //zombie moves down
            else if ((*i)->getgboRow() < player1->getgboRow())
            {
                if (randChoice == 1 && board[(*i)->getgboRow() + 1][(*i)->getgboCol()]->getUpPass())
                {
                    (*i)->setgboRow((*i)->getgboRow() + 1);
                }
            }

            //zombie moves left
            if ((*i)->getgboCol() > player1->getgboCol())
            {
                if (randChoice == 0 && board[(*i)->getgboRow()][(*i)->getgboCol() - 1]->getRightPass())
                {
                    (*i)->setgboCol((*i)->getgboCol() - 1);
                }
            }
            //zombie moves right
            else if ((*i)->getgboCol() < player1->getgboCol())
            {
                if (randChoice == 0 && board[(*i)->getgboRow()][(*i)->getgboCol() + 1]->getLeftPass())
                {
                    (*i)->setgboCol((*i)->getgboCol() + 1);
                }
            }
        }
    }
}

//create a new Zobie in a random location along boundary
/**
 * @brief GameBoard::createZombie
 *
 * Function to randomly create a zombie along the borders of the map
 */
void GameBoard::createZombie()
{
    int randCreate = rand();
    int randCreate2 = rand();

    //Create zombie along the top row
    if (randCreate % 4 == 0)
    {
        for (int i = 0; i < col_size ; i++)
        {
            if (randCreate2 % col_size == i)
            {
                zlist.push_back(new Zombie(0, i));
            }
        }
    }
    //Create zombie on the right side
    if (randCreate % 4 == 1)
    {
        for (int i = 0; i < row_size ; i++)
        {
            if (randCreate2 % row_size == i)
            {
                zlist.push_back(new Zombie(i, col_size-1));
            }
        }
    }
    //Create zombie on the bottom row
    if (randCreate % 4 == 2)
    {
        for (int i = 0; i < col_size ; i++)
        {
            if (randCreate2 % col_size == i)
            {
                zlist.push_back(new Zombie(row_size-1, i));
            }
        }
    }
    //Create zombie on the left side
    if (randCreate % 4 == 3)
    {
        for (int i = 0; i < row_size ; i++)
        {
            if (randCreate2 % row_size == i)
            {
                 zlist.push_back(new Zombie(i, 0));
            }
        }
    }


    //increase number of zombies and interpret the zombie's sprite
    ++numZombies;
    gbLayout->addWidget(interpretSprite(*(--zlist.end())), 20*((*--zlist.end())->getgboRow()), 20*((*--zlist.end())->getgboCol()));
}

/**
 * @brief GameBoard::nextToPlayer
 * @param z is the zombie
 * @return
 *
 * Function to determine if the zombie is next to the player or on the
 * same space. Returns true if they are. False otherwise.
 */
bool GameBoard::nextToPlayer(Zombie *z)
{
    if (z->getgboRow() == player1->getgboRow() && z->getgboCol() == player1->getgboCol() - 1)
    {
        return true;
    }
    else if (z->getgboRow() == player1->getgboRow() && z->getgboCol() == player1->getgboCol() + 1)
    {
        return true;
    }
    else if (z->getgboCol() == player1->getgboCol() && z->getgboRow() == player1->getgboRow() - 1)
    {
        return true;
    }
    else if (z->getgboCol() == player1->getgboCol() && z->getgboRow() == player1->getgboRow() + 1)
    {
        return true;
    }
    else if (z->getgboRow() == player1->getgboRow() && z->getgboCol() == player1->getgboCol())
    {
        return true;
    }
    else
        return false;
}

//uses iterators to check whether the zombie is alive. If it is dead, remove the iterators from their lists
/**
 * @brief GameBoard::checkZombie
 * @param zlistIT is the iterator pointing to the zombie
 * @param zlistLabelIT is the iterator pointing to the zombie's label
 * @return
 *
 * Check whether zombie is alive. If not, checks if the zombie had
 * an item. If so, drops it on the ground.
 * Next, it hides the zombie's label.
 * Then, it erases the zombie and its label.
 * Finally, it decreases numZombie, updates score, and repaints.
 */
bool GameBoard::checkZombie(std::list<Zombie*>::iterator zlistIT, std::list<QLabel*>::iterator zlistLabelIT)
{
    if (!(*zlistIT)->isAlive())
    {
        //handle zombie's inventory
        //will only drop last item on ground
        if ((*zlistIT)->getInventory().empty() == false)
        {
            board[(*zlistIT)->getgboRow()][(*zlistIT)->getgboCol()]->pushBackDroppedItems(((*zlistIT)->getInventory()[0]));
            board[(*zlistIT)->getgboRow()][(*zlistIT)->getgboCol()]->setSprite("gold tile");
        }

        //hide the Zombie's label, and erase the zombie and its label
        (*zlistLabelIT)->hide();
        zlistIT = zlist.erase(zlistIT);
        zlistLabelIT = zlistLabel.erase(zlistLabelIT);

        //updates score and numZombies
        --numZombies;
        score += 40;

        //repaint board after
        repaint();
        QCoreApplication::processEvents();

        return true;
    }

    return false;
}

/**
 * @brief GameBoard::pause
 *
 * Function to set pause to true and show the pauseMenu which is given
 * focus.
 */
void GameBoard::pause()
{
    paused = true;
    pauseMenu->show();
    pauseMenu->setFocus();
}
