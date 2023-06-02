all: letters numbers firstname userinput newshell  

letters: letters.o
	cc -o letters letters.c

numbers: numbers.o
	cc -o numbers numbers.c
	
firstname: firstname.o
	cc -o firstname firstname.c

userinput: userinput.o
	cc -o userinput userinput.c

newshell: newshell.o
	cc -o newshell newshell.c

clean:
	rm *.o
