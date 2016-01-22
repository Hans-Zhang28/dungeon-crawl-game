#include "enemy.h"
#include "cell.h"
#include "player.h"
#include <cstdlib>
#include <cmath>

//dtor
Enemy::~Enemy() {}

//ctor
Enemy::Enemy(int r, int c, char state, int hp, int atk, int def)
	: Cell(r, c, state), hp(hp), atk(atk), def(def), movement(0){}

//getter for the atk
int Enemy::getAtk() {return atk;}

//getter for def
int Enemy::getDef() {return def;}

//purpose: returns true if the enemy is dead otherwise returns false
//return: bool
bool Enemy::isDead() {return hp <= 0;}

//adder of hp
void Enemy::addHp(int hp) {this->hp += hp;}

//getter of hp
int Enemy::getHp() {
	if (hp <= 0) return 0;
	else return hp;
}

//purpose: returns the damage of the Player
//return: integer
int Enemy::combat(Player* player) {
	int num = (rand() % 2);
	if (num == 0) {
		int damage = ceil((100.0/(100+player->getDef())) * atk);
		player->addHp(-damage);
		return damage;
	} else return 0;
} //combat(Player*)

//purpose: returns the number of gold that the enemy will drop when he dies
//return: integer
int Enemy::dropGold() {
  int num = (rand() % 1);
	if (num == 0) return 1;
	else return 2;
}

//getter of movement
int Enemy::getMovement() {return movement;}

//adder of movement
void Enemy::addMovement() {movement++;}
