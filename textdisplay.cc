#include "textdisplay.h"
#include <iostream>

using namespace std;

//default ctor
//purpose: generates a gameboard for game.
TextDisplay::TextDisplay(int r, int c) : View(r, c){
	theDisplay = new char*[r];
	for (int i = 0; i < r; ++i) {
		theDisplay[i] = new char[c]; 
		for (int j = 0; j < c; ++j)
		  theDisplay[i][j] = ' ';
		//for
	} //for
}


//dtor
TextDisplay::~TextDisplay() {
	for (int i = 0; i < r; ++i) 
		delete[] theDisplay[i];
	//for
	delete[] theDisplay;
}


//purpose: called by Controller to update the (r,c) location into ch
//return: void
void TextDisplay::notify(int r, int c, char ch) {	theDisplay[r][c] = ch; } //notify(int,int,char)

//purpose: print the grid as specified in the assignment specification
//return: void
void TextDisplay::print(ostream& out) {
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			out << theDisplay[i][j];
		} //for
		out << endl;
	} //for
} //print(ostream&)
