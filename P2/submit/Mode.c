// CS370
// Mode.c
// Created by: Alex Laswell

#include <stdio.h>
#include <unistd.h>

const int DEBUG = 0;

int main(int argc, char** argv) {
	printf("Mode process [%d]: Starting.\n", getpid());

	int intArray[10];
	int count, mode, maxCount = 0;

	// open and verify that Nums.txt is a valid file as expected
	FILE* infile = fopen ("Nums.txt", "r");
	
	for(int i = 0; i < 10; i++) {
		// put the numbers into the file
		fscanf (infile, "%d", &intArray[i]);
		if(DEBUG == 1) printf("int:%d\n", intArray[i]);
	}
	
	// Find the mode
	for(int i = 0; i < 9; i++) { 
		count = 0;
		for(int j = i + 1; j < 10; j++) {
			if(intArray[i] == intArray[j])
				count++;
		}
		if (count > maxCount) {
			maxCount = count; 
			mode = intArray[i];
		}
	}
	// if the maxCount is still zero then 
	// there are 10 distinct integers 
	// so set mode to the first number it encountered
	if(maxCount == 0)
		mode = intArray[0];

	// print the mean value to stdout
	printf("Mode process [%d]: ", getpid()); 
	printf("Mode is %d.\n", mode);
	printf("Mode process [%d]: Stopping.\n", getpid());

	// return codes
	if(mode > 0) return 1;
	else if(mode == 0) return 0;
	else return -1;	
}
