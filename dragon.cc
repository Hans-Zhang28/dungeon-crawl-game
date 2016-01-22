#include "dragon.h"
#include "treasure.h"

//default ctor
Dragon::Dragon(int r, int c, char state) 
	: Enemy(r,c,state,150,20,20), d_hoard(0){}

//getter for d_hoard
Treasure* Dragon::getD_hoard() {return d_hoard;}

// purpose: drop zero gold when dragon is dead
// returns: zero
int Dragon::dropGold()
{
    return 0;
} // dropGold()

// setter for d_hoard
void Dragon::setD_hoard(Treasure * gold)
{
    d_hoard=gold;
}
