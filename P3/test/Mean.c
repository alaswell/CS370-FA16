// CS370
// Mean.c
// Created by: Alex Laswell

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>	

const int DEBUG = 0;

int main(int argc, char** argv) {
	printf("Mean process [%d]: Starting.\n", getpid());

	int intArray[10];
	int count = 10;
	double mean, zero = 0;

	char* location = malloc(sizeof(char)*32);
	int pfdModeCh = atoi(argv[2]);

	read(pfdModeCh, location, sizeof(location));
	close(pfdModeCh);

	int shmidMode = atoi(location);

	printf("Mead process [%d]: read (%lu bytes) containing shm ID %d\n", getpid(), sizeof(char)*32, shmidMode);

	// open and verify that Nums.txt is a valid file as expected
	FILE* infile = fopen (argv[1], "r");
	
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

	// return codes
	if(mean < zero) return -1;
	else if(mean == zero) return 0;
	else return 1;
}
