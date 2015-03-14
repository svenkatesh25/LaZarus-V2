#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "gameboard.h"

/**
 * class GameBoard is declared beforehand
 */
class GameBoard;

/**
 * @brief The Game class
 * Game handles the user interface for LaZarus. It is a QMainWindow that has
 * the logo of the game as its top dockwidget, a widget with a health bar and score
 * counter for the right dockwidget and a message box as the bottom dockwidget.
 * The messagebox, healthbar, and score counter all recieve output from the game to have
 * dynamic values. The messagebox will tell the user when to reload and if their gun is reloaded.
 * If the user attempts to reload but it does not say the gun is reloaded after a second, it means
 * the user is out of ammunition.
 */
class Game : public QMainWindow
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    Game(int row_size, int col_size);
    
signals:

public slots:
    void gameTimerAction();

private:
    QDockWidget* bottomMenu;
    QDockWidget* rightMenu;
    QDockWidget* topMenu;

    QWidget* bottomWidget;
    QWidget* rightWidget;
    QWidget* topWidget;

    QGridLayout* bottomLayout;
    QGridLayout* rightLayout;
    QGridLayout* topLayout;

    QLabel* gameLogo;
    GameBoard* gameBoard;
    QTextEdit* textBox;
    QLabel* healthLabel;
    QProgressBar* healthBar;
    QLabel* scoreLabel;
    QLabel* scoreText;
    
    std::vector<QPixmap*> gameImages;

    QTimer* gameTimer;

    QWidget* gameOverWindow;
    QGridLayout* gameOverWindowLayout;
    QLabel* gameOverWindowText;
    QLabel* gameOverWindowScore;
};

#endif // GAME_H
