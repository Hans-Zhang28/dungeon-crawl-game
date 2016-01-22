#include "controller.h"
#include <string>
#include "game.h"
#include "textdisplay.h"
#include <iostream>
#include "player.h"
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;


// purpose: check if the player is dead.
// returns: true if player is dead, false otherwise.
bool Controller::checkDead()
{
    return game->getPlayer()->getHp() <= 0;
}

// purpose: check if the player has reached the stair of the current floor
// returns: true if player has reached the stair of the current floor, false otherwise.
bool Controller::checkPass()
{
    return game->getPass();
}


// ctor
Controller::Controller(): game(0), td(0), floor(1), action(""){}


// dtor
Controller::~Controller()
{
    if(game) // when game is allocated on heap
        delete game;
    if(td) // when td is allocated on heap
        delete td;
}


// purpose: plays the game, takes in commands from user and interact with Game and View.
void Controller::play(string filename, bool haveArg)
{
    string cmd;
    string dir; // direction of enemy or potion
    //bool quit; // check if the user want to quit the game
    bool isset=false; // check if player is set
    bool playing=false; // check if game is playing
    ifstream file(filename.c_str());

    while(1)
    {
        
        if(!isset) // set up player
        {
            cout << "Please choose a race: s(Shade), d(Drow), v(Vampire), g(Goblin), t(Troll)" << endl;
            cin >> cmd;
            // if player entered the correct race
            if((cmd == "s") || (cmd == "d") || (cmd == "v") || (cmd == "g") || (cmd == "t")) 
            {
                if(td) // delete old view when possible 
                    delete td;
                td=new TextDisplay(numRows, numCols);
                if(game) // delete old game when possible
                    delete game;
                game=new Game(this);
                game->init(cmd, this, file, haveArg); // initialize the game board with all items on it
                td->print(cout); // print the initialized game.
                action=action+"Player character has spawned.";
                printstatus(); // print the last 4 lines of game info.
                isset=true;
                playing=true;
            }
            else
                cout << "This race does not exist. Please choose again ^_^";
        }        
        else if(cmd == "r") // restart game
        {
            playing=false;
            isset=false;
            floor=1;
            file.close();
            file.clear();
            file.open(filename.c_str());
            continue;
        }
        else if((cmd == "q") || cin.eof()) // player want to quit
        {
            break;
        }
        else if(((cmd == "u") || (cmd == "a")) && playing) // player combat or drink potion
        {
            cin >> dir;
            // when invalid input of dir
            if(!((dir == "no") || (dir == "so") || (dir == "ea") || (dir == "we") 
            || (dir == "ne") || (dir == "nw") || (dir == "se") || (dir == "sw")))
            {
                cout << "Wrong direction. Please enter again: ";
                continue;
            }
            game->change(cmd, dir); // tell Game that user make an action.
            td->print(cout); // print the game after the command.
            printstatus(); // print the last 4 lines of game info.
            if(checkDead()) // when player is dead
            {
                cout << "You lose!!!" << endl;
                int score=game->getPlayer()->getGold();
                if(game->getPlayer()->getState() == 's')
                    cout << "Your score is: " << ceil(score*1.5) << endl;
                else
                    cout << "Your score is: " << score << endl;
                cout << "Would you like to play again? Press r to play again or press q to quit." << endl;
                playing=false;
            }
            else if(checkPass() && (floor == 5)) // when player wins
            {
                cout << "You win!!!" << endl;
                int score=game->getPlayer()->getGold();
                if(game->getPlayer()->getState() == 's')
                    cout << "Your score is: " << ceil(score*1.5) << endl;
                else
                    cout << "Your score is: " << score << endl;
                cout << "Would you like to play again? Press r to play again or press q to quit." << endl;
                playing=false;
            }
            else if(checkPass() && (floor <= 4)) // when player reaches the stair for floor 1-4
            {
                delete td;
                td=new TextDisplay(numRows, numCols);
                game->clearGame();
                game->init("", this, file, haveArg);
                floor++;
                td->print(cout); // print the new floor
                action=action+"Player character has spawned on the next floor.";
                printstatus(); // print the last 4 lines of game info.
            }
        }
        else if(((cmd == "no") || (cmd == "so") || (cmd == "ea") || (cmd == "we") 
        || (cmd == "ne") || (cmd == "nw") || (cmd == "se") || (cmd == "sw")) && playing)
        {
            game->change(cmd); // tell Game that user make an action.
            td->print(cout); // print the game after the command.
            printstatus(); // print the last 4 lines of game info.
            if(checkDead()) // when player is dead
            {
                cout << "You lose!!!" << endl;
                int score=game->getPlayer()->getGold();
                if(game->getPlayer()->getState() == 's')
                    cout << "Your score is: " << ceil(score*1.5) << endl;
                else
                    cout << "Your score is: " << score << endl;
                cout << "Would you like to play again? Press r to play again or press q to quit." << endl;
                playing=false;
            }
            else if(checkPass() && (floor == 5)) // when player wins
            {
                cout << "You win!!!" << endl;
                int score=game->getPlayer()->getGold();
                if(game->getPlayer()->getState() == 's')
                    cout << "Your score is: " << ceil(score*1.5) << endl;
                else
                    cout << "Your score is: " << score << endl;
                cout << "Would you like to play again? Press r to play again or press q to quit." << endl;
                playing=false;
            }
            else if(checkPass() && (floor <= 4)) // when player reaches the stair for floor 1-4
            {
                delete td;
                td=new TextDisplay(numRows, numCols);
                action="";
                game->clearGame();
                game->init("", this, file, haveArg);
                floor++;
                td->print(cout); // print the new floor
                action=action+"Player character has spawned on the next floor.";
                printstatus(); // print the last 4 lines of game info.
            }
        }
        else
        {
            cout << "Wrong command. Please enter again: ";
        }
        if(isset)
        {
            // prompt the player to enter command 
            cout << "Please enter a command: " << endl;
            //cout << "no, so, we, ea, nw, ne, sw, se: move player to the direction" << endl;
            //cout << "u <direction> : use potion" << endl << "a <direction> : attack enemy" << endl; 
            //cout << "r : restart game " << endl << "q : quit game" << endl;
            // let user to enter command.
            cin >> cmd;
        }
        action=""; // reset action
    }
}

// purpose: called by Game, notify View of the change
void Controller::notify(int r, int c, char state)
{
    td->notify(r, c, state);
}

// purpose: called by Game, update action.
void Controller::notifyAction(string act) 
{
    if(action == "")
        action=act;
    else if(act.substr(0, 3) == "and")
        //ex: PC moves East. -> PC moves East and sees an unknown potion.
        action=action.replace(action.length()-1, 1, " ")+act; 
    else
        action=action + " " + act;   
}


// purpose: print the last 4 line of the display (the text part)
void Controller::printstatus() 
{
    string race;
    int len;
    // translate the state of player to a string race
    if(game->getPlayer()->getState() == 's')
    {
        race = "Shade";
        len=5;
    }
    else if(game->getPlayer()->getState() == 'd')
    {
        race = "Drow";
        len=4;
    }
    else if(game->getPlayer()->getState() == 'v')
    {
        race = "Vampire";
        len=7;
    }
    else if(game->getPlayer()->getState() == 'g')
    {
        race = "Goblin";
        len=6;
    }
    else
    {
        race = "Troll";
        len=5;
    }
    cout << "Race: " << race << " Gold: " 
    << left << setw(56-len) << setfill(' ') << game->getPlayer()->getGold() << "Floor " << floor << endl;
    cout << "HP: " << game->getPlayer()->getHp() << endl;
    cout << "Atk: " << game->getPlayer()->getAtk() << endl;
    cout << "Def: " << game->getPlayer()->getDef() << endl;
    cout << "Action: " << action << endl;
}

