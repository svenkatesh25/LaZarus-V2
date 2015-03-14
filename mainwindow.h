#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "doclib.h"
//#include "objectdirectory.h"
#include "gameboard.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * MainWindow has many different buttons and logos. The only working buttons
 * right now are the File Buttons and Instructions. The File buttons open up the game, and
 * the Instructions button opens up a new window to describe how to play the game.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void openGameBoard();
    void openInstructions();

    //just slot to test out timer
    void mainTimerGraphics();

private:
    Ui::MainWindow *ui;
    std::vector<QPixmap*> images;
    std::vector<QPushButton*> rsButtons;
    std::vector<QPushButton*> file;
    std::vector<QPushButton*> fileDelete;
    QLabel* logo;

    QGridLayout* mainWindowLayout;
    QWidget* window;

    QTimer* mainTimer;

    QWidget* instructions;
    QGridLayout* instructionsLayout;
    QLabel* instructionsLabel;
    QLabel* instructionsLabel2;

    //GET RID OF THIS CODE
    //test for keypress
    //QLabel *myLabelText;
};

#endif // MAINWINDOW_H
