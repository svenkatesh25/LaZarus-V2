#ifndef ITEM_H
#define ITEM_H

#include "doclib.h"

/**
 * @brief The Item class
 * the item class has a name, description, quantity and weight. This is used to
 * describe the item.
 */
class Item
{
public:
    Item();
    ~Item();

    Item(QString name, int quantity);


    QString name;
    QString description;

    int quantity;
    int weight;
private:
    //QString name;
    //QString description;

    //int quantity;
    //int weight;
};

#endif // ITEM_H
