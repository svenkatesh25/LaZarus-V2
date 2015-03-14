#ifndef OBJECTDIRECTORY_H
#define OBJECTDIRECTORY_H

#include "gameboardobject.h"
#include "mainwindow.h"
#include "doclib.h"

/**
 * @brief The ObjectDirectory class
 * Class to hold objects to be copied. Not implemented for now.
 */
class ObjectDirectory
{
    friend class MainWindow;
public:
    ObjectDirectory();
    ~ObjectDirectory();

    //GET METHODS
    GameBoardObject* getODgboObjects(int index);

private:
    std::vector<GameBoardObject*> ODgboObjects;
};

#endif // OBJECTDIRECTORY_H
