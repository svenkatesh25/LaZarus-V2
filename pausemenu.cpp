#include "pausemenu.h"

/**
 * @brief PauseMenu::~PauseMenu
 *
 * default destructor for PauseMenu
 */
PauseMenu::~PauseMenu()
{
}

/**
 * @brief PauseMenu::PauseMenu
 * @param gameboard is the gameboard PauseMenu pauses
 *
 * Constructor for PauseMenu. Sets the title and size first.
 * Secondly, it creates a layout, sets it gameboard, and makes its buttons.
 * Next it connects all its buttons and displays them.
 *
 * Difficulty buttons will change the gbTimer frequency in gameboard
 *
 */
PauseMenu::PauseMenu(GameBoard* gameboard)
{
    this->setWindowTitle("Pause Menu");
    this->setMaximumSize(500,500);
    this->setMinimumSize(500,500);

    this->gameboard = gameboard;
    pauseLayout = new QGridLayout;
    resume = new QPushButton("Resume");
    resume->setStyleSheet("border-image: /images/biohazard bin.jpg");

    QObject::connect(resume, SIGNAL(clicked()), this, SLOT(close()));
    pauseLayout->addWidget(resume, 20, 20);

    difficultyGroup = new QButtonGroup();
    difficulty[0] = new QRadioButton("Easy");
    QObject::connect(difficulty[0], SIGNAL(clicked()), this, SLOT(setDifficulty0()));
    difficulty[1] = new QRadioButton("Medium");
    difficulty[1]->setChecked(true);
    QObject::connect(difficulty[1], SIGNAL(clicked()), this, SLOT(setDifficulty1()));
    difficulty[2] = new QRadioButton("Hard");
    QObject::connect(difficulty[2], SIGNAL(clicked()), this, SLOT(setDifficulty2()));
    for (int i = 0; i < NUM_DIFFICULTY; i++)
    {
        difficultyGroup->addButton(difficulty[i]);
        pauseLayout->addWidget(difficulty[i], 40+(20*i), 20);
    }

    this->setLayout(pauseLayout);
}

/**
 * @brief PauseMenu::closeEvent
 * @param event is the event telling the PauseMenu to close
 *
 * resume the gameBoard, and sets focus back to the gameboard
 */
void PauseMenu::closeEvent(QCloseEvent *event)
{
    gameboard->setPaused(false);
    gameboard->setFocus();
    event->accept();
}

/**
 * @brief PauseMenu::setDifficulty0
 *
 * Easy Mode sets the gbTimer to activate every 3 seconds
 */
void PauseMenu::setDifficulty0()
{
    this->gameboard->setDifficulty(4);
}

/**
 * @brief PauseMenu::setDifficulty1
 *
 * Medium mode sets the gbTimer to activate every 1.5 seconds
 */
void PauseMenu::setDifficulty1()
{
    this->gameboard->setDifficulty(2);
}

/**
 * @brief PauseMenu::setDifficulty2
 *
 * Hard mode sets the gbTimer to activate every .75 seconds
 */
void PauseMenu::setDifficulty2()
{
    this->gameboard->setDifficulty(1);
}
