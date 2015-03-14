#include "mainwindow.h"
#include "ui_mainwindow.h"

//Edit2: make the keypressevent and qtimer do something

/**
 * @brief MainWindow::MainWindow
 * @param parent is the function to link MainWindow to another widget
 *
 * Function to create the mainWindow. Sets up srand, stores images,
 * , initializes all the buttons and much more. Only buttons that work are
 * file buttons and instructions. Has a Timer as well.
 *
    //DIRECTORY
    //1. Set up ui for user interface
    //2. Set up srand for varying random values
    //3. Initialize the necessary stored images
    //4. Initialize rsButtons
        //4.1. Set up rsButtons options
    //5. Initialize Files
        //5.1 Set up Files options
    //6. Initialize fileDelete
        //6.1 Set up fileDelete options
    //7. Initialize Logo
    //8. Add everything to a layout
    //9. Create a widget and display the widget. Widget has the layout.
    //10. Implement Timer
    //11. Sets all the options
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //1. Set up ui for user interface
    ui->setupUi(this);

    //2. Set up srand for varying random values
    int seed = static_cast<int>(time(NULL));
    srand(seed);

    //3. Initialize the necessary stored images
    images.push_back(new QPixmap(":/images/biohazard bin.jpg"));
    images.push_back(new QPixmap(":/images/bloodsplatter.jpeg"));
    images.push_back(new QPixmap(":/images/LaZarus.png"));
    images.push_back(new QPixmap(":/images/Zombie fanart.jpg"));


    //4. Initialize rsButtons
    rsButtons.push_back(new QPushButton("Instructions"));
    rsButtons.push_back(new QPushButton("Options"));
    rsButtons.push_back(new QPushButton("Extras"));
    rsButtons.push_back(new QPushButton("Credits"));


    //4.1. Set up rsButtons options
    for (int i = 0; i < rsButtons.size(); i++)
    {
        rsButtons[i]->setStyleSheet("background: white");
    }
        //connects rsButtons
    connect(rsButtons[0], SIGNAL(clicked()), this, SLOT(openInstructions()));

    //5. Initialize Files
    file.push_back(new QPushButton("File 1"));
    file.push_back(new QPushButton("File 2"));
    file.push_back(new QPushButton("File 3"));

    //5.1 Set up Files options
    for (int i = 0; i < file.size(); i++)
    {
        file[i]->setStyleSheet("background: white");
        connect(file[i], SIGNAL(clicked()), this, SLOT(openGameBoard()));
    }

    //6. Initialize fileDelete
        //6.1 Set up fileDelete options
    //7. Initialize Logo
    fileDelete.push_back(new QPushButton(*images[0], "Delete"));
    fileDelete.push_back(new QPushButton(*images[0], "Delete"));
    fileDelete.push_back(new QPushButton(*images[0], "Delete"));

    //6.1 Set up fileDelete options
    for (int i = 0; i < file.size(); i++)
    {
        fileDelete[i]->setStyleSheet("background: white");
        fileDelete[i]->setMaximumWidth(100);
    }

    //7. Initialize Logo
    logo = new QLabel();
    logo->setStyleSheet("background: red");
    logo->setMaximumHeight(100);
    logo->setMaximumWidth(360);
    logo->setPixmap(*images[2]);
    logo->setScaledContents(true);


    //8. Add everything to a layout
    mainWindowLayout = new QGridLayout();
    mainWindowLayout->addWidget(logo, 10, 50);
    for (unsigned int i = 0; i < file.size(); i++)
    {
        int mwRow = 20 + (10*i);
        int mwCol = 40;
        mainWindowLayout->addWidget(file[i], mwRow, mwCol);
    }
    for (unsigned int i = 0; i < fileDelete.size(); i++)
    {
        int mwRow = 20 + (10*i);
        int mwCol = 20;
        mainWindowLayout->addWidget(fileDelete[i], mwRow, mwCol);
    }
    for (unsigned int i = 0; i < rsButtons.size(); i++)
    {
        int mwRow = 20 + (10 * i);
        int mwCol = 100;
        mainWindowLayout->addWidget(rsButtons[i], mwRow, mwCol);
    }

    //9. Create a widget and display the widget. Widget has the layout.
    window = new QWidget();
    window->setMinimumSize(1800, 825);
    window->setMaximumSize(1800, 825);
    window->setStyleSheet("background-image: url(:/images/Zombie fanart.jpg)");
    window->setLayout(mainWindowLayout);

    //10. Implement Timer
    mainTimer = new QTimer(this);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(mainTimerGraphics()));
    mainTimer->start(1000);

    //11. Sets all the options
    this->setWindowTitle("LaZarus");
    this->setFocus();
    this->setCentralWidget(window);
}

/**
 * @brief MainWindow::~MainWindow
 *
 * default destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::keyPressEvent
 * @param event is the event to be handled
 *
 * KeyPressEvent does nothing for now.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        break;
    default:
        QWidget::keyPressEvent(event);
    }

    repaint();
    QCoreApplication::processEvents();
    return;
}

/**
 * @brief MainWindow::openGameBoard
 *
 * Opens a Game which opens a gameboard. shows the game as well.
 * Also gives itself no focus so events go to the game.
 */
void MainWindow::openGameBoard()
{
    this->setFocusPolicy(Qt::NoFocus);
    Game* game = new Game(17,17);
    game->show();
}

/**
 * @brief MainWindow::openInstructions
 *
 * Opens instructions widget detailing how to play the game
 */
void MainWindow::openInstructions()
{
    instructions = new QWidget();
    instructionsLayout = new QGridLayout;
    instructionsLabel = new QLabel("Welcome to LaZarus!\nUse the arrow keys to move\nUse WASD to turn\nUse space to fire\nUse R to reload\nUse P to pause\nUse V to pick up crowns of ammo\n");

    QString stringForLabel2 = "You must defend yourself from zombies! Black spaces are walls. Gray spaces are tiles. Zombies spawn every 1.5 seconds on Medium, \n.75 on Hard, and 3 on Easy. You can set difficulty in the Pause Menu. Zombies will also move just as often as they spawn. Your goal is to \nsurvive for as long as possible. Basic Zombies will do 40 damage, and master zombies will do 60. Basic Zombies take 1 hit to \nkill, while masters take 5. Your gun has an accuracy of 80% and a magazine size of \n8. You have 200 bullets, but can pick up more in the crowns master zombies drop, \nand find some randomly every now and then. You will know you're out of bullets when you try to \nreload and it doesn't tell you you have reloaded. You will also be able to regenerate your health.\n Your health regenerates 1 point every 3/1.5/.75 seconds according to the difficulty. \nYou also have a max fire rate on your gun, and a max movement rate on \nyour player. You cannot shoot while reloading. Your bullets can miss one zombie and hit another.\nFinally, do not hold down arrow keys. Only press them. Also, only the instructions and files button work. The others are for future editions.\nGood luck and have fun!";
    instructionsLabel2 = new QLabel(stringForLabel2);
    instructionsLayout->addWidget(instructionsLabel, 20, 20);
    instructionsLayout->addWidget(instructionsLabel2, 40, 20);
    instructions->setLayout(instructionsLayout);
    instructions->show();
}

/**
 * @brief MainWindow::mainTimerGraphics
 *
 * does nothing for now
 */
void MainWindow::mainTimerGraphics()
{
}
