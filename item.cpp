#include "item.h"

/**
 * @brief Item::Item
 *
 * Item default constructor
 */
Item::Item()
{

}

/**
 * @brief Item::~Item
 *
 * Item default destructor
 */
Item::~Item()
{

}

/**
 * @brief Item::Item
 * @param name is the name of the item
 * @param quantity is how much of the item you have
 *
 * Item constructor. Sets name and quantity. Sets the description and name for
 * all non gun items based on the name of the item.
 */
Item::Item(QString name, int quantity)
{
    //don't set description or weight for guns
    this->name = name;
    this->quantity = quantity;
    if (name == "Apple")
    {
        this->description = "A red fruit. Restores satiety";
        this->weight = 1 * quantity;
    }
    else if (name == ".44 Magnum Ammo")
    {
        this->description = "Ammo for the .44 Magnum";
        this->weight = 0 * quantity;
    }
}
