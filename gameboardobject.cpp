#include "gameboardobject.h"

/**
 * @brief GameBoardObject::GameBoardObject
 * @param parent is the QWidget this object is linked to
 *
 * Default constructor for class.
 */
GameBoardObject::GameBoardObject(QWidget *parent) : QWidget(parent)
{

}

//2 Discarded function to keep just in case
/*
GameBoardObject& GameBoardObject::operator=(const GameBoardObject& gbo)
{
    if (this != &gbo)
    {

        this->sprite = gbo.sprite;
        this->gboRow = gbo.gboRow;
        this->gboCol = gbo.gboCol;

        upPass = gbo.upPass;
        rightPass = gbo.rightPass;
        downPass = gbo.downPass;
        leftPass = gbo.leftPass;
    }

    return *this;
}

//copy constructor
GameBoardObject::GameBoardObject(const GameBoardObject& gbo)
{
    this->sprite = gbo.sprite;
    this->gboRow = gbo.gboRow;
    this->gboCol = gbo.gboCol;

    upPass = gbo.upPass;
    rightPass = gbo.rightPass;
    downPass = gbo.downPass;
    leftPass = gbo.leftPass;
}
*/

/**
 * @brief GameBoardObject::~GameBoardObject
 *
 * Default destructor for Game Board Object
 */
GameBoardObject::~GameBoardObject()
{

}

/**
 * @brief GameBoardObject::GameBoardObject
 * @param sprite is the string that will be interpreted into a QLabel
 * @param gboRow is the row of the object
 * @param gboCol is the column of the object
 * @param passable sets whether the object can be passed by the player, zombies, or bullets
 *
 * Constructor for gameBoardObject. Sets the sprite to be interpreted.
 * , the row and col of the object, and whether the object can be passed by
 * the player, zombies, or bullets.
 */
GameBoardObject::GameBoardObject(std::string sprite, int gboRow, int gboCol, bool passable)
{
    this->sprite = sprite;
    this->gboRow = gboRow;
    this->gboCol = gboCol;

    if (passable == true)
    {
        upPass = true;
        rightPass = true;
        downPass = true;
        leftPass = true;
    }
    else
    {
        upPass = false;
        rightPass = false;
        downPass = false;
        leftPass = false;
    }
}

//***********************************
//SET METHODS
//***********************************

/**
 * @brief GameBoardObject::setgboRow
 * @param gboRow is what the gboRow will be set to
 *
 * Sets gboRow
 */
void GameBoardObject::setgboRow(int gboRow)
{
    this->gboRow = gboRow;
}

/**
 * @brief GameBoardObject::setgboCol
 * @param gboCol is what the gboCol will be set to
 *
 * Sets gboCol
 */
void GameBoardObject::setgboCol(int gboCol)
{
    this->gboCol = gboCol;
}

/**
 * @brief GameBoardObject::setSprite
 * @param sprite is what the sprite will be set to
 *
 * Sets the sprite to be interpreted
 */
void GameBoardObject::setSprite(std::string sprite)
{
    this->sprite = sprite;
}

/**
 * @brief GameBoardObject::setPass
 * @param pass says what all the pass bools will be
 *
 * Determines whether object is passable from any side or not
 */
void GameBoardObject::setPass(bool pass)
{
    this->upPass = pass;
    this->rightPass = pass;
    this->leftPass = pass;
    this->downPass = pass;
}

/**
 * @brief GameBoardObject::setUpPass
 * @param upPass is what upPass is set to
 *
 * sets upPass
 */
void GameBoardObject::setUpPass(bool upPass)
{
    this->upPass = upPass;
}

/**
 * @brief GameBoardObject::setRightPass
 * @param rightPass is what rightPass is set to
 *
 * sets rightPass
 */
void GameBoardObject::setRightPass(bool rightPass)
{
    this->rightPass = rightPass;
}

/**
 * @brief GameBoardObject::setDownPass
 * @param downPass is what downPass is set to
 *
 * sets downPass
 */
void GameBoardObject::setDownPass(bool downPass)
{
    this->downPass = downPass;
}

/**
 * @brief GameBoardObject::setLeftPass
 * @param leftPass is what leftPass is set to
 *
 * sets leftPass
 */
void GameBoardObject::setLeftPass(bool leftPass)
{
    this->leftPass = leftPass;
}

//***********************************
//GET METHODS
//***********************************

/**
 * @brief GameBoardObject::getgboRow
 * @return
 *
 * returns gboRow
 */
int GameBoardObject::getgboRow()
{
    return gboRow;
}

/**
 * @brief GameBoardObject::getgboCol
 * @return
 *
 * return gboCol
 */
int GameBoardObject::getgboCol()
{
    return gboCol;
}

/**
 * @brief GameBoardObject::getSprite
 * @return
 *
 * return sprite
 */
std::string GameBoardObject::getSprite()
{
    return sprite;
}

/**
 * @brief GameBoardObject::getUpPass
 * @return
 *
 * return upPass
 */
bool GameBoardObject::getUpPass()
{
    return upPass;
}

/**
 * @brief GameBoardObject::getRightPass
 * @return
 *
 * return rightPass
 */
bool GameBoardObject::getRightPass()
{
    return rightPass;
}

/**
 * @brief GameBoardObject::getDownPass
 * @return
 *
 * returns downPass
 */
bool GameBoardObject::getDownPass()
{
    return downPass;
}

/**
 * @brief GameBoardObject::getLeftPass
 * @return
 *
 * returns leftPass
 */
bool GameBoardObject::getLeftPass()
{
    return leftPass;
}

/**
 * @brief GameBoardObject::getDroppedItems
 * @return
 *
 * returns vector droppedItems
 */
std::vector<Item*> GameBoardObject::getDroppedItems()
{
    return droppedItems;
}

/**
 * @brief GameBoardObject::pushBackDroppedItems
 * @param item is the item to be pushed back onto droppedItems
 *
 * pushes back an item onto droppedItems
 */
void GameBoardObject::pushBackDroppedItems(Item* item)
{
    droppedItems.push_back(item);
}
