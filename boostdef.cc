#include "boostdef.h"
//#include "temppotion.h"

using namespace std;


// ctor
boostDef::boostDef(Player & player): tempPotion(player){}


// dtor
boostDef::~boostDef(){delete &origPlayer;}


// purpose: player attack enemy when user enter "a <direction>"
// returns: the hp drop of enemy.
int boostDef::combat(Enemy *enemy)
{
    return origPlayer.combat(enemy);
} 


// purpose: getter for atk
// returns: the value of atk
int boostDef::getAtk()
{
    return origPlayer.getAtk();
}    


// purpose: getter for hp
// returns: the value of hp
int boostDef::getHp()
{
    return origPlayer.getHp();
}


// purpose: getter for def
// returns: the value of def
int boostDef::getDef()
{
    return origPlayer.getDef()+5;
}


// purpose: getter for gold
// returns: the value of gold
int boostDef::getGold()
{
    return origPlayer.getGold();
}


// purpose: adder for gold
void boostDef::addGold(int amount)
{
    origPlayer.addGold(amount);
}


// purpose: adder for hp
void boostDef::addHp(int hp)
{
    origPlayer.addHp(hp);
}


// purpose: getter for state
// returns: the state of the Cell
char boostDef::getState() 
{
    return origPlayer.getState();
}


// purpose: setter for state
void boostDef::setState(char newstate) 
{
    origPlayer.setState(newstate);
}


// purpose: setter for the coordinate which are row and column
void boostDef::setCoords(const int newr, const int newc) 
{
    origPlayer.setCoords(newr, newc);
}
	

// purpose: getter for c
// returns: value of c
int boostDef::getC() 
{
    return origPlayer.getC();
}


// purpose: getter for r
// returns: value of r
int boostDef::getR() 
{
    return origPlayer.getR();
}



