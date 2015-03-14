#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "gameboardobject.h"
#include "gun.h"


/* class zombie zombie.h "zombie.h"
   class Zombie inherits from GameBoardObject and has health to survive
 */
/**
 * @brief The Zombie class
 * Zombies have hp and damage and return whether they are alive (undead) or not.
 * Zombies can also be randomly initialized into a master zombie as a rate of 5%. These
 * zombies drop ammunition for your gun.
 */
class Zombie : public GameBoardObject
{
public:
    Zombie();
    ~Zombie();

    Zombie(int gboRow, int gboCol) : GameBoardObject("zombie", gboRow, gboCol, true)
    {
        damage = 41;
        hp = 20;
        alive = true;

        if (rand() % 100 < 5)
        {
            damage = 61;
            hp = 150;
            //sprite = "zombie2";
            this->setSprite("zombie2");
            inventory.push_back(new Item(".44 Magnum Ammo", 50));
        }

    }

    int getDamage();
    std::vector<Item*> getInventory();

    void damaged(int damage);
    bool isAlive();
private:
    int damage;
    int hp;
    bool alive;

    std::vector<Item*> inventory;
};

#endif // ZOMBIE_H
