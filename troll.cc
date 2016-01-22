#include "troll.h"
#include "player.h"

using namespace std;


const int HPMAX=120;


// ctor
Troll::Troll(int r, int c, char state): Player(r, c, state, 120, 25, 15, 0){}


// purpose: adder for hp, hp is capped at 120 HP
void Troll::addHp(int hp)
{
    hp += hp;
		if(hp > HPMAX)
        hp = HPMAX;
    if(this->hp < 0)
        this->hp = 0;
}
