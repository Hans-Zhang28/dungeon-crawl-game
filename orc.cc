#include "cell.h"
#include "orc.h"
#include "enemy.h"
#include "player.h"
#include <cstdlib>
#include <cmath>

//default ctor
Orc::Orc(int r, int c, char state) 
	:Enemy(r,c,state,180,30,25){}


//Purpose: causes the damage from the player character
//Return: void
int Orc::combat(Player* player) {
	int num = (rand() % 2);
	if (num == 0) {
		int damage = ceil((100.0/(100+player->getDef())) * getAtk());
	//g means the player character goblin
		if (player->getState() == 'g') {
			damage = ceil( 1.5 * damage );
			player->addHp(-damage); 
		} else { 
			player->addHp(-damage);
		}
		return damage;
	} else return 0;
}//combat(Player*)
