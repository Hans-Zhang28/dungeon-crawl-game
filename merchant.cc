#include "merchant.h"


//default ctor
Merchant::Merchant(int r, int c, char state) 
	:Enemy(r,c,state,30,70,5) {}


//purpose: returns the amount of the gold
//return: integer
int Merchant::dropGold() { return 4; }
