// CS370
// Mean.c
// Created by: Alex Laswell

#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>

const int DEBUG = 0;

int main(int argc, char** argv) {
	printf("Mean process [%d]: Starting.\n", getpid());

	char* FD = malloc(sizeof(char)*32);
	double* shmaddr;
	int pipefd;

	/*if (pipe(&pipefd) == -1 ) {
		perror("Mean Error Creating Pipe");
		return -1;
	}*/
	
	open(argv[1], O_RDONLY);
	pipefd = atoi(argv[1]);
	read(pipefd, FD, sizeof(FD));
	close(pipefd);
	printf("FD: %d\n", *FD);

	int shmid = atoi(FD);

	if(!(shmaddr = shmat(shmid, NULL, 0))) {
		perror("Mean Error shmat");
		return -1;
	}
		
		
	printf("Mean process [%d]: read (%lu bytes) containing shm ID %f\n", getpid(), sizeof(char)*32, *shmaddr);
	printf("7\n");
	int intArray[10];
	int count = 10;
	double mean, zero = 0;

	// open and verify that Nums.txt is a valid file as expected
	FILE* infile = fopen (argv[0], "r");
	
	// Step 1: Read the interger values from the file
	// Step 2: Count can be assumed to be 10
	for(int i = 0; i < 10; i++) {	
		fscanf (infile, "%d", &intArray[i]);
	}
	
	// Step 3: Add the numbers
	for(int i = 0; i < 10; i++) { 
		mean += intArray[i];	
	}

	// Step 4: Divide the sum by the count
	mean = mean/count;
	
	// Step 5: Print the mean value to stdout
	printf("Mean process [%d]: ", getpid()); 
	printf("Mean is %f.\n", mean);
	printf("Mean process [%d]: Stopping.\n", getpid());

	*shmaddr = mean;
	shmdt(shmaddr);
	return 1;
}
