// CS370
// Initiator.c
// Created by: Alex Laswell

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

int intArray[10];
char* filename = "Nums.txt";

int main(int argc, char** argv) {
	pid_t pid;	// Program ID
	int count = 1, mean, median, mode, status;

	// Program expects a fileName
	if(argc<2) {
		fprintf (stderr, "Usage: ./Initiator Nums.txt \n");
		return 0;
	}

	// verify the filename is "Nums.txt"
	if(strcmp(argv[1], "Nums.txt") != 0) {	
		fprintf (stderr, "Usage: ./Initiator Nums.txt \n");
		return 0;
	}
	
	// open and verify that Nums.txt is a valid file as expected
	FILE* infile = fopen (argv[1], "r");
	
	fscanf (infile, "%d", &intArray[0]);
	while (!feof(infile)) {
		// check if count is over 10 
		//fprintf(stderr, "%d:count\n", count);
		if(count > 10) {
			fprintf (stderr, "Initiator Error Message : File contents are invalid\n");
			return 0;
		}
		// count < 10
		// get next int and increment count
		fscanf (infile, "%d", &intArray[count++]);
	}	
	
	// file expected to contain 10 integers
	// count will be 11 because of final loop
	if(count != 11) {
		fprintf (stderr, "Initiator Error Message : not enough integers in Nums.txt \n");
		return 0;
	}
	
	/* Evaluate the mean */

	// start by forking the process
	pid = fork();

	if(pid == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pid == 0) {	// child process
		execlp("./Mean", "Mean", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pid);
		printf("Initiator: waiting for process [%d].\n", pid);

		wait(&status);
		mean = WEXITSTATUS(status);
	}
	if(mean == 255)
		printf("Initiator: child process %d returned -1\n", pid);
	else
		printf("Initiator: child process %d returned %d\n", pid, mean);
	/* end mean */
	

	/* Evaluate the median */

	// start by forking the process
	pid = fork();

	if(pid == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pid == 0) {	// child process
		execlp("./Median", "Median", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pid);
		printf("Initiator: waiting for process [%d].\n", pid);

		wait(&status);
		median = WEXITSTATUS(status);
	}
	if(median == 255)
		printf("Initiator: child process %d returned -1\n", pid);
	else
		printf("Initiator: child process %d returned %d\n", pid, median);
	/* end median */
	
	/* Evaluate the mode */

	// start by forking the process
	pid = fork();

	if(pid == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pid == 0) {	// child process
		execlp("./Mode", "Mode", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pid);
		printf("Initiator: waiting for process [%d].\n", pid);

		wait(&status);
		mode = WEXITSTATUS(status);
	}
	if(mode == 255)
		printf("Initiator: child process %d returned -1\n", pid);
	else
		printf("Initiator: child process %d returned %d\n", pid, mode);
	/* end mode */
	return 0;
}
