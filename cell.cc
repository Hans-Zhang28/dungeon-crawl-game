#include "cell.h"
#include "game.h"

using namespace std;

//ctor
Cell::Cell(int r, int c, char state): state(state), r(r), c(c){}


 //dtor
Cell::~Cell(){}


// purpose: getter for state
// returns: the state of the Cell
char Cell::getState() 
{
    return state;
}


// purpose: setter for state
void Cell::setState(char newstate) 
{
    state=newstate;
}


// purpose: setter for the coordinate which are row and column
void Cell::setCoords(const int newr, const int newc) 
{
    r=newr;
    c=newc;
}
	

// purpose: getter for c
// returns: value of c
int Cell::getC() 
{
    return c;
}


// purpose: getter for r
// returns: value of r
int Cell::getR() 
{
    return r;
}

