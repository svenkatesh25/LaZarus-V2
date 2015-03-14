#include "zombie.h"

/**
 * @brief Zombie::Zombie
 *
 * default constructor for Zombie class
 */
Zombie::Zombie()
{

}

/**
 * @brief Zombie::~Zombie
 *
 * default destructor for zombie class
 */
Zombie::~Zombie()
{

}

/**
 * @brief Zombie::getDamage
 * @return
 *
 * returns the amount of damage zombie does. 41 for basic zombie. 61 for master zombie.
 */
int Zombie::getDamage()
{
    return damage;
}

/**
 * @brief Zombie::getInventory
 * @return
 *
 * return the zombie's inventory
 */
std::vector<Item*> Zombie::getInventory()
{
    return inventory;
}

/**
 * @brief Zombie::damaged
 * @param damage is how much health zombie losses
 *
 * subtract damage from zombie's health and
 * sets alive to false if health goes to 0 or below
 */
void Zombie::damaged(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        alive = false;
    }
}

/**
 * @brief Zombie::isAlive
 * @return
 *
 * returns bool alive
 */
bool Zombie::isAlive()
{
    return alive;
}
