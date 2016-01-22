#include "halfling.h"
#include "cell.h"

//default ctor
Halfling::Halfling(int r, int c, char state) 
	: Enemy(r,c,state,100,15,20){}
