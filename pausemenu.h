#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include "doclib.h"
#include "gameboard.h"

/**
 * class GameBoard must be declared beforehand due to the PauseMenu's GameBoard pointer.
 */
class GameBoard;

/**
 * @brief The PauseMenu class
 * Menu to pop up when the game is paused. Resumes the game when closed.
 * Has QRadioButtons toa djut the difficulty of the game. They make the
 * gameBoard's timer run at 3 seconds, 1.5 seconds, and .75 seconds respectively.
 */
class PauseMenu : public QWidget
{
    Q_OBJECT
public:
    ~PauseMenu();

    PauseMenu(GameBoard* gameboard);
    void closeEvent(QCloseEvent *event);
signals:

public slots:
    //bool close();
    void setDifficulty0();
    void setDifficulty1();
    void setDifficulty2();


private:
    GameBoard* gameboard;

    QGridLayout* pauseLayout;
    QPushButton* resume;

    QButtonGroup* difficultyGroup;
    QRadioButton* difficulty[NUM_DIFFICULTY];
};

#endif // PAUSEMENU_H
