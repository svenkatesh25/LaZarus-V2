#include "player.h"

/**
 * @brief Player::Player
 *
 * default constructor
 */
Player::Player()
{

}

/**
 * @brief Player::~Player
 *
 * default destructor
 */
Player::~Player()
{

}

/**
 * @brief Player::damaged
 * @param damage is how much gets subtracted from the player's health
 *
 * function damaged subtracts damage from hp, and will modify the bool
 * alive if hp goes to 0 or below
 */
void Player::damaged(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        alive = false;
    }
}

//********************************
//GET METHODS
//*****************************

/**
 * @brief Player::getEquippedGun
 * @return
 *
 * returns the equippedGun
 */
Gun* Player::getEquippedGun()
{
    return equippedGun;
}

/**
 * @brief Player::isAlive
 * @return
 *
 * returns the bool alive
 */
bool Player::isAlive()
{
    return alive;
}

/**
 * @brief Player::getMvmntRate
 * @return
 *
 * returns the player's movement rate
 */
double Player::getMvmntRate()
{
    return mvmntRate;
}

/**
 * @brief Player::getHP
 * @return
 *
 * returns the player's hp
 */
int Player::getHP()
{
    return hp;
}

/**
 * @brief Player::mutHP
 * @param hp is how much is added to player's hp
 *
 * adds to players hp
 */
void Player::mutHP(int hp)
{
    this->hp += hp;
}

/**
 * @brief Player::pushBackInventory
 * @param item is the item to add to inventory
 *
 * pushes back item onto player's inventory
 */
void Player::pushBackInventory(Item* item)
{
    inventory.push_back(item);
}

/**
 * @brief Player::reload
 * @return
 *
 * reload's the players gun.
 * First, makes string to look for.
 * Next, goes through the entire inventory list to find the ammo and a non zero quantity.
 * Next, reloads the gun or adds ammo if theres not enough to fully reload
 * Finally, returns true if reloaded and false otherwise
 */
bool Player::reload()
{
    QString ammoName = equippedGun->name + " Ammo";
    for (auto i = inventory.begin(); i != inventory.end(); i++)
    {
        if ((*i)->name == ammoName && (*i)->quantity > 0)
        {
            if ((*i)->quantity > equippedGun->getMagazineSize())
            {
                equippedGun->reload();
                (*i)->quantity -= equippedGun->getMagazineSize();
            }
            else
            {
                equippedGun->setCurrentMagazine((*i)->quantity);
                (*i)->quantity = 0;
            }
            return true;
        }
    }
    return false;
}
