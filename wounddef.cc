#include "wounddef.h"
#include "temppotion.h"
#include "player.h"

using namespace std;

// ctor
woundDef::woundDef(Player & player): tempPotion(player){}


//dtor
woundDef::~woundDef(){delete &origPlayer;}



// purpose: player attack enemy when user enter "a <direction>"
// returns: the hp drop of enemy.
int woundDef::combat(Enemy *enemy)
{
    return origPlayer.combat(enemy);
} 


// purpose: getter for atk
// returns: the value of atk
int woundDef::getAtk()
{
    return origPlayer.getAtk();
}    


// purpose: getter for hp
// returns: the value of hp
int woundDef::getHp()
{
    return origPlayer.getHp();
}


// purpose: getter for def
// returns: the value of def
int woundDef::getDef()
{
    return origPlayer.getDef()-5;
}


// purpose: getter for gold
// returns: the value of gold
int woundDef::getGold()
{
    return origPlayer.getGold();
}


// purpose: adder for gold
void woundDef::addGold(int amount)
{
    origPlayer.addGold(amount);
}


// purpose: adder for hp
void woundDef::addHp(int hp)
{
    origPlayer.addHp(hp);
}


// purpose: getter for state
// returns: the state of the Cell
char woundDef::getState() 
{
    return origPlayer.getState();
}


// purpose: setter for state
void woundDef::setState(char newstate) 
{
    origPlayer.setState(newstate);
}


// purpose: setter for the coordinate which are row and column
void woundDef::setCoords(const int newr, const int newc) 
{
    origPlayer.setCoords(newr, newc);
}
	

// purpose: getter for c
// returns: value of c
int woundDef::getC() 
{
    return origPlayer.getC();
}


// purpose: getter for r
// returns: value of r
int woundDef::getR() 
{
    return origPlayer.getR();
}


