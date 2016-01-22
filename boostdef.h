#ifndef __BOOSTDEF_H__
#define __BOOSTDEF_H__
#include "temppotion.h"


class boostDef: public tempPotion{
  public:
    boostDef(Player & player); // ctor
    ~boostDef(); // dtor
    int combat(Enemy *enemy); // player attack enemy // returns: the hp drop of enemy.
    // getter:
    int getHp();   // getter for hp
    int getAtk();  // getter for atk
    int getDef();  // getter for def
    int getGold(); // getter for gold
    // setter:
    void addGold(int amount);  // adder for gold
    void addHp(int hp);  // adder for hp
    char getState(); //getter for state
	void setState(char newstate); //setter for state
	void setCoords(const int newr, const int newc); //setter for the coordinate which are row and column
	void setGame(Game* game); //setter for game
	int getC(); //getter for c
	int getR(); //getter for r
};

#endif
