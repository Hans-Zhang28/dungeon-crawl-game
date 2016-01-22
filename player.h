#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cell.h"
#include <string>

class Enemy;

class Player: public Cell{
	protected:
    int hp;
    int atk;
    int def;
    int gold;
  public:
    Player(int r, int c, char state, int hp, int atk, int def, int gold); // ctor
    virtual ~Player() =0;   // dtor 
    virtual int combat(Enemy *enemy); // player attack enemy // returns: the hp drop of enemy.
    // getter:
    int getHp();   // getter for hp
    int getAtk();  // getter for atk
    int getDef();  // getter for def
    int getGold(); // getter for gold

    // setter:
    void addGold(int amount);  // adder for gold
    virtual void addHp(int hp);  // adder for hp
    void addAtk(int atk); // adder for atk
    void addDef(int def); // adder for def
};

#endif
