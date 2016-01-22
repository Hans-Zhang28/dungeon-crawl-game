#ifndef __CELL_H__
#define __CELL_H__

class Game;

//const int maxNeighbours = 4;

class Cell {
	char state; //it is the current char representation of each Cell
	int r, c; //co-odinates of the Cell

  public:
	Cell(int r, int c, char state); //ctor
	virtual ~Cell(); //dtor
	char getState(); //getter for state
	void setState(char newstate); //setter for state
	void setCoords(const int newr, const int newc); //setter for the coordinate which are row and column
	int getC(); //getter for c
	int getR(); //getter for r
};

#endif
