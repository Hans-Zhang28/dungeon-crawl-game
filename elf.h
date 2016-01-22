#ifndef __ELF_H__
#define __ELF_H__
#include "enemy.h"

class Cell;

class Elf : public Enemy {
	public:
	Elf(int r, int c, char state); //default ctor
};

#endif
