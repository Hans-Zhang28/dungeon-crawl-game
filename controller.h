#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <string>
#include "game.h"
#include "view.h"
#include <fstream>

class Controller: public GameNotification
{
    Game *game;
    View *td;
    int floor; // the floor the player is currently in.
       // add in uml
    std::string action; // the cumulated action
    
    
    bool checkDead(); // check if the player is dead.
    bool checkPass(); // check if the player has reached the stair of current floor
    
    void printstatus();// print the last 5 lines
    public:
    Controller(); // ctor
    ~Controller(); // dtor
    void play(std::string filename, bool haveArg); // plays the game, takes in commands from user and interact with Game and View.
    // uml mistake
    void notify(int r, int c, char state);// called by Game, notify View of the change
    void notifyAction(std::string act); // called by Game, update action
    
};

#endif
