#include "enemy.h"
#include "human.h"

//default ctor
Human::Human(int r, int c, char state) 
	:Enemy(r,c,state,140,20,20) {};

//purpose: returns the number of the gold that human will drop when he dies
//return: integer
int Human::dropGold() {
	return 4;
}//dropGold()
