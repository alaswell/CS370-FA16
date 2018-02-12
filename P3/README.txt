Program Assignment 2 README 
Written by: Alex Laswell

files:
	Mean.c 		- expects a filename | evaluates the mean of the ten (10) integers
	Median.c 	- expects a filename | evaluates the median of the ten (10) integers
	Mode.c 		- exepcts a filename | evaluates the mode of the ten (10) integers
	Initiator.c	- expects "Nums.txt" | fork(), exec(), and wait() for each of the preceding programs 
	makefile	- standard method for compiling the program(s)
	this README

The program(s) sucessfully complete the following tasks:

1. The Initiator takes the text file Nums.txt as input and sends it to the child processes. Each of the other three programs accepts the file as an argument.

2. The Initiator spawns 3 processes using the fork() command and ensures that it completes one full cycle of fork(), exec(), and wait() for a given process before it moves on to spawning a new process.

3. Once it has used the fork() command, the Initiator prints out the process ID of the process that it created.

4. Child-specific processing immediately following the fork() command then loads the Mean/Median/Mode program into the newly created process using the exec() command. This ensures that the forked process is no longer a copy of the Mean/Median/Mode. This exec() command also passes 1 argument to the Mean/Median/Mode program. 

5. When the Mean/Median/Mode is executing it prints out its process ID; this will match the one returned by the fork()command in step 3.

6. The Mean/Median/Mode then determines whether the result is positive, negative or zero.

7. Mean/Median/Mode returns an exit code +1 for positive result, -1 for negative result and 0 if the result is zero. These correspond to the standard UNIX exit codes. Each exit code received by the Initiator is printed.

8. Parent-specific processing in the Initiator ensures that the Initiator will wait() for each instance of the child-specific processing to complete.

/* Error message prints to stderr */

# Usage: ./Initiator Nums.txt 					-> 	Program arguments invalid, program MUST be passed the filename "Nums.txt" specifically
# Initiator Error Message : File contents are invalid 		-> 	file "Nums.txt" MUST contain exactly ten (10) intger values. Verify "Nums.txt"
# Initiator Error Message : not enough integers in Nums.txt 	-> 	file "Nums.txt MUST contain exactly ten (10 integer values. Verify "Nums.txt"
# Initiator Error Message : fork failed 			-> 	fork() error pid returned '-1'

/* end ERROR */
