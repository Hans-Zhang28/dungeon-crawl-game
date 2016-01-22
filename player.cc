#include "player.h"
#include <string>
#include "enemy.h"
#include <cmath>
#include <cstdlib>
#include "cell.h"

using namespace std;

Player::Player(int r, int c, char state, int hp, int atk, int def, int gold)
                : Cell(r, c, state), hp(hp), atk(atk), def(def), gold(gold){}

// dtor
Player::~Player(){};    
    
    
// purpose: player attack enemy when user enter "a <direction>"
// returns: the hp drop of enemy.
int Player::combat(Enemy *enemy)
{
    float result; // the original result
    int damage; // final ceiling answer
    int num=rand()%2; // generate a random number between 0 and 1
    result = ((100.0 / (100 + enemy->getDef())) * atk);
    damage=ceil(result);
    if((enemy->getState() == 'L') && (num == 0)) // player have 50% chance to miss when he attack halfling.
        return 0;
    enemy->addHp(-damage); // enemy is damaged, 
    return damage; 
} 


// purpose: getter for atk
// returns: the value of atk
int Player::getAtk()
{
    return atk;
}    


// purpose: getter for hp
// returns: the value of hp
int Player::getHp()
{
    return hp;
}


// purpose: getter for def
// returns: the value of def
int Player::getDef()
{
    return def;
}


// purpose: getter for gold
// returns: the value of gold
int Player::getGold()
{
    return gold;
}


// purpose: adder for gold
void Player::addGold(int amount)
{
    gold+=amount;
}


// purpose: adder for hp
void Player::addHp(int hp)
{
    this->hp+=hp;
    if(this->hp < 0)
        this->hp=0;
}


// adder for atk
void Player::addAtk(int atk)
{
    this->atk+=atk;
    if(this->atk < 0)
        this->atk=0;
}


// adder for def
void Player::addDef(int def)
{
    this->def+=def;
    if(this->def < 0)
        this->def=0;
} 
