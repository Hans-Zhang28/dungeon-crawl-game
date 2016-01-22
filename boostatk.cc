#include "boostatk.h"
//#include "temppotion.h"

using namespace std;


// ctor
boostAtk::boostAtk(Player & player): tempPotion(player){}


// dtor
boostAtk::~boostAtk(){delete &origPlayer;}


// purpose: player attack enemy when user enter "a <direction>"
// returns: the hp drop of enemy.
int boostAtk::combat(Enemy *enemy)
{
    return origPlayer.combat(enemy);
} 


// purpose: getter for atk
// returns: the value of atk
int boostAtk::getAtk()
{
    return origPlayer.getAtk()+5;
}    


// purpose: getter for hp
// returns: the value of hp
int boostAtk::getHp()
{
    return origPlayer.getHp();
}


// purpose: getter for def
// returns: the value of def
int boostAtk::getDef()
{
    return origPlayer.getDef();
}


// purpose: getter for gold
// returns: the value of gold
int boostAtk::getGold()
{
    return origPlayer.getGold();
}


// purpose: adder for gold
void boostAtk::addGold(int amount)
{
    origPlayer.addGold(amount);
}


// purpose: adder for hp
void boostAtk::addHp(int hp)
{
    origPlayer.addHp(hp);
}


// purpose: getter for state
// returns: the state of the Cell
char boostAtk::getState() 
{
    return origPlayer.getState();
}


// purpose: setter for state
void boostAtk::setState(char newstate) 
{
    origPlayer.setState(newstate);
}


// purpose: setter for the coordinate which are row and column
void boostAtk::setCoords(const int newr, const int newc) 
{
    origPlayer.setCoords(newr, newc);
}
	

// purpose: getter for c
// returns: value of c
int boostAtk::getC() 
{
    return origPlayer.getC();
}


// purpose: getter for r
// returns: value of r
int boostAtk::getR() 
{
    return origPlayer.getR();
}


 
