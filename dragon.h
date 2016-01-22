#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class Treasure;

class Dragon : public Enemy {
  Treasure* d_hoard;
	public:
	Dragon(int r, int c, char state); //default ctor
	Treasure* getD_hoard(); //getter for d_hoard
    int dropGold();// drop zero gold when dragon is dead 
    void setD_hoard(Treasure * gold); // setter for d_hoard
};

#endif
