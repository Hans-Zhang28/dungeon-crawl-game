#include "vampire.h"
#include "enemy.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "player.h"

using namespace std;


// ctor
Vampire::Vampire(int r, int c, char state): Player(r, c, state, 50, 25, 25, 0){}


// purpose: vampire attack enemy 
// returns: the hp drop of enemy.
int Vampire::combat(Enemy *enemy)
{
    float result; // the original result
    int damage; // final ceiling answer
    int num=rand()%2; // generate a random number between 0 and 1
    result = ((100.0 / (100 + enemy->getDef())) * atk);
    damage=ceil(result);
    if((enemy->getState() == 'L') && (num == 0)) // Vampire have 50% chance to miss when he attack halfling.
        return 0;
    else if(enemy->getState() == 'W') // Vampire loses 5 hp when attack Dwarf
        addHp(-5);
    else // Vampire gains 5 hp when attack enemies other than Dwarf
        addHp(5);
    enemy->addHp(-damage); // enemy is attacked and reset its Hp.
    return damage;
}
