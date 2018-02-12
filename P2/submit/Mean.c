// CS370
// Mean.c
// Created by: Alex Laswell

#include <stdio.h>
#include <unistd.h>

const int DEBUG = 0;

int main(int argc, char** argv) {
	printf("Mean process [%d]: Starting.\n", getpid());

	int intArray[10];
	int count = 10;
	double mean, zero = 0;

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
