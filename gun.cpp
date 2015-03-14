#include "gun.h"

/**
 * @brief Gun::Gun
 *
 * Gun default constructor
 */
Gun::Gun()
{

}

/**
 * @brief Gun::~Gun
 *
 * Gun default destructor
 */
Gun::~Gun()
{

}

/**
 * @brief Gun::useAmmo
 * @return
 *
 * if theres ammo left, decrease it by one and return true.
 * otherwise, return false
 */
bool Gun::useAmmo()
{
    if (currentMagazine == 0)
    {
        return false;
    }
    else
    {
        --currentMagazine;
        return true;
    }
}

/**
 * @brief Gun::reload
 *
 * set currentMagazine to magazineSize to restore ammo
 */
void Gun::reload()
{
    currentMagazine = magazineSize;
}

//***********************************
//GET METHODS
//***********************************
/**
 * @brief Gun::getType
 * @return
 *
 * returns QString type;
 */
QString Gun::getType()
{
    return this->type;
}

/**
 * @brief Gun::getMagazineSize
 * @return
 *
 * return magazine size
 */
int Gun::getMagazineSize()
{
    return this->magazineSize;
}

/**
 * @brief Gun::getCurrentMagazine
 * @return
 *
 * return current magazine size
 */
int Gun::getCurrentMagazine()
{
    return this->currentMagazine;
}

/**
 * @brief Gun::getReloadTime
 * @return
 *
 * returns reload time
 */
double Gun::getReloadTime()
{
    return this->reloadTime;
}

/**
 * @brief Gun::getAccuracy
 * @return
 *
 * return accuracy
 */
int Gun::getAccuracy()
{
    return this->accuracy;
}

/**
 * @brief Gun::getRange
 * @return
 *
 * returns range of the gun. Not used.
 */
int Gun::getRange()
{
    return this->range;
}

/**
 * @brief Gun::getPower
 * @return
 *
 * returns the power of the gun
 */
int Gun::getPower()
{
    return this->power;
}

/**
 * @brief Gun::getFiringRate
 * @return
 *
 * returns firing rate of the gun
 */
double Gun::getFiringRate()
{
    return this->firingRate;
}

/**
 * @brief Gun::getSwapTime
 * @return
 *
 * returns swap time of the gun
 */
double Gun::getSwapTime()
{
    return this->swapTime;
}

//***********************
//SET FUNCTIONS
//**********************

/**
 * @brief Gun::setCurrentMagazine
 * @param number is what the magazine gets set to
 *
 * Function to set magazine to some size if there is not enough ammo
 * for a full reload;
 */
void Gun::setCurrentMagazine(int number)
{
    currentMagazine = number;
}

//*************************
//Other functions
//*************************

/**
 * @brief Gun::setStats
 *
 * sets all the stats of the gun depending on the name of the gun.
 * Only gun implemented right now is the .44 magnum
 */
void Gun::setStats()
{
    if (this->name == "M9")
    {
        this->accuracy = 100;//90;
        this->description = "good pistol";
        this->firingRate = .3;//.3; //one shot every .3
        this->magazineSize = 15;
        this->power = 30;
        this->range = 3;
        this->reloadTime = 1;
        this->swapTime = 1;
        this->type = "pistol";
        this->weight = 5;
    }
    else if (this->name == ".44 Magnum")
    {
        this->accuracy = 80;
        this->description = "meh pistol";
        this->firingRate = .1;
        this->magazineSize = 8;
        this->power = 50;
        this->range = 2;
        this->reloadTime = 1;
        this->swapTime = 1;
        this->type = "pistol";
        this->weight = 5;
    }
    else if (this->name == "Ray Gun")
    {
        this->accuracy = 100;
        this->description = "best pistol";
        this->firingRate = .2;
        this->magazineSize = 15;
        this->power = 40;
        this->range = 5;
        this->reloadTime = .5;
        this->swapTime = .5;
        this->type = "pistol";
        this->weight = 5;
    }
    else if (this->name == "RPG")
    {
        this->accuracy = 65;
        this->description = "worst explosive launcher";
        this->firingRate = 1;
        this->magazineSize = 1;
        this->power = 100;
        this->range = 5;
        this->reloadTime = 2.5;
        this->swapTime = 2;
        this->type = "launcher";
        this->weight = 20;
    }

    this->currentMagazine = this->magazineSize;
}
