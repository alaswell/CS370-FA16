// CS370
// Median.c
// Created by: Alex Laswell

#include <stdio.h>
#include <unistd.h>

const int DEBUG = 0;

int main(int argc, char** argv) {
	printf("Median process [%d]: Starting.\n", getpid());

	int intArray[10];
	int median, max, min;

	// Step 1: Read the numbers from the file
	FILE* infile = fopen ("Nums.txt", "r");
	
	for(int i = 0; i < 10; i++) {
		// put the numbers into the file
		fscanf (infile, "%d", &intArray[i]);
		if(DEBUG == 1) printf("int:%d\n", intArray[i]);
	}
	
	// Step 2: Find the maximum value among the numbers
	max = intArray[0];
	for(int i = 1; i < 10; i++) { 
		if(max < intArray[i])
			max = intArray[i];
		if(DEBUG == 1) printf("%d:max\n", max);
	}

	// Step 3: Find the minimum value among the numbers
	min = intArray[0];
	for(int i = 1; i < 10; i++) { 
		if(min > intArray[i])
			min = intArray[i];
		if(DEBUG == 1) printf("%d:min\n", min);
	}

	// Step 4:
	if(min == max) {
		median = max;
	}	
	else {
		median = ((max - min)/2 + min);
	}

	// print the median value to stdout
	printf("Median process [%d]: ", getpid()); 
	printf("Median is %d.\n", median);
	printf("Median process [%d]: Stopping.\n", getpid());
	
	// return codes
	if(median > 0) return 1;
	else if(median < 0) return -1;
	else return 0;	
}
