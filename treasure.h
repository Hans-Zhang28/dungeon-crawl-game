#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "cell.h"

class Dragon;

class Treasure: public Cell{
    int amount;
    Dragon * dragon; // point to dragon if this is a dragon hoard
  public:
    Treasure(int r, int c, char state, int amt); // ctor
    int getAmount(); // getter for amount
    Dragon * getDragon();
    void setDragon(Dragon * dragon);
};

#endif
