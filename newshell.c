/* Studet Name: Marcos Ondruska
 *	Student ID: 2685885
 * 
 *  I affirm that I wrote this program without any help from any other
 *  people or sources from the internet.
 *
 *  Program description: This program creates a shell for the user that allows for 8 different options. 
 *  The first option prints out letters from A-Z. The second option prints numbers 0 throuhg 9 on a newline.
 *  The third prints out a user entered name. The fourth takes user input and converts to upper case. 
 *  The fifth redirects letters to a user entered file name. The sixth pipes letters to upper case. The 
 *  seventh takes a user entered name and converts to uper case. Option eight exits.
 * 
 *  usage: newshell
 * 
	Marcos Ondruska


	Parts of this code are stolen from Dr. Raju Rangaswami's original 4338
	demo and modified to fit into our lecture, and modified once more to 
	fit my needs.. 
   
*/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_ARGS 2	// Max number of arguments 
#define BUFSIZ 8192	// worked without compile error on my machine

int get_args(char* cmdline, char* args[]) 
{
	int i = 0;

	/* if no args */
	if((args[0] = strtok(cmdline, "\n\t ")) == NULL) 
	return 0; 

	while((args[++i] = strtok(NULL, "\n\t ")) != NULL) {
    		if(i >= MAX_ARGS) {
      			printf("Too many arguments!\n");
      			exit(1);
    		}
  	}
	/* the last one is always NULL */
	return i;
}

void execute(char* cmdline) 
{
	int pid, async;
 	char* args[MAX_ARGS];

	int nargs = get_args(cmdline, args);
	if(nargs <= 0) return;

	if(!strcmp(args[0], "quit") || !strcmp(args[0], "exit")) {
	exit(0);
	}

	/* check if async call */
	if(!strcmp(args[nargs-1], "&")) { async = 1; args[--nargs] = 0; }
	else async = 0;

	pid = fork();
	if(pid == 0) { /* child process */
		execvp(args[0], args);
	/* return only when exec fails */
    		perror("exec failed");
    		exit(-1);
  	} 
	else if(pid > 0) { /* parent process */
    		if(!async) waitpid(pid, NULL, 0);
    		else printf("this is an async call\n");
  	} 
	else { /* error occurred */
    		perror("fork failed");
    		exit(1);
  	}
}

int makePipe(char *cmd1[], char *cmd2[]) {
	int pid, status;
	int fd[2];	// create input/output

	pipe(fd);
	// runsource (fd)
	switch (pid = fork()) {
		case 0:		// child
			dup2(fd[1], 1);		//this end of the pipe becomes the standard output
			close(fd[0]);		// this process does not need the other end
			execvp(cmd1[0], cmd1);		// run the command
			fprintf(stderr, "%s failed\n", cmd1[0]);		//command failed

		default:	// parent does nothing
			break;

		case -1:
			fprintf(stderr, "fork failed\n");
			exit(1);	
	}
	// rundest(fd)
	switch (pid = fork()) {
		case 0:		//child
			dup2(fd[0], 0);		// this end of the pipe becomes the standard input 
			close(fd[1]);		// the process does not need the other end 
			execvp(cmd2[0], cmd2);		// run the command
			fprintf(stderr, "%s failed\n", cmd2[0]);	//comand failed	

		default:	//parent does nothing	
			break;

		case -1:	//if there is an arror, print message below
			fprintf(stderr, "fork failed\n");
			exit(1);	
	}

	close(fd[0]);		//close both file descriptors on the pipe 
	close(fd[1]);

	return 0;
}	

int main (int argc, char* argv [])
{
	char cmdline[BUFSIZ];	// allocating size of buffer
	int menuInput = 0;	 	// initializing for switch
	int fileId;				// Declaring fileId	
	char temp[30];			// creating temp to store userinput
	char argument[130];		// creating argument to store string
	char filename[100];		// creating filename to store filename
	char userinput[100];	//	creating userinput to store user input
	char *cmd1[] = {"letters", (char *) 0};		// runs letters
	char *cmd2[] = {"userinput", (char *) 0};	// runs userinput
	char *cmd3[] = {"firstname", userinput, (char *) 0};	//runs firstname with userinput string

  	for(;;) {					// infinte loop
    		printf("\n1 letters\n"		// printing menu items
			"2 numbers\n"
			"3 firstname\n"
			"4 userinput\n"
		    	"5 letters > filename    (letters redirected to a file)\n"
		    	"6 letters | userinput   (letters piped to a file)\n"
		        "7 firstname | userinput (names piped to userinput)\n"
		        "8 exit\n");	 		// exit infinite loop

    		if(fgets(cmdline, BUFSIZ, stdin) == NULL) {		//if there is no data in cmdline print error message below
      			perror("fgets failed");
      			exit(1);
    		}
    		menuInput = atoi(cmdline);				//place cmdline into menuInput	
    		switch (menuInput) {					// switch begins
			case 1:						// case 1 runs letters
				strcpy(argument, "letters");
				break;
			case 2:						// case 2 runs numbers
				strcpy(argument,"numbers");
				break;
			case 3:						// case 3 accepts user entered name and runs firstname with this name
				fgets(temp, BUFSIZ, stdin);		// get user name and stores in temp
				strcpy(argument, ("%s", temp));		// add name stored in temp to argument
				fflush(stdin);				// flush buffer
				break;
			case 4:
				strcpy(argument, "userinput");		// runs userinput
				break;
			case 5:
				printf("Enter filename to redirect letters to: \n");	
				scanf("%s", filename);						//accepts user entered filename
				fileId = creat(filename, 0640);					// create fileId
				if (fileId < 0) {						// if fileId smaller than zero print error message
					printf("error creating %s\n", filename);
					exit(1);
				}
				dup2(fileId, fileno(stdout));					// redirect output to filename entered by user
				close(fileId);											

				execl("letters", (char *) 0);					// runs letters and redirects to user entered filename
				break;
			case 6: 
				makePipe(cmd1, cmd2);			// pipes letters and userinput
				break;	
			case 7:
				fgets(userinput, BUFSIZ, stdin);	// gets user name and stores in userinput
				makePipe(cmd3, cmd2);			// pipes user entered name and userinput
				fflush(stdin);				// flushes buffer
				break;
			case 8:
				strcpy(argument, "exit");		// exits switch
				break;	
			default:
				printf("Please enter a number from 1 to 8.\n");		// default statement
    		}
	
    		execute(argument) ;						// execute appropriate arguments in switch
  	}
	return 0;
}
