#ifndef __DROW_H__
#define __DROW_H__
#include "player.h"


class Drow: public Player{
  public:
    Drow(int r, int c, char state); // ctor
    ~Drow(); // dtor
};

#endif
