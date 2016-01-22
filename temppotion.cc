#include "temppotion.h"
//#include "player.h"

using namespace std;

class Enemy;

// ctor
tempPotion::tempPotion(Player & player): origPlayer(player){} 


// dtor
tempPotion::~tempPotion()
{
    delete &origPlayer;
}


