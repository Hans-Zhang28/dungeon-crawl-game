#include "controller.h"
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(0));
	Controller c; // create a controller
	if(argc == 2) // if we read in floor which has all things generated
	{
        string argfile=argv[1];
        c.play(argfile, true);
    }
    else   // if we randomly generate our own items
    {
        c.play("emptyboard.txt", false); // play the game
    }   
}
