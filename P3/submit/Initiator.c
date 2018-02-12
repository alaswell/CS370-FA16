// CS370
// Initiator.c
// Created by: Alex Laswell

#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>

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
	char buf[1024];
	char pipearg[20];
	pid_t pid_Mean;		// Program ID
	pid_t pid_median;	// Program ID
	pid_t pid_mode;		// Program ID

	int mean, median, mode, status;
	int size = sizeof(double);

	if(parseFile(argc, argv) <= 0) {
		fprintf (stderr, "Initiator Error Message : parse failed\n");
		return -1;
	}

	// 2. create a pipe for each child process (3)
	int pipe0[2];
	if(pipe(pipe0) == -1 ) {
		perror("Creating pipe\n");
		exit(1);
	}
	
	// create the shared memory segments
	int shmid0 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0664);
	// attach to parent
	double* shm0addr = shmat(shmid0, 0, 0);
	if(*shm0addr == (-1))
		perror("shmat");

	
	// 3. Initiator should spawn 3 processes using fork()
	//    and print their process ID's as they are created
	
	/* mean */
	pid_Mean = fork();

	if(pid_Mean == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}
	else if (pid_Mean > 0) { // parent process
		close(pipe0[0]);			// close(read)
	
		// print to stdout
		printf("Initiator: forked process with ID %d.\n", pid_Mean);
		printf("Initiator: wrote shm ID %d to pipe (%d bytes)\n", shmid0, size);
		write(pipe0[1], &shmid0, size);
	}
	else {	// child process
		close(pipe0[1]);	// close(write)
		char* pipe0c = malloc(sizeof(char) * 32);

		sprintf(pipe0c, "%d", pipe0[0]);
		// exec mean
		execlp("./Mean", "Mean", "Nums.txt", pipe0c, (char*)NULL);
		free(pipe0c);
	}
	/* end mean */
	
	/* Evaluate the median */

	// start by forking the process
	pid_median = fork();

	if(pid_median == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pid_median == 0) {	// child process
		execlp("./Median", "Median", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pid_median);
		printf("Initiator: waiting for process [%d].\n", pid_median);

		wait(&status);
		median = WEXITSTATUS(status);
	}
	if(median == 255)
		printf("Initiator: child process %d returned -1\n", pid_median);
	else
		printf("Initiator: child process %d returned %d\n", pid_median, median);
	/*  end median */
	
	/* Evaluate the mode */

	// start by forking the process
	pid_mode = fork();

	if(pid_mode == -1) {
		fprintf (stderr, "Initiator Error Message : fork failed\n");
		return -1;
	}	

	if(pid_mode == 0) {	// child process
		execlp("./Mode", "Mode", "Nums.txt", NULL);

	}
	else {	// parent process

		// print pid to stdout
		printf("Initiator: forked process with ID %d.\n", pid_mode);
		printf("Initiator: waiting for process [%d].\n", pid_mode);

		wait(&status);
		mode = WEXITSTATUS(status);
	}
	if(mode == 255)
		printf("Initiator: child process %d returned -1\n", pid_mode);
	else
		printf("Initiator: child process %d returned %d\n", pid_mode, mode);
	/* end mode */

	shmdt(&shmid0);
//	shmdt(&shmid2);
//	shmdt(&shmid3);

//	shmctl(shmid1);
//	shmctl(shmid2);
//	shmctl(shmid3);
	return 0;
}
