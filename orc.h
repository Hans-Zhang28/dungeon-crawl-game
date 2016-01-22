#ifndef __ORCS_H__
#define __ORCS_H__
#include "enemy.h"

class Player;

class Orc : public Enemy {
	public:
	Orc(int r, int c, char state); //default ctor
	int combat(Player* player); //for it does 50% more damage to goblins
	                      //we need to overwrite combat(Player*)
};

#endif
