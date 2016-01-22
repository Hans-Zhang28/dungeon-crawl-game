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
    else if(dir == "se")
        return theGrid[r+1][c+1];
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
            
            if(neighbourCell->getType() == "RH")
            {
                if(getSawRH())
                    notification->notifyAction("and sees RH.");
                else
                {
                    setSawRH();
                    notification->notifyAction("and sees an unknown potion.");
                }
            }
            else if(neighbourCell->getType() == "BA")
            {
                if(getSawBA())
                    notification->notifyAction("and sees BA.");
                else
                {
                    setSawBA();
                    notification->notifyAction("and sees an unknown potion.");
                }
            }
            else if(neighbourCell->getType() == "BD")
            {
                if(getSawBD())
                    notification->notifyAction("and sees BD.");
                else
                {
                    setSawBD();
                    notification->notifyAction("and sees an unknown potion.");
                }
            }
            else if(neighbourCell->getType() == "PH")
            {
                if(getSawPH())
                    notification->notifyAction("and sees PH.");
                else
                {
                    setSawPH();
                    notification->notifyAction("and sees an unknown potion.");
                }
            }
            else if(neighbourCell->getType() == "WA")
            {
                if(getSawWA())
                    notification->notifyAction("and sees WA.");
                else
                {
                    setSawWA();
                    notification->notifyAction("and sees an unknown potion.");
                }
            }
            else if(neighbourCell->getType() == "WD")
            {
                if(getSawWD())
                    notification->notifyAction("and sees WD.");
                else
                {
                    setSawWD();
                    notification->notifyAction("and sees an unknown potion.");
                }
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
        if((neighbourCell->getState() == 'H') && (neighbourCell->getState() == 'W')
            && (neighbourCell->getState() == 'O') && (neighbourCell->getState() == 'L') 
            && (neighbourCell->getState() == 'D')) // human or dwarf or orc or halfling or dragon
        {
            int dropHp=neighbourCell->combat(player); // attack player
            if(dropHp > 0) // if enemy attack player successfully, update action.
                notification->notifyAction(neighbourCell->getState()+" deals "+dropHp+"damage to PC.");
            else // fails attack
                notification->notifyAction(neighbourCell->getState()+"miss");
            neighbourCell->addMovement(); // movement + 1
        }
        else if(neighbourCell->getState() == 'E') // Elf
        {
            // first attack
            int dropHp=neighbourCell->combat(player);
            if(dropHp > 0) // if enemy attack player successfully
                notification->notifyAction(neighbourCell->getState()+" deals "+dropHp+"damage to PC.");
            else // fails attack
                notification->notifyAction(neighbourCell->getState()+"miss");
            // second attack
            dropHp=neighbourCell->combat(player);
            if(dropHp > 0) // if enemy attack player successfully
                notification->notifyAction(neighbourCell->getState()+" deals "+dropHp+"damage to PC.");
            else // fails attack
                notification->notifyAction(neighbourCell->getState()+"miss");
            neighbourCell->addMovement(); // movement + 1
        }
        else if((neighbourCell->getState() == 'G') && (neighbourCell->getAmount() == 6)) // dragon hoard
        {
            Dragon * dragon=neighbourCell->getDragon(); // the dragon associated to the dragon hoard
            if(!dragon) // when dragon exist
            {
                int dropHp=dragon->combat(player);
                if(dropHp > 0) // if enemy attack player successfully
                    notification->notifyAction("D deals "+dropHp+"damage to PC.");
                else // fails attack
                    notification->notifyAction("D miss");
            }    
        }
        else if(neighbourCell->getState() == 'M') // merchant
        {
            if(!neutral)
            {
                int dropHp=neighbourCell->combat(player); // attack player
                if(dropHp > 0) // if enemy attack player successfully, update action.
                    notification->notifyAction(neighbourCell->getState()+" deals "+dropHp+"damage to PC.");
                else // fails attack
                    notification->notifyAction(neighbourCell->getState()+"miss");
                neighbourCell->addMovement(); // movement + 1
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
    else if(dir == "se")
        return "Southeast";
}

// purpose:
void Game::change(string com1, string com2="")
{
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
            prevState=tmpState;
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
            // if dragon hoard, but dragon exist, cannot walk on it.
            if((tmpCell->getAmount() == 6) && (tmpCell->getDragon()))            {
                notification->notifyAction("Sorry, PC cannot pick up the gold before dragon is dead.");
            }
            else
            {
                int pr=player->getR(), pc=player->getC(); // the player's coordinates
                int tr=tmpCell->getR(), tc=tmpCell->getC(); // the coordinates of the cell the player wants to walk on.
                int amount=tmpCell->getAmount();
                player->addGold(amount); // player add gold to its account
                delete tmpCell; // delete the Gold Cell
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
                string action="PC gains "+amt+" gold(s)";
                notification->notifyAction(action); 
            }
        }// check the new posn's neighbour, update action if sth exists.
        // if player go the stair of the current floor
        else if(tmpCell->getState() == '\\')
        {
            isPass=true; // player pass the current level
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
            notification->notifyAction("PC finishes the current level :)"); 
        }
        // if player want to go to invalid direction.
        else
        {
            notification->notifyAction("Sorry, invalid move.");
        }
    }
    // check if there is something surrounding the player
    checkNeighbour(player);
}
