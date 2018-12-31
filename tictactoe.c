#include <stdio.h>
#include <stdlib.h> //for rand
#include<time.h> //for rand
/* There aren't boolean values so have to use this */
#define true 1 
#define false 0
#define MAX  3 //the maximun number of things read for the human turn 
#define MAP 9 //the number for the size of the array(values)

int turn = 0; // gives the amount of turns that happened. 
 
/* One must declare a function before using it in C 
This function prints the board */
void printBoard(char values[]);
/*This allows the player to choose a spot*/
void humanTurn(char values[]);
/* This will start the algo for the robot to make a turn. */
void robotTurn(char values[]);
/* This happens when the first turn happens for the robot */
void turn0(char values[]);
/* A special case can arrize on turn 1 - we check for it with this method*/
int turn1(char values[]);
/*This method checks if a winner is there, or a tie. 0 - nothing 1 - winner 2 - tie*/
int winner(char values[]);
/* Helps winner by actually finding if there is a winner */
int winnerHelper(char values[]);
/* checks if the human or robot can win*/
int winChecker(char values[], int index, char player1, char player2);

int main()
{
	char values[MAP];
	srand(time(0)); //rand will return the same set of random numbers. srand(time(0)) solves this. Should only be called once.


	for (int i = 0; i < MAP; i++) {
		values[i] = ' ';
	}

	printf("Welcome to tictactoe! Player has X, while the computer has O. \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

	while (true == 1) {
		int hwinner = -1;
		int rwinner = -1;

		printBoard(values);

		humanTurn(values);
		
		hwinner = winner(values);
		if (hwinner == 1) {
			printf("*********************************************************\n");
			printf("You shouldn't have been able to do that! (Win that is!)\n");
			printf("*********************************************************\n");
			break;
		} else if (hwinner == 2) {
			printf("*********************************************************\n");
			printf("Tie! Time to get a better strat.\n");
			printf("*********************************************************\n");
			break;
		}
				

		//robot turn
		robotTurn(values);
		
		rwinner = winner(values);
		if (rwinner == 1) {
			printf("*********************************************************\n");
			printf("Computer won! Are you even trying?\n");
			printf("*********************************************************\n");
			break;
		} //the game never ends on a tie on the computers turn so we don't check it. 
		
		turn++;
		//To print an integer 
		//printf("%d \n", turn);

		 
	}

	printBoard(values);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("Thank you for playing!\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");


	return 0;
}

void printBoard(char values[]) {

	printf("%c|%c|%c\n", values[0], values[1], values[2]);
	printf("------\n");
	printf("%c|%c|%c\n", values[3], values[4], values[5]);
	printf("------\n");
	printf("%c|%c|%c\n", values[6], values[7], values[8]);

}

void humanTurn(char values[]) {
	char spot[MAX];
	for (int i = 0; i < MAX; i++)
		spot[i] = ' ';
	printf("Choose a location(1-9)(Only the first character is read): ");
	while (true == 1) {
		fgets(spot, MAX, stdin);
		//ASCII - number 1 starts at 49
		if (spot[0] == 49 || spot[0] == 50 ||
			spot[0] == 51 || spot[0] == 52 ||
			spot[0] == 53 || spot[0] == 54 ||
			spot[0] == 55 || spot[0] == 56 ||
			spot[0] == 57) {
			
			if (values[spot[0] - 49] == ' ') {
				break;
			} 

		}

		printf("Invalid entry, try again: ");

	}

	values[spot[0] - 49] = 'X';


}

void robotTurn(char values[]) {

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

/*0 - nothing 1 - winner 2 - tie */
int winner(char values[]) {
	//first check if there is a tie. 
	int tie = true;
	for (int i = 0; i < MAP; i++) {
		if (values[i] == ' ') {
			tie = false;
			break;
		}
	}

	if (tie == 1) {
		if (winnerHelper(values) == 1)
			return 1;
		else 
			return 2;
	}

	return winnerHelper(values);

}

/* Finds if there is a winner 0 - nothing 1 - winner
We are just gong to brute force it for now. */
int winnerHelper(char values[]) {

	//checking if there is a winner
	char cPos = values[0];
	if (cPos != ' ') {
		//checking the 0 vertical
		if (values[3] == cPos && values[6] == cPos) {
			return 1;
		}

		if (values[1] == cPos && values[2] == cPos) {
			return 1;
		}

		if (values[4] == cPos && values[8] == cPos) {
			return 1;
		}

	}
	//vertical 1
	cPos = values[1];
	if (cPos != ' ') {
		if (values[4] == cPos && values[7] == cPos) {
			return 1;
		}
	}

	//vertical and diagonal of 2
	cPos = values[2];
	if (cPos != ' ') {
		if (values[5] == cPos && values[8] == cPos) {
			return 1;
		}
		if (values[4] == cPos && values[6] == cPos) {
			return 1;
		}
	}

	cPos = values[3];
	if (cPos != ' ') {
		if (values[4] == cPos && values[5] == cPos) {
			return 1;
		}
	}

	cPos = values[6];
	if (cPos != ' ') {
		if (values[7] == cPos && values[8] == cPos) {
			return 1;
		}
	}
	//no winner return 0
	return 0;

}







