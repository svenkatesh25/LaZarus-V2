#include "mainwindow.h"
#include <QApplication>
#include "gameboardobject.h"
#include "gameboard.h"

/**
 * @brief main
 * @param argc is the parameter for all qt functions
 * @param argv is the parameter for all qt functions
 * @return
 *
 * main function is whats run. Creates a mainWindow and shows it.
 */
int main(int argc, char *argv[])
{
    //create a mainwindow and everything will flow from there
    QApplication a(argc, argv);
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();

    return a.exec();
}
