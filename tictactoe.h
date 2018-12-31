/*This .h file is used to linking things in C. It is good practice to use .h files, NOT .c */
#include <stdio.h>
#include <stdlib.h> //for rand
#include<time.h>

#define MAP 9

int turn = 0;

void robotTurn(char values[], int turn);
/* This happens when the first turn happens for the robot */
void turn0(char values[]);
/* A special case can arrize on turn 1 - we check for it with this method*/
int turn1(char values[]);
/* checks if the human or robot can win*/
int winChecker(char values[], int index, char player1, char player2);

/*This one has an extra parameter for turn*/
void robotTurn(char values[], int turn) {

	if (turn == 0) {
		turn0(values);
		return;
	}

	//On turn 1 there is one strat that can beat the algo if the board has a config of
	// | |X   if the robot does not play either to 0 or 1, it loses.
	//X|O|	  This can happen on turn 1. 
	// | |
	if (turn == 1) {
		if (turn1(values) == 1)
			return;
	}

	//we now check if the robot can win
	for (int i = 0; i < MAP; i++) {
		if (values[i] == 'O') {
			if (winChecker(values, i, 'O', 'X') == 1) {
				return;
			}
		}
	}

	//check if human can win. 
	for (int i = 0; i < MAP; i++) {
		if (values[i] == 'X') {
			if (winChecker(values, i, 'X', 'O') == 1) {
				return;
			}
		}
	}

	//if we can not find any moves that meet these criteria, play random for now. 
	for (int i = 0; i < MAP; i++) {
		if (values[i] == ' ') {
			values[i] = 'O';
			break;
		}
	}	

}

/*checks if either human or robot can win ret - 0 if no 1 - if yes and plays */
int winChecker(char values[], int index, char player1, char player2) {
	//checking the horizontal lines
	for (int i = 0; i <= 6; i += 3) {
		int pos = 0; //finds the open spot
		int count = 0;
		if (values[i] == player1)
			count++;
		else if (values[i] == player2)
			continue;
		else 
			pos = i;

		if (values[i + 1] == player1)
			count++;
		else if (values[i + 1] == player2)
			continue;
		else 
			pos = i + 1;

		if (values[i + 2] == player1)
			count++;
		else if (values[i + 2] == player2)
			continue;
		else 
			pos = i + 2;

		if (count == 2) {
			values[pos] = 'O';
			return 1;
		}

	}

	//checking the vertical lines
	for (int i = 0; i <= 2; i++) {
		int pos = 0; //finds the open spot
		int count = 0;
		if (values[i] == player1)
			count++;
		else if (values[i] == player2)
			continue;
		else 
			pos = i;

		if (values[i + 3] == player1)
			count++;
		else if (values[i + 3] == player2)
			continue;
		else 
			pos = i + 3;

		if (values[i + 6] == player1)
			count++;
		else if (values[i + 6] == player2)
			continue;
		else 
			pos = i + 6;

		if (count == 2) {
			values[pos] = 'O';
			return 1;
		}

	}

	int pos = 0;
	int count = 0;
	//checking the diagonal lines
	for (int i = 0; i <= 8; i += 4) {
		if (values[i] == player1)
			count++;
		else if (values[i] == player2) {
			count -= 50;
			break;
		} else {
			pos = i;
		}
	}

	if (count == 2) {
		values[pos] = 'O';
		return 1;
	}

	//reset variables
	pos = 0;
	count = 0;

	for (int i = 2; i <= 6; i += 2) {
		if (values[i] == player1)
			count++;
		else if (values[i] == player2) {
			count -= 50;
			break;
		} else {
			pos = i;
		}
	}

	if (count == 2) {
		values[pos] = 'O';
		return 1;
	}
	

	return 0;
}


/* 0 - nothing was played (special case never reached) 1 - case reached and a play made.*/
int turn1(char values[]) {
	int num = rand() % 2;
	//first check if X has a corner spot
	if (values[0] == 'X') { //then check the to other cases
		if (values[5] == 'X') {
			if (num == 0) {
				values[1] = 'O';
				return 1;
			} else {
				values[2] = 'O';
				return 1;
			}
		}
		if (values[7] == 'X') {
			if (num == 0) {
				values[3] = 'O';
				return 1;
			} else {
				values[6] = 'O';
				return 1;
			}
		}
	}

	if (values[2] == 'X') { //then check the to other cases
		if (values[3] == 'X') {
			if (num == 0) {
				values[0] = 'O';
				return 1;
			} else {
				values[1] = 'O';
				return 1;
			}
		}
		if (values[7] == 'X') {
			if (num == 0) {
				values[5] = 'O';
				return 1;
			} else {
				values[8] = 'O';
				return 1;
			}
		}
	}

	if (values[6] == 'X') { //then check the to other cases
		if (values[1] == 'X') {
			if (num == 0) {
				values[0] = 'O';
				return 1;
			} else {
				values[3] = 'O';
				return 1;
			}
		}
		if (values[5] == 'X') {
			if (num == 0) {
				values[7] = 'O';
				return 1;
			} else {
				values[8] = 'O';
				return 1;
			}
		}
	}

	if (values[8] == 'X') { //then check the to other cases
		if (values[1] == 'X') {
			if (num == 0) {
				values[2] = 'O';
				return 1;
			} else {
				values[5] = 'O';
				return 1;
			}
		}
		if (values[3] == 'X') {
			if (num == 0) {
				values[6] = 'O';
				return 1;
			} else {
				values[7] = 'O';
				return 1;
			}
		}
	}


	return 0;
}

/* We will try and get the O in the middle, if not we go for one of the corners */
void turn0(char values[]) {
	int num;
	//We always start by playing something in the middle of the board. 
	if (values[4] != 'X') {
		values[4] = 'O';
	} else { //choosing a random corner. 

		//srand was called here. 

		num = rand() % 4; 

		if (num == 0)
			values[num] = 'O';
		else if (num == 1) 
			values[2] = 'O';
		else if (num == 2) 
			values[6] = 'O';
		else 
			values[8] = 'O';
	}
				

	
}