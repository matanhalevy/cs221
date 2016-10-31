#include <cstdlib>
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main() {
	int random_num;
	int guess_num;
	srand(0);
	random_num = rand() % 10 + 1;
	char buffer[256];
	do {printf ("Guess a number from 1 to 100, or Press 'q' to Quit: ");
	fgets(buffer, 256, stdin);
	if (buffer[0]  == 'q'){
		printf("You have quit the game.");
		return 0;}
	guess_num = atoi(buffer);
	if (random_num == guess_num){ printf("Congratulations, your guess was correct!");
	}
	else{printf ("Try again. ");}
	} while (random_num != guess_num);
	return 0;
	
}