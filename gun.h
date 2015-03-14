#ifndef GUN_H
#define GUN_H

#include "item.h"

/**
 * @brief The Gun class
 * The gun has many different internal variables, such as magazine size, current magazine,
 * accuracy, power, firing rate, and swap time. It also has a QString to name it. These variables
 * set all the stats of the gun that affects how it is used. It also has a type to detail how the bullets
 * are fired. Finally it has reload and useammo functions to detail how the current magazine is managed.
 */
class Gun : public Item
{
public:
    Gun();
    ~Gun();

    Gun(QString name) : Item(name, 1)
    {
       setStats();
    }

    bool useAmmo();
    void reload();

    //get methods
    QString getType();
    int getMagazineSize();
    int getCurrentMagazine();
    double getReloadTime();
    int getAccuracy();
    int getRange();
    int getPower();
    double getFiringRate();
    double getSwapTime();

    //set methods
    void setCurrentMagazine(int number);
private:
    void setStats();

    QString type;

    int magazineSize;
    int currentMagazine;
    double reloadTime;

    int accuracy;
    int range;
    int power;
    double firingRate;

    double swapTime;
};

#endif // GUN_H
