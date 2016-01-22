#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "enemy.h"

class Human : public Enemy {
	public:
	Human(int r, int c, char state); //default ctor
	int dropGold(); //for the reason that human always drops 2 normal piles of gold
	                 // so we need to overwrite the dropGold()
};

#endif
