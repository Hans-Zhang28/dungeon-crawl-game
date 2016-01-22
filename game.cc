#include "game.h"
#include "cell.h"
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <fstream>
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"
#include "treasure.h"
#include "potion.h"
#include "controller.h"
#include "player.h"
#include "enemy.h"

using namespace std;


//ctor
Game::Game(GameNotification* gameNotification) 
	: sizeChamber1(0), sizeChamber2(0), sizeChamber3(0), sizeChamber4(0), 
	  sizeChamber5(0), pass(false), prevState('.'), theGrid(NULL),  player(NULL), 
		notification(gameNotification), neutral(true),useRH(false), useBA(false), 
		useBD(false), usePH(false), useWA(false), useWD(false), move_count(0), tmpChamber(0) {}



//purpose: if the player is dead return true, otherwise return false
//return: bool
bool Game::isDead() { return player->getHp() <= 0; } //isDead()




//purpose: used to be called by controller to pass commands to help the
//         player to make action, com1 may be the direction, or action commad like
//         u, a or specification of races, com2 is direction or nothing.
//return: void 
void Game::change(string com1, string com2) {
	// at the beginning of the turn, update move_count
  move_count++;
  Cell * tmpCell;
  
  if(com2 == "")
  {
    tmpCell=findNeighbour(player, com1);
      // if player move to an empty floor tile or door or passage way
     if((tmpCell->getState() == '.') || (tmpCell->getState() == '+') || (tmpCell->getState() == '#'))
        {
            int pr=player->getR(), pc=player->getC(); // the player's coordinates
            int tr=tmpCell->getR(), tc=tmpCell->getC(); // the coordinates of the cell that the player wants to walk on.
            // switch the pointer of the 2 changing cells(one points to the player, 
            // one points to the cell that the player wants to move on)
            Cell * tmp = theGrid[tr][tc];
            theGrid[tr][tc] = theGrid[pr][pc];
            theGrid[pr][pc] = tmp;
            // switch the coordinates of the 2 cells.
            player->setCoords(tr, tc);
            tmpCell->setCoords(pr, pc);
            // switch prevState and tmpCell's state
            char tmpstate = tmpCell->getState();
            tmpCell->setState(prevState);
            prevState=tmpstate;
            // notify controller of the change
            notification->notify(pr, pc, tmpCell->getState()); // the change of the previous position of player
            notification->notify(tr, tc, '@'); // the change of the new position of player
            // notify controller of the player's action(a string)
            string action="PC moves "+convertDir(com1)+".";
            notification->notifyAction(action); 
            
        }// check the new posn's neighbour, update action if sth exists.
        // if player go to pick up the gold.
        else if(tmpCell->getState() == 'G') 
        {
						//cast the Cell to Treasure
						Treasure* tmpTreasure = static_cast<Treasure*>(tmpCell);
            // if dragon hoard, but dragon exist, cannot walk on it. 
            if((tmpTreasure->getAmount() == 6) && (tmpTreasure->getDragon()))            {
                notification->notifyAction("Sorry, PC cannot pick up the gold before dragon is dead.");
            }
            else
            {
                int pr=player->getR(), pc=player->getC(); // the player's coordinates
                int tr=tmpTreasure->getR(), tc=tmpTreasure->getC(); // the coordinates of the cell the player wants to walk on.
                int amount=tmpTreasure->getAmount();
                player->addGold(amount); // player add gold to its account
                delete tmpTreasure; // delete the Gold Cell
                theGrid[tr][tc] = player; // the gold's position now becames the player
                player->setCoords(tr, tc); // set coordinates for player
                theGrid[pr][pc]=new Cell(pr, pc, '.'); // the player's previous position now has a new Cell '.'
                prevState='.';
                // notify controller of the change
                notification->notify(pr, pc, '.'); // the change of the previous position of player
                notification->notify(tr, tc, '@'); // the change of the new position of player
                // notify controller of the player's action(a string)
                stringstream ss;
                string amt;
                ss << amount;
                ss >> amt;
                ss.str("");
                ss.clear();
                string action="PC gains "+amt+" gold(s).";
                notification->notifyAction(action); 
            }
        }// check the new posn's neighbour, update action if sth exists.
        // if player go the stair of the current floor
        else if(tmpCell->getState() == '\\')
        {
            pass=true; // player pass the current level
            int pr=player->getR(), pc=player->getC(); // the player's coordinates
            int tr=tmpCell->getR(), tc=tmpCell->getC(); // the coordinates of the cell that the player wants to walk on.
            delete tmpCell; // delete the stair Cell
            theGrid[tr][tc] = player; // the stair's position now becames the player
            player->setCoords(tr, tc); // set coordinates for player
            theGrid[pr][pc]=new Cell(pr, pc, '.'); // the player's previous position now has a new Cell '.'
            prevState='.';
            // notify controller of the change
            notification->notify(pr, pc, '.'); // the change of the previous position of player
            notification->notify(tr, tc, '@'); // the change of the new position of player
            // notify controller of the player's action(a string)
            notification->notifyAction("PC finishes the current level :)."); 
        }
        // if player want to go to invalid direction.
        else
        {
            notification->notifyAction("Sorry, invalid move.");
        }
    }

	//player chooses to attack the enemy
	if (com1 == "a") {
		int damage_e; //damage that player deals with enemy
		string damage_str;
		string hp_str;
		string action = ""; //showing the action that will pass to the controller
		Cell* enemy = findNeighbour(player, com2);
		char state_e = enemy->getState();
			if (state_e == 'H' || state_e == 'O' || state_e == 'D' || state_e == 'E' || 
					state_e == 'M' || state_e == 'L' || state_e == 'W') {
				Enemy* tmpEnemy = static_cast<Enemy*>(enemy);
				//the merchant is attacked then set neutral to false
				if (state_e == 'M') neutral = false;
					damage_e = player->combat(tmpEnemy);
					//if PC is attacking Halfling, combat function may return 0
					if (damage_e != 0) {
					 	damage_str = int_str(damage_e); //transfer the integer damage to string transfer
						action = action + "PC deals " + damage_str + " damage to ";
						hp_str = int_str(tmpEnemy->getHp()); //transfer the integer hp of enemy to string transfer
						action = action + state_e + " (" + hp_str + "HP).";
						notification->notifyAction(action);
						//check the enemy is dead or not
						if (tmpEnemy->isDead()) {
							int r_enemy = tmpEnemy->getR();
							int c_enemy = tmpEnemy->getC();
							theGrid[r_enemy][c_enemy] = new Cell(r_enemy,c_enemy,'.');
							notification->notify(r_enemy,c_enemy,'.');
							//if the player is goblin then we will add 5 gold to it
							if (player->getState() == 'g') player->addGold(5);
							player->addGold(tmpEnemy->dropGold());
							delete tmpEnemy;
						} //if
					} else {
						notification->notifyAction("PC Miss >_< ");
					} //if..else (damage != 0)
			} else {
				notification->notifyAction("Invalid attack!! ");
			} //if..else if(state_e....
		} //if
		
	//player drinks potion
	if (com1 == "u") {
		Cell* potion = findNeighbour(player,com2);
		//if the neighbour on the direction user specified is not a Potion
		if (potion->getState() != 'P') {
			notification->notifyAction("Failed to get potion :( ");
		} else {
			Potion* tmpPotion = static_cast<Potion*>(potion);
			string type = tmpPotion->getType();
			int hpadd=10; // hp related value is 10
			int atkordef=5; //  atk or def related value is 5
			if(player->getState() == 'd') // if drow, all potion effect multiply by 1.5
			{
                hpadd=15;
                atkordef=8;
            }
			if (type == "RH")
            { 
                player->addHp(hpadd);
                if(!getUseRH()) // if RH is not used previously, set it to used.
                    setUseRH();
            }
			else if (type == "PH")
            {
                player->addHp(-hpadd);
                if(!getUsePH()) // if PH is not used previously, set it to used.
                    setUsePH();
            }
			else if (type == "BA") 
            {
                player->addAtk(atkordef);
                if(!getUseBA()) // if BA is not used previously, set it to used.
                    setUseBA();
            }
			else if (type == "BD") 
            {
                player->addDef(atkordef);
                if(!getUseBD()) // if BD is not used previously, set it to used.
                    setUseBD();
            }
			else if (type == "WA") 
            {
                player->addAtk(-atkordef);
                if(!getUseWA()) // if WA is not used previously, set it to used.
                    setUseWA();
            }
			else 
            {
                player->addDef(-atkordef);
                if(!getUseWD()) // if WD is not used previously, set it to used.
                    setUseWD();
            }
			//if we decorated our player we need to delete the player previoursly used
		    //	if (type != "RH" && type != "PH") delete prevPlayer;
			int r = tmpPotion->getR();
			int c = tmpPotion->getC();
			delete theGrid[r][c];
		  theGrid[r][c]	= new Cell(r,c,'.');
			notification->notify(r,c,'.');
			notification->notifyAction("PC uses " + type + ".");
		} //if..else
	} //if (com1 == "u")
	
	// if troll, add 5 hp every turn
	if(player->getState() == 't')
	   player->addHp(5);
	   
	// check potion, gold, enemies surrounding the player
	// detail of checkNeighour(Player*) see definition
  checkNeighbour(player);

	//enemies move
  for (int r = 0; r < numRows; ++r) {
		for (int c = 0; c < numCols; ++c) {
			Cell* enemy = theGrid[r][c];
			char state_e = enemy->getState();
			if (state_e == 'H' || state_e == 'O' ||  state_e == 'E' || state_e == 'M' || state_e == 'L' || state_e == 'W') {
				Enemy* tmpEnemy = static_cast<Enemy*>(enemy);
				if (tmpEnemy->getMovement() < move_count) {
					int r_e = tmpEnemy->getR();
					int c_e = tmpEnemy->getC();
					pair<int,int> tmp = make_pair(r_e,c_e);
					// check if enemy can move to a valid position.
					string dirarr[8]={"no", "so", "we", "ea", "nw", "ne", "sw", "se"}; // an array of direction string
					bool canMove=false; // a flag to check if enemy can move
					for(int i=0; i<8; i++) 
					{
              if(findNeighbour(tmpEnemy, dirarr[i])->getState() == '.')
              canMove=true;
          }
					if(canMove) // if enemy can move, then it changes position
					{
					   tmp = neighbour_loc(tmp); //location of Neighbour Cell
					   //swap tmpEnemy with one of its Neighbour Cell
			 		  Cell* tmpCell = tmpEnemy;
					   theGrid[r_e][c_e] = theGrid[tmp.first][tmp.second];
					   theGrid[tmp.first][tmp.second] = tmpCell; 
					   //swap the coordinates
					   theGrid[tmp.first][tmp.second]->setCoords(tmp.first,tmp.second);
					   theGrid[r_e][c_e]->setCoords(r_e,c_e);
					   tmpEnemy->addMovement();
					   notification->notify(r_e,c_e,'.');
					   notification->notify(tmp.first,tmp.second,state_e);
           }
           else // if enemy cannot move, then it stays where it was.
           	tmpEnemy->addMovement(); // movement + 1
			} 
		} //if
		else if (state_e == 'D')
		{	
			Enemy* tmpEnemy = static_cast<Enemy*>(enemy);
			if (tmpEnemy->getMovement() < move_count) tmpEnemy->addMovement();
		}
	} //for
} //for
} //init(string,string)




//purpose: helper function for generating a random valid location from five Chambers
//         the valid, when it is generating the location for stair we need to give it
//         the chamber of the player
//return: pair<int,int>
pair<int,int> Game::pop_loc(int player_room) {
	pair<int,int> location;
  while (true) {
  	int room = (rand() % 5);
		tmpChamber = room;
		if (room == player_room) continue; //if
		if (room == 0) location = Chamber1.at(rand() % sizeChamber1);	
		else if (room == 1) location = Chamber2.at(rand() % sizeChamber2);
  	else if (room == 2) location = Chamber3.at(rand() % sizeChamber3);
		else if (room == 3) location = Chamber4.at(rand() % sizeChamber4);
		else location = Chamber5.at(rand() % sizeChamber5); //if..else
		if (gameBoard[location.first][location.second] != '.') continue;
		else break; //if..else
	} //while
	return location;
} //pop_loc



//setter for pass
void Game::setPass() {pass = true;} //setPass()



//getter for pass
bool Game::getPass() {return pass;} //getPass()



//setter for prevState
void Game::setPrevState(char state) {
	prevState = state;
} //setPrevState(char)



//getter for prevState
char Game::getPrevState() {return prevState;} //getPrevState()



//purpose: frees the gameboard except player pointer, it is called by controller
//         when the player get to the new floor
//return: void
void Game::clearGame() {
	pass = false;
	prevState = '.';
	Player* tmp;
  move_count = 0;
	char race = player->getState();
	if (race == 's') tmp = new Shade(0,0,'s');
	else if (race == 'd') tmp = new Drow(0,0,'d');
	else if (race == 'v') tmp = new Vampire(0,0,'v');
	else if (race == 't') tmp = new Troll(0,0,'t');
	else tmp = new Goblin(0,0,'g'); //if..else
	tmp->addGold(player->getGold());
	tmp->addHp(player->getHp() - tmp->getHp());
	player = tmp;
	for (int r = 0; r < numRows; ++r) {
		for (int c = 0; c < numCols; ++c) {
			delete theGrid[r][c];
		} //for
		delete[] theGrid[r];
	} //for
	delete[] theGrid;
	theGrid=0; // reset to NULL
} //clearGame()




//purpose: generate the one of the valid location  to the location we provide randomly
//return: pair<int,int>
pair<int,int> Game::neighbour_loc(pair<int,int> loc) {
	pair<int,int> tmp = loc;
	while (true) {
		int val = (rand() % 8);
		if (val == 0) tmp.first++;
		else if (val == 1) tmp.first--;
  	else if (val == 2) tmp.second++;
		else if (val == 3) tmp.second--;
		else if (val == 4) {
			tmp.first++;
			tmp.second++;
		} else if (val == 5) {
			tmp.first++;
			tmp.second--;
		} else if (val == 6) {
			tmp.first--;
			tmp.second++;
		} else {
			tmp.first--;
			tmp.second--;
		} //if..else
		if ((theGrid == NULL && gameBoard[tmp.first][tmp.second] == '.') || 
				(theGrid != NULL && theGrid[tmp.first][tmp.second]->getState() == '.'))
		{
			break;
		} else{
			tmp = loc;
			continue;
		}
	} //while 
	return tmp;
} //neighbour_loc(pair<int,int>)




//setter for useRH
void Game::setUseRH() {useRH = true;}

//setter for useBA
void Game::setUseBA() {useBA = true;}

//setter for useBD
void Game::setUseBD() {useBD = true;}

//setter for usePH
void Game::setUsePH() {usePH = true;}

//setter for useWA
void Game::setUseWA() {useWA = true;}

//setter for useWD
void Game::setUseWD() {useWD = true;}

//getter for useRH
bool Game::getUseRH() {return useRH;}

//getter for useBA
bool Game::getUseBA() {return useBA;}

//getter for useBD
bool Game::getUseBD() {return useBD;}

//getter for usePH
bool Game::getUsePH() {return usePH;}

//getter for useWA
bool Game::getUseWA() {return useWA;}

//getter for useWD
bool Game::getUseWD() {return useWD;} 



// purpose: find the neighbour of cell in the given direction dir.
// returns: the neighbour in the given direction dir.
Cell * Game::findNeighbour(Cell* cell, string dir)
{
    int r=cell->getR();
    int c=cell->getC();
    if(dir == "no")
        return theGrid[r-1][c];
    else if(dir == "so")
        return theGrid[r+1][c];
    else if(dir == "we")
        return theGrid[r][c-1];
    else if(dir == "ea")
        return theGrid[r][c+1];
    else if(dir == "nw")
        return theGrid[r-1][c-1];
    else if(dir == "ne")
        return theGrid[r-1][c+1];
    else if(dir == "sw")
        return theGrid[r+1][c-1];
    else
        return theGrid[r+1][c+1];
}


// purpose: convert int to string
// returns: the string form of given int
string Game::int_str(int n)
{
    string str;
    stringstream intstr;
    intstr << n;
    intstr >> str;
    intstr.str("");
    intstr.clear();
    return str;
}

// purpose: first check if there are potion or gold within 1 block radius of player.
//          then check if there are enemies around, if yes, enemies attack player.
void Game::checkNeighbour(Player * player)
{
    string dirarr[8]={"no", "so", "we", "ea", "nw", "ne", "sw", "se"}; // an array of direction string
    // first check if there is potion or gold around
    for(int i=0; i<8; i++) 
    {
        Cell * neighbourCell=findNeighbour(player, dirarr[i]);
        if(neighbourCell->getState() == 'P') // player see a potion
        {
           Potion* tmpPotion = static_cast<Potion*>(neighbourCell); 
            if(tmpPotion->getType() == "RH")
            {
                if(getUseRH())
                    notification->notifyAction("and sees RH.");
                else
                    notification->notifyAction("and sees an unknown potion.");
            }
            else if(tmpPotion->getType() == "BA")
            {
                if(getUseBA())
                    notification->notifyAction("and sees BA.");
                else
                    notification->notifyAction("and sees an unknown potion.");
            }
            else if(tmpPotion->getType() == "BD")
            {
                if(getUseBD())
                    notification->notifyAction("and sees BD.");
                else
                    notification->notifyAction("and sees an unknown potion.");
            }
            else if(tmpPotion->getType() == "PH")
            {
                if(getUsePH())
                    notification->notifyAction("and sees PH.");
                else
                    notification->notifyAction("and sees an unknown potion.");
            }
            else if(tmpPotion->getType() == "WA")
            {
                if(getUseWA())
                    notification->notifyAction("and sees WA.");
                else
                    notification->notifyAction("and sees an unknown potion.");
            }
            else if(tmpPotion->getType() == "WD")
            {
                if(getUseWD())
                    notification->notifyAction("and sees WD.");
                else
                    notification->notifyAction("and sees an unknown potion.");
            }
        }
        else if(neighbourCell->getState() == 'G') 
        {
            notification->notifyAction("and sees a pile of gold.");
        }
        else
            continue;
        
    }
    // then if there are enemies, enemies will try to attack player.
    for(int i=0; i<8; i++)
    {
        Cell * neighbourCell=findNeighbour(player, dirarr[i]);
        if((neighbourCell->getState() == 'H') || (neighbourCell->getState() == 'W')
            || (neighbourCell->getState() == 'O') || (neighbourCell->getState() == 'L') 
            || (neighbourCell->getState() == 'D')) // human or dwarf or orc or halfling or dragon
        {
					Enemy* tmpEnemy = static_cast <Enemy*> (neighbourCell);
					if (tmpEnemy->getMovement() < move_count) {
            	int dropHp = tmpEnemy->combat(player); // attack player
            	string action="";
            	char state=neighbourCell->getState();
            	string damage=int_str(dropHp);
            	if(dropHp > 0)  // if enemy attack player successfully, update action.
            	{
               		action=action+state+" deals "+damage+" damage to PC.";
									notification->notifyAction(action);
            	}
            	else // fails attack
            	{
              	  action=action+state+" miss.";
              	  notification->notifyAction(action);
            	}
          	  tmpEnemy->addMovement(); // movement + 1
        	}
				}
        else if(neighbourCell->getState() == 'E') // Elf
        {
			    	Enemy* tmpEnemy = static_cast <Enemy*> (neighbourCell);
						if (tmpEnemy->getMovement() < move_count) {
            // first attack
            int dropHp=tmpEnemy->combat(player);
            string action="";
            char state=tmpEnemy->getState();
            string damage=int_str(dropHp);
            if(dropHp > 0) // if enemy attack player successfully
            {
                action=action+state+" deals "+damage+" damage to PC.";
								notification->notifyAction(action);
            }
            else // fails attack
            {
                action=action+state+" miss.";
                notification->notifyAction(action);
            }
            // second attack
            if(player->getState() != 'd') // if droll, won't attack twice
            {
                dropHp=tmpEnemy->combat(player);
                string damage=int_str(dropHp);
                action="";
                if(dropHp > 0) // if enemy attack player successfully
                {
                    action=action+state+" deals "+damage+" damage to PC.";
				   				  notification->notifyAction(action);
                }
                else // fails attack
                {
                    action=action+state+" miss.";
                    notification->notifyAction(action);
                }
            }
            	tmpEnemy->addMovement(); // movement + 1
						}
        }
        else if(neighbourCell->getState() == 'G') {
			Treasure* tmpTreasure = static_cast <Treasure*> (neighbourCell);
			string action="";
			if (tmpTreasure->getAmount() == 6) // dragon hoard
        	{
            	Dragon * dragon=tmpTreasure->getDragon(); // the dragon associated to the dragon hoard
							if (dragon->getMovement() < move_count) {
            		if(dragon) // when dragon exist
            		{
                		int dropHp=dragon->combat(player);
                		string damage=int_str(dropHp);
                		if(dropHp > 0) // if enemy attack player successfully
                		{
                      	  action=action+"D deals "+damage+" damage to PC.";
													notification->notifyAction(action);
                  	}
                		else // fails attack
                		{
                      	  action=action+"D miss.";
              	    	    notification->notifyAction(action);
                  	}
										dragon->addMovement();
            		}
							}
        	}
				}
        else if(neighbourCell->getState() == 'M') // merchant
        {
			Enemy* tmpEnemy = static_cast <Enemy*> (neighbourCell);
			string action="";
			char state=tmpEnemy->getState();
            if(!neutral)
            {
                int dropHp=tmpEnemy->combat(player); // attack player
                string damage=int_str(dropHp);
                if(dropHp > 0) // if enemy attack player successfully, update action.
                {
                    action=action+state+" deals "+damage+" damage to PC.";
					notification->notifyAction(action);
                }
                else // fails attack
                {
                    action=action+state+" miss.";
                    notification->notifyAction(action);
                }
                tmpEnemy->addMovement(); // movement + 1
            }
        }
        else
        {
            continue;
        }
    }
    
}



// purpose: convert a 2 character string to a full string of direction.
// returns: the corresponding string of direction.
string Game::convertDir(string dir)
{
    if(dir == "no")
        return "North";
    else if(dir == "so")
        return "South";
    else if(dir == "we")
        return "West";
    else if(dir == "ea")
        return "East";
    else if(dir == "nw")
        return "Northwest";
    else if(dir == "ne")
        return "Northeast";
    else if(dir == "sw")
        return "Southwest";
    else
        return "Southeast";
}

//getter for player
Player* Game::getPlayer() {return player;}

//dtor
Game::~Game() {
	clearGame();
	if (player) delete player;
}




//purpose: called by Controller in response to initialization, requested
//         when the game is in the initializtion mode or when the floor is
//         changed.
//return: void
void Game::init(string race, GameNotification* gameNotification, ifstream& fileToRead, bool haveArg){
	//read the file of gameboard and allocate for the Chamber vector
	for(int r = 0; r < numRows; ++r) {
		for (int c = 0; c < numCols; ++c) {
			char state;
			fileToRead >> noskipws >> state;
			if (state == '\n') fileToRead >> noskipws >> state;
			gameBoard[r][c] = state;
			//allocate coordinates for Chamber1
			if (3 <= r && r <= 6) {
				if (3 <= c && c <= 28) {
	 				Chamber1.push_back(make_pair(r,c));
					sizeChamber1++;
 				} //if
			} //if
			//allocate coordinates for Chamber2
			if (3 <= r && r <= 6) {
				if (39 <= c && c <= 72) {
					if (state != ' ' && state != '+' && state != '|' && state != '-' && state != '#') {
						Chamber2.push_back(make_pair(r,c));
		  			sizeChamber2++;
					} //if
				} //if
			} //if
			if (7 <= r && r <= 12) {
				if (61 <= c && c <= 75) {
					Chamber2.push_back(make_pair(r,c));
					sizeChamber2++;
				} //if
			} //if
			//allocate cooordinates for Chamber3
			if (15 <= r && r <= 21) {
				if (4 <= c && c <= 24) {
	 				Chamber3.push_back(make_pair(r,c));
					sizeChamber3++;
	 			} //if
			} //if
  		//allocate coordinates for Chamber4
			if (10 <= r && r <= 12) {
				if (38 <= c && c <= 49) {
					Chamber4.push_back(make_pair(r,c));
					sizeChamber4++;
				} //if
			} //if
			//allocate coordinates for Chamber5
			if (16 <= r && r <= 21) {
				if (37 <= c && c <= 75) {
					if (state != ' ' && state != '+' && state != '|' && state != '-' && state != '#') {
						Chamber5.push_back(make_pair(r,c));
			  		sizeChamber5++;
					} //if
				} //if
			} //if
		}	//for
	} //for
	//if user does not pass in a file with anything set already
	if (!haveArg) {	
    // randomly generate items on gameBoard
    pair<int,int> location = pop_loc();
		//generate the player
		gameBoard[location.first][location.second]='@';
		//generate stair
		location = pop_loc(tmpChamber);
		gameBoard[location.first][location.second]='\\';
		//generate 10 potions
		for (int i = 0; i < 10; ++i) {
			location = pop_loc();
			int type = (rand() % 6);
			if (type == 0) 
				gameBoard[location.first][location.second] = '0';
			else if (type == 1) 
				gameBoard[location.first][location.second] = '1';
			else if (type == 2) 
				gameBoard[location.first][location.second] = '2';
			else if (type == 3) 
				gameBoard[location.first][location.second] = '3';
			else if (type == 4) 
				gameBoard[location.first][location.second] = '4';
			else
				gameBoard[location.first][location.second] = '5';
			//if..else
		} //for
		//generate gold
		for (int i = 0; i < 10; ++i) {
			location = pop_loc();
			int type = (rand() % 8);
			if (0 <= type && type <= 4) 
				gameBoard[location.first][location.second] = '7';
			else if (type == 5 || type == 6) 
				gameBoard[location.first][location.second] = '6';
			else if (type == 7) {
				gameBoard[location.first][location.second] = '9';
			    pair<int,int> loc_dragon = neighbour_loc(location);
			    gameBoard[loc_dragon.first][loc_dragon.second] = 'D';
			}
		  //if..else
		} //for 
		//generate 20 enemies
		for (int i = 0; i < 20; ++i) {
			location = pop_loc();
			int type = (rand() % 18);
			if (0 <= type && type <= 3) 
				gameBoard[location.first][location.second] = 'H';
			else if (4 <= type && type <= 6)
				gameBoard[location.first][location.second] = 'W';
			else if (7 <= type && type <= 11)
				gameBoard[location.first][location.second] = 'L';
			else if (12 == type || type == 13)
				gameBoard[location.first][location.second] = 'E';
			else if (14 == type || type == 15)
				gameBoard[location.first][location.second] = 'O';
			else
				gameBoard[location.first][location.second] = 'M';
		//if..else
		} //for 
	}

	//create Cell on theGrid according to the gameBoard we read in before
		theGrid = new Cell**[numRows];
		for (int r = 0; r < numRows; ++r) {
			theGrid[r] = new Cell*[numCols];
			for (int c = 0; c < numCols; ++c) {
				if (gameBoard[r][c] == '0') {
					theGrid[r][c] = new Potion(r,c, 'P', "RH");
					notification->notify(r,c, 'P');
				}
				if (gameBoard[r][c] == '1') {
					theGrid[r][c] = new Potion(r,c, 'P', "BA");
					notification->notify(r,c, 'P');
				}
				if (gameBoard[r][c] == '2') {
					theGrid[r][c] = new Potion(r,c, 'P', "BD");
					notification->notify(r,c, 'P');	
				}
				if (gameBoard[r][c] == '3') {
					theGrid[r][c] = new Potion(r,c, 'P', "PH");
					notification->notify(r,c, 'P');	
				}
				if (gameBoard[r][c] == '4') {
					theGrid[r][c] = new Potion(r,c, 'P', "WA");
					notification->notify(r,c, 'P');	
				}
				if (gameBoard[r][c] == '5') {
					theGrid[r][c] = new Potion(r,c, 'P', "WD");
					notification->notify(r,c, 'P');	
				}
				if (gameBoard[r][c] == '6') {	
					theGrid[r][c] = new Treasure(r,c, 'G', 1);
					notification->notify(r,c, 'G');	
				}
				if (gameBoard[r][c] == '7') {	
					theGrid[r][c] = new Treasure(r,c, 'G', 2);
					notification->notify(r,c, 'G');	
				}
				if (gameBoard[r][c] == '8') {	
					theGrid[r][c] = new Treasure(r,c, 'G', 4);
					notification->notify(r,c, 'G');	
				}
				if (gameBoard[r][c] == '9') {	
					theGrid[r][c] = new Treasure(r,c, 'G', 6);
					notification->notify(r,c, 'G');	
				}
				if (gameBoard[r][c] == 'H') {	
					theGrid[r][c] = new Human(r,c,'H');
					notification->notify(r,c,'H');	
				}
				if (gameBoard[r][c] == 'W') {	
					theGrid[r][c] = new Dwarf(r,c,'W');
					notification->notify(r,c,'W');	
				}
				if (gameBoard[r][c] == 'E') {	
					theGrid[r][c] = new Elf(r,c,'E');
					notification->notify(r,c,'E');	
				}
				if (gameBoard[r][c] == 'O') {	
					theGrid[r][c] = new Orc(r,c,'O');
					notification->notify(r,c,'O');	
				}
				if (gameBoard[r][c] == 'M') {	
					theGrid[r][c] = new Merchant(r,c,'M');
					notification->notify(r,c,'M');	
				}
				if (gameBoard[r][c] == 'D') {	
					theGrid[r][c] = new Dragon(r,c,'D');
					notification->notify(r,c,'D');	
				}
				if (gameBoard[r][c] == 'L') {	
					theGrid[r][c] = new Halfling(r,c,'L');
					notification->notify(r,c,'L');	
				}
				if (gameBoard[r][c] == '@') {
					if (player == NULL) {
						if (race == "s") player = new Shade(r,c,'s');
						else if (race == "d") player = new Drow(r,c,'d');
						else if (race == "v") player = new Vampire(r,c,'v');
						else if (race == "t") player = new Troll(r,c, 't');
						else player = new Goblin(r,c,'g'); //if..else
					} else {
						player->setCoords(r,c);
					}
						theGrid[r][c] = player;
						notification->notify(r,c,'@');
					}
				if (gameBoard[r][c] == '\\') {
					theGrid[r][c] = new Cell(r,c,'\\');
					notification->notify(r,c,'\\');	
				}
				if (gameBoard[r][c] == ' ') {
					theGrid[r][c] = new Cell(r,c,' ');
					notification->notify(r,c,' ');	
				}
				if (gameBoard[r][c] == '|') {
					theGrid[r][c] = new Cell(r,c,'|');
					notification->notify(r,c,'|');	
				}
				if (gameBoard[r][c] == '-') {
					theGrid[r][c] = new Cell(r,c,'-');
					notification->notify(r,c,'-');	
				}
				if (gameBoard[r][c] == '+') {
					theGrid[r][c] = new Cell(r,c,'+');
					notification->notify(r,c,'+');	
				}
				if (gameBoard[r][c] == '#') {
					theGrid[r][c] = new Cell(r,c,'#');
					notification->notify(r,c,'#');	
				}
				if (gameBoard[r][c] == '.') {
					theGrid[r][c] = new Cell(r,c,'.');
					notification->notify(r,c,'.');
				}
			} //for
		} //for
		//link Dragon with its hoard
		string dirarr[8]={"no", "so", "we", "ea", "nw", "ne", "sw", "se"}; // an array of direction string
		for (int r = 2; r < numRows - 2; ++r) {
			for (int c = 2; c < numCols - 2; ++c) {
				if (gameBoard[r][c] == 'D') {
    		// first check if there is potion or gold around
    			for(int i=0; i<8; i++) {
						Cell* tmp = findNeighbour(theGrid[r][c], dirarr[i]);
						//if the neighbour is a hoard
						if (tmp->getState() == 'G') {
							Treasure* tmpTreasure = static_cast <Treasure*> (tmp);
							//if the gold is a dragon hoard
							if (tmpTreasure->getAmount() == 6) {
								//if the dragon does not point to any dragon hoard
								if (tmpTreasure->getDragon() == NULL) {
									Dragon* tmpDragon = static_cast <Dragon*> (theGrid[r][c]);
									tmpTreasure->setDragon(tmpDragon);
									tmpDragon->setD_hoard(tmpTreasure);
								} //if
							} //if
						} //if
					} //for
				} //if
			} //for
		} //for
} //init
