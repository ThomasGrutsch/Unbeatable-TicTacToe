#include <stdio.h>
#include <stdlib.h> //for rand
#include<time.h> //for rand
/* There aren't boolean values so have to use this */
#define true 1 
#define false 0
#define MAX  3 //the maximun number of things read for the human turn 

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
/*This method checks if a winner is there, or a tie. 0 - nothing 1 - winner 2 - tie*/
int winner(char values[]);
/* Helps winner by actually finding if there is a winner */
int winnerHelper(char values[]);

int main()
{
	char values[9];
	srand(time(0)); //rand will return the same set of random numbers. srand(time(0)) solves this. Should only be called once.


	for (int i = 0; i < sizeof(values); i++) {
		values[i] = ' ';
	}

	printf("Welcome to tictactoe! Player has X, while the computer has 0. \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n \n");

	while (true == 1) {
		int hwinner = -1;
		int rwinner = -1;

		printBoard(values);

		humanTurn(values);
		if (turn > 2){
			hwinner = winner(values);
			if (hwinner == 1) {
				printf("You shouldn't have been able to do that! (Win that is!)\n");
				break;
			} else if (hwinner == 2) {
				printf("Tie! Time to get a better strat.\n");
				break;
			}
		}		

		//robot turn, robot does not go on the 5th iteration
		if (turn < 5)
			robotTurn(values);
		if (turn > 2){
			rwinner = winner(values);
			if (rwinner == 1) {
				printf("Computer won! Are you even trying?\n");
				break;
			} //the game never ends on a tie on the computers turn so we don't check it. 
		}


		//this well get deleted after testing and that jazz. 
		printBoard(values);

		
		turn++;
		
		//To print an integer 
		//printf("%d \n", turn);

		//this will also be deleted after testing and that jazz. 
		break;
	}


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

		printf("1st char was not an integer, try again: ");

	}

	values[spot[0] - 49] = 'X';


}

void robotTurn(char values[]) {

	if (turn == 0) {
		turn0(values);
	}

	//now we check if the human has a winning turn
	




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
	for (int i = 0; i < sizeof values; i++) {
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
	if (values[4] == cPos && values[7] == cPos) {
			return 1;
	}

	//vertical and horizontal of 2
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
	if (values[4] == cPos && values[5] == cPos) {
		return 1;
	}

	cPos = values[6];
	if (values[7] == cPos && values[8] == cPos) {
		return 1;
	}

	//no winner return 0
	return 0;

}






