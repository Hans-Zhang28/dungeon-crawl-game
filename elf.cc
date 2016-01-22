#include "cell.h"
#include "elf.h"

//default ctor
Elf::Elf(int r, int c, char state) 
	:Enemy(r,c,state,140,30,10) {}
