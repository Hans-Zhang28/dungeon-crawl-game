#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "enemy.h"

class Merchant : public Enemy {
	public:
	Merchant(int r, int c, char state); //default ctor
	int dropGold(); //since every time the merchant will drop merchant hoard with value 4 to the player
	              //so we need to overwrite it
};

#endif
