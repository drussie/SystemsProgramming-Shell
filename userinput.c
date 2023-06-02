/*	Studet Name: Marcos Ondruska
 *	Student ID: 2685885
 * 
 *  I affirm that I wrote this program without any help from any other
 *  people or sources from the internet.
 *
 *  Program description: This program takes a command line alphabetic input and converts it to upper case.
 * 
	usage: userinput

	Marcos Ondruska
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	char string[100]; 	//declare string with space for 100 characters
	int i;			// declare variable to be used in for loop
	
	fgets(string, 64, stdin); 		//get user input

	string[strcspn( string, "\n")] = 0; 	// Number of chars to \n

	for (i = 0; i < strlen(string); i++) {	
	string[i] = toupper(string[i]);		//char at i to upper case letter
		if(!isalpha(string[i])) {	//if char at i is not a letter, print error message
			printf("Please	enter only one string with alphabetic input\n");
			exit(100);
		}
	}

	printf("%s\n", string); 		//print string in uppercase

	return 0;
}
