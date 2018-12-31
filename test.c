#include <stdio.h>
#include "tictactoe.h" //this is the syntax for linking files, this is the file I will call for testing. 
/*This tests a bug where the game does not play for the win given a specific set up*/
int test1();

/*Currently I do not think this is the best way to setup test files, but this is what we figured out through little research*/



int main() {

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	int passes = 0;
	int fails = 0;

	if (test1() != 1) {
		printf("Test1 failed!\n");
		fails++;
	} else {
		passes++;
	}


	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Number of tests that failed: %d\n", fails);
	printf("Number of tests that passed: %d\n", passes);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	return 0;
}

/*1 - pass, anything else - fail. This tests for a specific case where the robot can win, but plays the wrong move. */
int test1() {
	char values[9];
	for (int i = 0; i < sizeof values; i++) {
		values[i] = ' ';
	}

	//human player plays this config in this order.
	values[0] = 'X';
	values[1] = 'X';
	values[5] = 'X';
	//robot response for the first two
	values[4] = 'O';
	values[2] = 'O';

	/*for testing purposes I have an extra parameter for turn*/
	robotTurn(values, 3);

	if (values[6] == 'O') {
		return 1;
	} else {
		printf("Test 1 Actual: %c. Expected: O \n", values[6]);
		return 0;
	}

}