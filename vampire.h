#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "player.h"

class Enemy;

class Vampire: public Player{
  public:
    Vampire(int r, int c, char state); // ctor
    int combat(Enemy *enemy); // player attack enemy // returns: the hp drop of enemy.
};

#endif
