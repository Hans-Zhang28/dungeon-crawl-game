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
		else if (12 == type && type == 13)
			gameBoard[location.first][location.second] = 'E';
		else if (14 == type && type == 15)
			gameBoard[location.first][location.second] = 'O';
		else
			gameBoard[location.first][location.second] = 'M';
		//if..else
	} //for 
