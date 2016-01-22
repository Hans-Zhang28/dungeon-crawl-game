#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cell.h"

class Player;

class Enemy : public Cell {
	int hp;
	int atk;
	int def;
	int movement;

	public:
	Enemy(int r, int c, char state, int hp, int atk, int def); //default ctor
	virtual ~Enemy() = 0; //dtor
  int	getAtk(); //getter of atk
	int getDef(); //getter of def
	bool isDead(); //return true if the Enemy is dead, otherwies false
	void addHp(int hp); //adder of hp
	int getHp(); //getter of hp
	void addMovement(); //adder of movement
	int getMovement(); //getter of movement
	virtual int combat(Player* player); //the combat function for Enemy
	virtual int dropGold(); //return the gold number the player will get when the enemy dies
};

#endif
