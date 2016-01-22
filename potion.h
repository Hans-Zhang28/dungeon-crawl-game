#ifndef __POTION_H__
#define __POTION_H__
#include "cell.h"
#include <string>

class Potion : public Cell {
	std::string type; //type of the potion

	public:
	Potion(int r, int c, char state, std::string type); //ctor
	std::string getType(); //getter for type
};

#endif
