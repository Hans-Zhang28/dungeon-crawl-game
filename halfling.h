#ifndef __HALFLING_H__
#define __HALFLING_H__
#include "enemy.h"

class Cell;

class Halfling : public Enemy {
	public:
	Halfling(int r, int c, char state); //default ctor
};

#endif
