#ifndef GAMEBOARDOBJECT_H
#define GAMEBOARDOBJECT_H

#include <QWidget>
#include "doclib.h"
#include "gun.h"


/* @class gameboardobject gameboardobject.h "gameboardobject.h"
 class to hold each GameBoardObject. Determines if it is passable (not yet implemented), whats the position, etc.
*/
/**
 * @brief The GameBoardObject class
 * Each GameBoardObject has a row and col to detail where it is on the gameboard.
 * The object also has a std::string sprite that is interpreted later to make the image for a corresponding QLabel to display.
 * The gameboardObject also has an item vector to hold an item that may be dropped on it.
 * It is also possible to set the GameBoardObject to impassable, meaning it cannot be passed by zombies or the player, and
 * bullets do not go through it.
 */
class GameBoardObject : public QWidget
{
    Q_OBJECT
public:
    //base constructor
    explicit GameBoardObject(QWidget *parent = 0);

    //2 Discarded functions to keep just in case
        //GameBoardObject& operator=(const GameBoardObject& gbo);
        //GameBoardObject(const GameBoardObject& gbo);
    ~GameBoardObject();

    //normal constructor
    GameBoardObject(std::string sprite, int gboRow, int gboCol, bool passable);

    //set methods
    void setgboRow(int gboRow);
    void setgboCol(int gboCol);
    void setSprite(std::string sprite);
    void setPass(bool pass);
    void setUpPass(bool upPass);
    void setRightPass(bool rightPass);
    void setDownPass(bool downPass);
    void setLeftPass(bool leftPass);

    //get methods
    int getgboRow();
    int getgboCol();
    std::string getSprite();
    bool getUpPass();
    bool getRightPass();
    bool getDownPass();
    bool getLeftPass();

    std::vector<Item*> getDroppedItems();

    void pushBackDroppedItems(Item* item);
signals:

public slots:

private:
    int gboRow; //row of object
    int gboCol; //col of object

    std::string sprite; //how to display object

    bool upPass; //can be passed from up
    bool rightPass; //can be passed from right
    bool downPass; //can be passed from down
    bool leftPass; //can be passed from left

    std::vector<Item*> droppedItems;
};

#endif // GAMEBOARDOBJECT_H
