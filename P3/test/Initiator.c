// CS370
// Initiator.c
// Created by: Alex Laswell

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int intArray[10];
char* filename = "Nums.txt";

int parseFile(int argc, char** argv) {
	int count = 1;

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
	return 1;
}

int main(int argc, char** argv) {
	// create the pipe
	int pfdMean[2];
	pipe(pfdMean);

	pid_t pidMean;		// Program ID
	pid_t pidMedian;	// Program ID
	pid_t pidMode;		// Program ID

	int mean, median, mode, status;

	if(parseFile(argc, argv) <= 0) {
		fprintf (stderr, "Initiator Error Message : parseFile()\n");
		return -1;
	}

	// create the shared memory segments
	int shmid_mean = shmget(IPC_PRIVATE, sizeof(double), 0664);
	// attach to parent
	char* shm1addr = shmat(shmid_mean, (void*) 0, 0);
	if(shm1addr == (char*) (-1))
		perror("shmat");
	/* Evaluate the mean */

	// start by forking the process
	pidMean = fork();

	if(pidMean == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	
	else if(pidMean == 0) {	// child process
		close(pfdMean[1]);	// close write end
/*		char* pfdMeanCh = malloc(sizeof(char)*32);

		
		sprintf(pfdMeanCh, "%d", pfdMeanCh[0]);
*/
		execlp("./Mean", "Mean", "Nums.txt", shm1addr, (char*)NULL);
//		free(pfdMeanCh);
	}
	else {	// parent process
		close(pfdMean[0]);
		write(pfdMean[1], shm1addr, 32);
		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pidMean);

	//	wait(&status);
	//	mean = WEXITSTATUS(status);
	}
	if(mean == 255)
		printf("Initiator: child process %d returned -1\n", pidMean);
	else
		printf("Initiator: child process %d returned %d\n", pidMean, mean);
	/* end mean */
	

	/* Evaluate the median */

	// start by forking the process
	pidMedian = fork();

	if(pidMedian == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pidMedian == 0) {	// child process
		execlp("./Median", "Median", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pidMedian);
		printf("Initiator: waiting for process [%d].\n", pidMedian);

		wait(&status);
		median = WEXITSTATUS(status);
	}
	if(median == 255)
		printf("Initiator: child process %d returned -1\n", pidMedian);
	else
		printf("Initiator: child process %d returned %d\n", pidMedian, median);
	/* end median */
	
	/* Evaluate the mode */

	// start by forking the process
	pidMode = fork();

	if(pidMode == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pidMode == 0) {	// child process
		execlp("./Mode", "Mode", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pidMode);
		printf("Initiator: waiting for process [%d].\n", pidMode);

		wait(&status);
		mode = WEXITSTATUS(status);
	}
	if(mode == 255)
		printf("Initiator: child process %d returned -1\n", pidMode);
	else
		printf("Initiator: child process %d returned %d\n", pidMode, mode);
	/* end mode */
	return 0;
}
