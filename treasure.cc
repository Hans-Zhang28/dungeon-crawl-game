#include "treasure.h"
#include "cell.h"


using namespace std;


// ctor
Treasure::Treasure(int r, int c, char state, int amt): Cell(r, c, state), amount(amt), dragon(0){}


// purpose: getter for amount
// returns: the value of amount
int Treasure::getAmount()
{
    return amount;
}


Dragon * Treasure::getDragon()
{
    return dragon;
}

void Treasure::setDragon(Dragon * dragon)
{
    this->dragon=dragon;
}
