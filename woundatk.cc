#include "woundatk.h"
//#include "temppotion.h"

using namespace std;

// ctor
woundAtk::woundAtk(Player & player): tempPotion(player){}
 
 
//dtor
woundAtk::~woundAtk(){delete &origPlayer;}


// purpose: player attack enemy when user enter "a <direction>"
// returns: the hp drop of enemy.
int woundAtk::combat(Enemy *enemy)
{
    return origPlayer.combat(enemy);
} 


// purpose: getter for atk
// returns: the value of atk
int woundAtk::getAtk()
{
    return origPlayer.getAtk()-5;
}    


// purpose: getter for hp
// returns: the value of hp
int woundAtk::getHp()
{
    return origPlayer.getHp();
}


// purpose: getter for def
// returns: the value of def
int woundAtk::getDef()
{
    return origPlayer.getDef();
}


// purpose: getter for gold
// returns: the value of gold
int woundAtk::getGold()
{
    return origPlayer.getGold();
}


// purpose: adder for gold
void woundAtk::addGold(int amount)
{
    origPlayer.addGold(amount);
}


// purpose: adder for hp
void woundAtk::addHp(int hp)
{
    origPlayer.addHp(hp);
}


// purpose: getter for state
// returns: the state of the Cell
char woundAtk::getState() 
{
    return origPlayer.getState();
}


// purpose: setter for state
void woundAtk::setState(char newstate) 
{
    origPlayer.setState(newstate);
}


// purpose: setter for the coordinate which are row and column
void woundAtk::setCoords(const int newr, const int newc) 
{
    origPlayer.setCoords(newr, newc);
}
	

// purpose: getter for c
// returns: value of c
int woundAtk::getC() 
{
    return origPlayer.getC();
}


// purpose: getter for r
// returns: value of r
int woundAtk::getR() 
{
    return origPlayer.getR();
}

