/*	Studet Name: Marcos Ondruska
 *	Student ID: 2685885
 * 
 *  I affirm that I wrote this program without any help from any other
 *  people or sources from the internet.
 *
 *  Program description: This program takes a command line input for the users name and prints that out.
 * 
	usage: firstname yourfirstname

	Marcos Ondruska
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int debug = 0;

int main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int err = 0; 
	static char usage[] = "usage: %s yourfirstname\n";

	if (optind < argc)	/* these are the arguments after the command-line options */
		for (; optind < argc; optind++)	//work through the command line options
			printf("%s\n", argv[optind]); // print command line option

	exit(0);
}
