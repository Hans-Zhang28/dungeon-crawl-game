#include "cell.h"
#include "potion.h"
#include <string>

using namespace std;

//default ctor
Potion::Potion(int r, int c, char state, string type) 
	: Cell(r,c,state), type(type) {} 

//getter for type
string Potion::getType() {return type;} //getType()
