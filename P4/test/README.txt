Program Assignment 4 README 
Written by: Alex Laswell

files:
	Scheduler.java	- expects a (String) filename and (int) quantum | loops until 'Q', 'QUIT', or 'EXIT

	this README

The program(s) sucessfully complete the following tasks:

1. Read the list of processes for your scheduling algorithms from a file. Every line in this  file  
	includes  a  record  with  comma  separated  fields.  The  format  for  this  record is  the 
	following: <ProcessID>,<Arrival Time>, <Burst Duration>. 
	
	All processes in yourinput files will be provided a unique process ID. 
	
	There is no limit to the number  of the entries. The arrival times and burst durations are integers. 

2. Your program (scheduler.java) should support these options: FCFS, SJF preemptive, Round Robin scheduling,
	and exit.

3. Implement FCFS and report sequence of execution (begin time and end time for each process CPU burst), 
	average turnaround time, average waiting time, and throughput.

4. Implement  SJF  (preemptive) and  report sequence  of  execution, average turnaround  time, average 
	waiting time, and throughput.

5. Implement Round Robin and report sequence of execution, average turnaround time, average waiting time, 
	and throughput


/* Error messages */

# Invalid Argument	 					-> 	Program arguments invalid, program 
									MUST be passed the filename and 
									size of quantum specifically

# Read Error 					 		-> 	filename is invalid

/* end ERROR */
