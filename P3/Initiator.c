// CS370
// Initiator.c
// Created by: Alex Laswell

#define _GNU_SOURCE
#define _XOPEN_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int intArray[10];
char* filename = "Nums.txt";

int parseFile(int argc, char** argv) {
	int count = 1;
	// Program expects a fileName
	if(argc<2) {
		fprintf (stderr, "Usage: ./Initiator Nums.txt \n");
		return -1;
	}

	// verify the filename is "Nums.txt"
	if(strcmp(argv[1], "Nums.txt") != 0) {	
		fprintf (stderr, "Usage: ./Initiator Nums.txt \n");
		return -1;
	}
	
	// open and verify that Nums.txt is a valid file as expected
	FILE* infile = fopen (argv[1], "r");
	
	fscanf (infile, "%d", &intArray[0]);
	while (!feof(infile)) {
		// check if count is over 10 
		//fprintf(stderr, "%d:count\n", count);
		if(count > 10) {
			fprintf (stderr, "Initiator Error Message : File contents are invalid\n");
			return -1;
		}
		// count < 10
		// get next int and increment count
		fscanf (infile, "%d", &intArray[count++]);
	}	
	
	// file expected to contain 10 integers
	// count will be 11 because of final loop
	if(count != 11) {
		fprintf (stderr, "Initiator Error Message : not enough integers in Nums.txt \n");
		return -1;
	}
	return 1;
}

int main(int argc, char** argv) {
	char pipearg[32];
	int shmid0 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0664);
	int* shm_addr;
	int pipeMean[2];

	int mean, status;
	
	if(!parseFile(argc, argv)) {
		fprintf (stderr, "Initiator Error Message : parse failed\n");
		return -1;
	}
	
	/* Evaluate the mean */

	if(pipe(pipeMean)) {
		fprintf (stderr, "Initiator Error Message : pipe failed\n");
		return -1;
	}

	// start by forking the process
	pid_t pidMean = fork();

	if(pidMean == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	
	else if(pidMean > 0) {	// parent process
		close(pipeMean[0]);	// close(read)
		// attach shm
		if((shm_addr = shmat(shmid0, 0, 0)) == -1) {
			fprintf (stderr, "Initiator Error Message : attached failed\n");
			return -1;
		}

		write(pipeMean[1], shm_addr, sizeof(int));

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pidMean);
		printf("Initiator: waiting for process [%d].\n", pidMean);
	}
	else {	// child process
		close(pipeMean[1]);	// close(write)

		// copy the read end to a char*
		sprintf(pipearg, "%d", pipeMean[0]);

		execlp("./Mean", "Mean", "Nums.txt", pipearg, (char*) 0);
	}
	if(mean == 255)
		printf("Initiator: child process %d returned -1\n", pidMean);
	else
		printf("Initiator: child process %d returned %d\n", pidMean, mean);
	/* end mean */
	wait(0);
	shmctl(shmid0, IPC_RMID, 0);
	
	return 0;
}
