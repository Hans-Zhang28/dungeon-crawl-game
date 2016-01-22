#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include <utility>
#include <string>
#include <fstream>

/*
Abstract class to allow Game to send
notifications to registered object
	 */
class Cell;
class Player;

const int numRows = 25;
const int numCols = 79;

class GameNotification {
	public:
	virtual void notify(int r, int c, char state) = 0;
	virtual void notifyAction(std::string action) = 0;
};

class Game {
	int sizeChamber1; //the size of the vector Chamber1
	int sizeChamber2; //the size of the vector Chamber2
	int sizeChamber3; //the size of the vector Chamber3
	int sizeChamber4; //the size of the vector Chamber4
	int sizeChamber5; //the size of the vector Chamber5
	bool pass; //is true when the player get to another floor, otherwise is falss
	char prevState; //record the previous state of the player stayed
	Cell*** theGrid; //the acutual grid	
	std::vector<std::pair<int,int> > Chamber1; //the vector of location to each Cell in the Chamber 1
	std::vector<std::pair<int,int> > Chamber2; //the vector of location to each Cell in the Chamber 2	
	std::vector<std::pair<int,int> > Chamber3; //the vector of location to each Cell in the Chamber 3	
	std::vector<std::pair<int,int> > Chamber4; //the vector of location to each Cell in the Chamber 4
	std::vector<std::pair<int,int> > Chamber5; //the vector of location to each Cell in the Chamber 5
	Player* player; //the Cell for player character
	GameNotification* notification; //object registered for notifications
	bool neutral; //if the merchant has been attacked neutral, set it to true, otherwise false
	bool useRH; //if the player use RH before, set it to true, otherwise false
	bool useBA; //if the player use BD before, set it to true, otherwise false
	bool useBD; //if the player use RH before, set it to true, otherwise false
	bool usePH; //if the player use PH before, set it to true, otherwise false
	bool useWA; //if the player use WA before, set it to true, otherwise false
	bool useWD; //if the player use WD before, set it to true, otherwise false
	int move_count; //used to count the enemy's movement
	int tmpChamber; //to record the chamber number generate in the pop_loc()
	Cell* findNeighbour(Cell* cell, std::string dir); //find the neighbour of Cell in the given direction dir
	std::string convertDir(std::string dir); //convert a 2 character string to a full string of direction.
	void checkNeighbour(Player * player); //first check if there are potion or gold within 1 block radius of 
	                                      //player then check if there are enemies around, if yes, enemies 
	                                      //attack player
  std::string int_str(int n); // convert int to string
	std::pair<int,int> pop_loc(int player_room = 6); //generate a random location from five Chambers	
	std::pair<int,int> neighbour_loc(std::pair<int,int> loc); //generate one of the neighbour of the locaiton we give
	char gameBoard[numRows][numCols];	
	
	
	public:
	Game(GameNotification* gameNotification); //default ctor
	~Game(); //dtor
	//void notify(int r, int c, char newState); //receive update notification
	                                                         //from Cells
  //void notityAction(string act1, string act2); //receive update of Action from Cells
	bool isDead(); //if the player is dead return true, otherwise false
	void change(std::string com1, std::string com2 = ""); //used to call the notify in the  player 
	void init(std::string race,  GameNotification* gameNotification, std::ifstream& fileToRead, bool haveArg); //called by Controller: init in response to initialization
	                      //requests when game is in init mode
	void setPass(); //setter for pass
	bool getPass(); //getter for pass
	void setPrevState(char state); //setter for prevState
	char getPrevState(); //getter for prevState
	void clearGame(); //Frees the gameboard except the player pointer
	void setUseRH(); //setter for useRH, will set it to true.
	void setUseBA(); //setter for useBA, will set it to true.
	void setUseBD(); //setter for useBD, will set it to true.
	void setUsePH(); //setter for usePH, will set it to true.
	void setUseWA(); //setter for useWA, will set it to true.
	void setUseWD(); //setter for useWD, will set it to true.
	bool getUseRH(); //getter for useRH
	bool getUseBA(); //getter for useBA
	bool getUseBD(); //getter for useBD
	bool getUsePH(); //getter for usePH
	bool getUseWA(); //getter for useWA
	bool getUseWD(); //getter for usesWD
	Player* getPlayer(); //getter for player
};
#endif
