#ifndef __TROLL_H__
#define __TROLL_H__
#include "player.h"


class Troll: public Player{
  public:
    Troll(int r, int c, char state); // ctor
    void addHp(int hp); // adder for hp, hp is capped at 120 HP
};

#endif
