#include "game.h"

/**
 * @brief Game::Game is the Game class's default constructor.
 * @param parent sets a QWidget* for the widget to link itself.
 */
Game::Game(QWidget *parent) : QMainWindow(parent)
{

}

/**
 * @brief Game::~Game is the Game class's default destructor.
 */
Game::~Game()
{

}

/**
 * @brief Game::Game
 * @param row_size details the row size of the GameBoard internal variable
 * @param col_size details the column size of the GameBoard internal variable
 *
 * This constructor makes all the dock widgets, initializes their internal widgts, and sets
 * the gameBoard as the central widget. The top dock widget has a QLabel for the logo. The right dock widget
 * has a health bar and a score label. Finally, the bottom dock widget has a message box for the gameboard to
 * display important messages
 *
 *
    //DIRECTORY
    //1) sets internal size variables
    //2) Initialize the dock widgets
    //3) Initialize the widgets and some of their settings
    //4) Initialize the GridLayouts
    //5) Initialize large parts of hud
    //6) adds Images to gameImages
    //7) edit settings of gameLogo
    //8) adds widgets to DockWidget layouts
    //9) sets the Layouts to their widgets
    //10) sets the widges to the dockwidgets
    //11) sets focus to gameboard
    //12) sets the Timer
    //13) adds the large parts of hud to the mainwindow
 */
Game::Game(int row_size, int col_size)
{
    //1) sets internal size variables
    this->setMaximumSize(1315,1250);
    this->setMinimumSize(1315,1250);

    //2) Initialize the dock widgets
    bottomMenu = new QDockWidget("Messages");
    rightMenu = new QDockWidget("Stats");
    topMenu = new QDockWidget("LaZarus");

    //3) initialize the widgets and chance some of their settings
    bottomWidget = new QWidget();
    bottomWidget->setMaximumSize(1315,100);
    bottomWidget->setMinimumSize(1315,100);
    rightWidget = new QWidget();
    topWidget = new QWidget();
    topWidget->setMaximumSize(1315, 150);
    topWidget->setMinimumSize(1315, 150);

    //4) Initialize the GridLayouts
    bottomLayout = new QGridLayout();
    rightLayout = new QGridLayout();
    topLayout = new QGridLayout();

    //5) Initialize large parts of hud
    gameBoard = new GameBoard(row_size, col_size, this);
    gameLogo = new QLabel();
    textBox = new QTextEdit();
    textBox->setFocusPolicy(Qt::NoFocus);
    QString testString = "Hello LaZarus!";
    textBox->setText(testString);
    healthLabel = new QLabel("HP");
    healthBar = new QProgressBar();
    healthBar->setFocusPolicy(Qt::NoFocus);
    healthBar->setRange(0, this->gameBoard->getPlayer1()->getHP());
    healthBar->setValue(this->gameBoard->getPlayer1()->getHP());
    healthBar->setMaximumSize(300, 50);
    healthBar->setMinimumSize(300, 50);
    scoreLabel = new QLabel("Score: ");
    scoreText = new QLabel("0");

    //6) adds Images to gameImages
    gameImages.push_back(new QPixmap(":/images/LaZarus.png"));

    //7) edit settings of gameLogo
    gameLogo->setPixmap(*gameImages[0]);
    gameLogo->setScaledContents(true);
    gameLogo->setMaximumSize(500,100);
    gameLogo->setMinimumSize(500,100);

    //8) adds widgets to DockWidget layouts
    bottomLayout->addWidget(textBox, 0, 0);
    rightLayout->addWidget(healthBar, 0, 20);
    rightLayout->addWidget(healthLabel, 0, 15);
    rightLayout->addWidget(scoreText, 20, 20);
    rightLayout->addWidget(scoreLabel, 20, 15);
    topLayout->addWidget(gameLogo, 0, 0);

    //9) sets the Layouts to their widgets
    bottomWidget->setLayout(bottomLayout);
    rightWidget->setLayout(rightLayout);
    topWidget->setLayout(topLayout);

    //10) sets the widges to the dockwidgets
    bottomMenu->setWidget(bottomWidget);
    rightMenu->setWidget(rightWidget);
    topMenu->setWidget(topWidget);

    //11) sets focus to gameboard
    gameBoard->setFocusPolicy(Qt::StrongFocus);
    gameBoard->setFocus();

    //12) sets the Timer
    gameTimer = new QTimer();
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerAction()));
    gameTimer->start(100);

    //13) adds the large parts of hud to the mainwindow
    this->setCentralWidget(gameBoard);
    this->addDockWidget(Qt::TopDockWidgetArea, topMenu);
    this->addDockWidget(Qt::RightDockWidgetArea, rightMenu);
    this->addDockWidget(Qt::BottomDockWidgetArea, bottomMenu);
    this->show();
}

/**
 * @brief Game::gameTimerAction managed the gameboard and the reactions
 * in the dockwidgets.
 *
 * First it checks if the gameBoard has a message for the messageBox
 * Secondly, it sets the healthBar to have the value of the player's health
 * Thirdly, it updates the score
 * Finally, it checks if the game is over and if so it will create a GameOver Widget and and close
 *      this window
 */
void Game::gameTimerAction()
{
    //checks if the gameBoard has a message for the
    if (gameBoard->getToParentGameBool() == true)
    {
        textBox->append(gameBoard->getToParentGame());
        textBox->moveCursor(QTextCursor::End);

        gameBoard->setToParentGameBool(false);
    }

    //updates score and healthbar
    healthBar->setValue(this->gameBoard->getPlayer1()->getHP());
    scoreText->setNum(this->gameBoard->getScore());

    //checks if the gameBoard is over and if so displays a GameOver widget
    if (gameBoard->getGameOver() == true)
    {
        healthBar->setValue(0);
        gameOverWindow = new QWidget();
        gameOverWindowText = new QLabel("Game Over! Score: ");
        gameOverWindowScore = new QLabel();
        gameOverWindowScore->setNum(this->gameBoard->getScore());
        gameOverWindowLayout = new QGridLayout();
        gameOverWindowLayout->addWidget(gameOverWindowText, 20, 20);
        gameOverWindowLayout->addWidget(gameOverWindowScore, 20, 25);
        gameOverWindow->setLayout(gameOverWindowLayout);
        gameOverWindow->setWindowTitle("LaZarus");
        this->close();
        this->gameTimer->stop();
        gameOverWindow->show();
    }
}
