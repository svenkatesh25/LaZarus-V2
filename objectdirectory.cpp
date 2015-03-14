#include "objectdirectory.h"

//***********************************
//GET METHODS
//***********************************
//Edit1: none of these check indexs

/**
 * @brief ObjectDirectory::getODgboObjects
 * @param index is the index of the vector of gameboardObjects
 * @return
 *
 * returns a gameBoardObject specified
 */
GameBoardObject* ObjectDirectory::getODgboObjects(int index)
{
    return ODgboObjects[index];
}

/**
 * @brief ObjectDirectory::ObjectDirectory
 *
 * makes a gray tile game board object. Not used
 */
ObjectDirectory::ObjectDirectory()
{
    //initialize ODgameBoardObjects
    ODgboObjects.push_back(new GameBoardObject("gray tile", 0, 0, true));               //gray tile
}

/**
 * @brief ObjectDirectory::~ObjectDirectory
 *
 * default destructor for Object Directory.
 */
ObjectDirectory::~ObjectDirectory()
{

}

