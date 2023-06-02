/* Studet Name: Marcos Ondruska
 *	Student ID: 2685885
 *
 *  I affirm that I wrote this program without any help from any other
 *  people or sources from the internet.
 *
 *  Program description: This program prints out letters A through Z on the same line.
 *
	usage: letters

	Marcos Ondruska
*/

#include <stdio.h>

int main(void)
{ // cycle through ascii characters lower case from a-z
	for (int i = 97; i < 123; i++)
	{
		printf("%c", i); // print characters without newline
	}

	return 0;
}
