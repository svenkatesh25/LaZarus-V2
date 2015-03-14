#ifndef DOCLIB
#define DOCLIB

/** @mainpage Pic-10C-Final-Project
    @author Sanan Venkatesh
    @date March 13 2015
    @version 4.18
    @brief This project is the user interface for my game LaZarus

    @section Introduction

   This code constructs a user interface for the game LaZarus. Th main page has several buttons,
   of which, the files and the instructions work. The remaining buttons are there for future
   expansions. The instructions button open up the instructions to play the game. The file buttons
   will open up a new window, in which the logo is in the top of the game, a health bar and score
   display on the right, and a message box on the bottom to display important images. The game runs as
   the window's central widget. The game is a 17 by 17 grid with the player starting around the middle.
   The gray tiles are the floor and the black tiles are impassable walls. The player and zombie sprites are
   also animated. Zombies will spawn from the borders of the map every 1.5 seconds and will move towards the player
   randomly. Basic Zombies deal 40 damage to the player and master zombies deal 60 damage. The player has 100 health.
   The player also recovers one point of health every 1.5 seconds. The zombies also move every 1.5 seconds. The space buttons
   shoots a bullet which can hit and kill the zombies. It takes 1 bullet to kill a basic zombie and 5 to kill a master zombie.
   The gun has a magazine size of 8, after which it must be reloaded, and it also has a fire cap of 1 bullet/.2 seconds and an accuracy of
   80%. Reloading can be done with the r button. Reloading will get rid of any existing bullets in the gun and will take 8 bullets
   from the player's inventory. The player starts with 200 bullets and can scavenge more from crowns on the ground
   which master zombies drop. Crowns can be picked up with the v button. The p button can pause the game and can be used to alter
   the difficulty. Finally, the score will continuously update, and the score varies based on the difficulty challenged.

   @section Conclusion
   This code successfully implements the user interface and will be expanded on later.
*/

#include <ctime>
#include <iostream>
#include <list>
#include <QApplication>
#include <QButtonGroup>
#include <QDebug>
#include <QDockWidget>
#include <QGridLayout>
#include <QtGui>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <string>
#include <utility>
#include <vector>

//clipboard for various things to be referenced
/*
 1) //GET RID OF THIS CODE
 2)
//***********************************
//GET METHODS
//***********************************
*/

//IDEAS
//Idea1: Experience based system
//Idea2: graphics and sound effects

/**
 * @brief MAX_BOARD_SIZE
 * details the max size for the board. Board is currently 17 by 17 but potentially
 * could be even bigger
*/
static const int MAX_BOARD_SIZE = 1000;

/**
 * @brief NUM_DIFFICULTY
 * details the number of  difficulty buttons
 */
static const int NUM_DIFFICULTY = 3;

/**
 * @brief LABEL_SIZE
 * details the size of labels for the gameboard
 */
static const int LABEL_SIZE = 50;

#endif // DOCLIB

