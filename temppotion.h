#ifndef __TEMPPOTION_H__
#define __TEMPPOTION_H__
#include "player.h"

class Enemy;

class tempPotion: public Player{
  protected:
    Player & origPlayer;
    tempPotion(Player & player); // ctor
    virtual ~tempPotion()=0; // dtor
    
};

#endif
