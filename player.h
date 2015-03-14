#ifndef PLAYER_H
#define PLAYER_H

#include "gameboardobject.h"
#include "gun.h"

/* class player player.h "player.h"
   class Player inherits from GameBoardObject and has health to survive
 */
/**
 * @brief The Player class
 * The Player class inherits from GameBoardObject. It has its own movement rate
 * , equippedGun, bool to desribe its alive and more. Its inventory has Apples (which
 * are not used yet) and ammo for the gun.
 */
class Player : public GameBoardObject
{
    Q_OBJECT
public:
    Player();
    ~Player();

    Player(std::string name, int gboRow, int gboCol) : GameBoardObject("Player Down", gboRow, gboCol, false)
    {
        this->name = name;
        hp = 100;
        satiety = 100;
        alive = true;
        mvmntRate = .2;
        equippedGun = new Gun(".44 Magnum");
        inventory.push_back(new Item("Apple", 5));
        inventory.push_back(new Item(".44 Magnum Ammo", 200));
    }

    void damaged(int damage);

    //get methods
    Gun* getEquippedGun();
    bool isAlive();
    double getMvmntRate();
    int getHP();

    //set methods
    void mutHP(int hp);
    void pushBackInventory(Item* item);

    //other methods
    bool reload();
private:
    std::string name;

    int hp;
    int satiety;
    bool alive;
    double mvmntRate;

    std::list<Item*> inventory;
    Gun* equippedGun;
};

#endif // PLAYER_H
