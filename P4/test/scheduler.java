// Programming Assignment 4
// Author: Alex Laswell
// Date: Oct 21, 2016
// Class: CS370
// Email: alaswell@cs.colostate.edu	

import java.io.File;
import java.util.*;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.RoundingMode;


public class scheduler {

static final boolean DEBUG = false;
//static final boolean DEBUG = true;

	public List<int[]> readProcesses(String filename) {
		// An array list to hold each process
		List<int[]> processes = new ArrayList<>();
		
		try {
			Scanner scanner = new Scanner(new File(filename));

			// Need to use strings to parse the file b/c of ','
			String tempLine;
			String[] eachLine;

			while (scanner.hasNext()) {
				// create a new temp int []
				int [] tempProcess = new int[5];
	
				// get the next line and parse on ','
				tempLine = scanner.nextLine();
				eachLine = tempLine.split(",");
					if(DEBUG) System.out.println("get the next 3 values:");
				// <ProcessID>
				// <Arrival Time>
				// <Burst Duration>
				tempProcess[0] = Integer.parseInt(eachLine[0]);
				tempProcess[1] = Integer.parseInt(eachLine[1]);
				tempProcess[2] = Integer.parseInt(eachLine[2]);
				
				// add to List
				processes.add(tempProcess);
			}
		} 
		catch (IOException e) {
			e.printStackTrace();
			System.exit(0);
		}
	return processes;
	}

	public void printHeading(String type) {
		System.out.println("\n=========================================\n");
		System.out.println(type + " SCHEDULING ALGORITHM:\n");
		System.out.println("=========================================\n");
		System.out.println("PID\tStBurst\tEburst\n");
	}

	public static double round(double val, int digit) {
		if(digit < 0) return -1;

		BigDecimal newVal = new BigDecimal(val);
		newVal = newVal.setScale(digit, RoundingMode.HALF_UP);
		return newVal.doubleValue();
	}

	public String getSelection() {
		Scanner in = new Scanner(System.in);

		System.out.print("Which scheduling algorithm would you like to use? (FCFS, PRESJF, RR): ");
		return in.next();
	}
	
	public List<int[]> sortProcesses(int category, List<int[]> processes) {
		List<int[]> newProcesses = new ArrayList<>();
		int size = processes.size();

		do {
			int minLoc = 0;
			int minVal = processes.get(0)[category];	// init to first process arival

			for(int i = 0; i < processes.size(); i++) {
				// for each process in the List
				if(minVal > processes.get(i)[category]) {		
					// if the minVal is higher it is not the MIN
					// so re-adjust
					minVal = processes.get(i)[category];
					minLoc = i;
				}
			}
			// add to the newProcess List
			newProcesses.add(processes.get(minLoc));
			processes.remove(minLoc);
		} while( newProcesses.size() < size);
		return newProcesses;
	}

	public void FCFS(List<int[]> processes) {
		double timeElapsed = 0.0, idleTime = 0.0, avgTurnAround = 0.0, avgWaitTime = 0.0;
		double[] turnAround = new double[processes.size()];
		double[] waitTime = new double[processes.size()];

		printHeading("FCFS");
		processes = sortProcesses(1, processes);
	
		for(int i = 0; i < processes.size(); i++) {
			// make sure we are not idle
			if(timeElapsed < processes.get(i)[1]) {
					if(DEBUG) System.out.println("Elapsed less: " + timeElapsed);
				// add to idle and "wait" that long
				idleTime += (processes.get(i)[1] - timeElapsed);
				timeElapsed += (processes.get(i)[1] - timeElapsed);
			}
			else if(timeElapsed > processes.get(i)[1])
				// process has been waiting
				waitTime[i] = (timeElapsed - processes.get(i)[1]);
	
			// go through and run each process
			System.out.print(processes.get(i)[0] + "\t"
					 + processes.get(i)[1] + "\t"
					 + (timeElapsed + processes.get(i)[2]) 
					 + "\n");
			// Execute the process
			timeElapsed += processes.get(i)[2];

			// Turnaround time = completion - arrive
			turnAround[i] = (timeElapsed - processes.get(i)[1]);
				if(DEBUG) System.out.println("Elapsed: " + timeElapsed);
		}
		
		// compute and output Average Wait
		for(int i = 0; i < processes.size(); i++) avgWaitTime += waitTime[i];
		System.out.println("Average waiting time: " + round(avgWaitTime/processes.size(), 2) + "\n");

		
		// compute and output Avgerage Turnaround
		for(int i = 0; i < processes.size(); i++) avgTurnAround += turnAround[i];
		System.out.println("Average turnaround time: " + round(avgTurnAround/processes.size(), 2) + "\n");
		
		// compute and output throughput
		System.out.println("Throughput: " + round(processes.size()/timeElapsed, 2));
	
		// footer
		System.out.println("=========================================\n");
	}
	
	public void getReady(List<int[]> processes, List<int[]> readyQueue, double timeElapsed) {
		for(int i = 0; i < processes.size(); i++) {
			// for each process (b/c there could be two arriving at same time)
			if(timeElapsed >= processes.get(i)[1]) {
				// process.get()[1] = arival time
				// if curTime > arival (arived)
				// add to ready queue 
				readyQueue.add(processes.get(i));
				
				// and remove from List
				processes.remove(i);
			}
		}
	}

	public void SJF(List<int[]> processes, String filename) {
		double timeElapsed = 0.0, idleTime = 0.0, avgTurnAround = 0.0, avgWaitTime = 0.0;
		List<int[]> readyQueue = new ArrayList<>();
		List<int[]> origCopy = new ArrayList<>();
		origCopy = readProcesses(filename);

		boolean changed = false;
		double[] turnAround = new double[processes.size()];
		double[] waitTime = new double[processes.size()];
		int turnCount = 0;

		printHeading("PRESJF");
		processes = sortProcesses(1, processes);	// sort by arivalTime
		getReady(processes, readyQueue, timeElapsed);	
		
		while( (processes.size() > 0) ) {
			// while there are processes left to process
			// process the shortest job 
			int minVal = -1, location = 0;

			// check the readyQueue first
			while(readyQueue.size() > 0) {
				minVal = readyQueue.get(0)[2];
				for(int i = 0; i < readyQueue.size(); i++) {
					// find the shortest remaining job
					if(minVal > readyQueue.get(i)[2]) {
						minVal = (readyQueue.get(i)[2]);
						location = i;
						changed = true;
					}
				}
				if(changed) {
					readyQueue.get(location)[3] = (int) timeElapsed;
					int tempPro = readyQueue.get(location)[0];
					for(int i = 0; i < origCopy.size(); i++) {
						if(origCopy.get(i)[0] == tempPro)
							origCopy.get(i)[3] = (int) timeElapsed;
					}
						changed = false;
				}
				timeElapsed++;	// one tick processed...
				readyQueue.get(location)[2]--;
				if( readyQueue.get(location)[2] < 1 ) {
					// if after processing the last tick 
					// this process is finished
					// print, remove, and save turnaround time!
					System.out.println(readyQueue.get(location)[0] + "\t"
							+ readyQueue.get(location)[3] + "\t"
							+ (int) timeElapsed);
					turnAround[turnCount++] = (timeElapsed - readyQueue.get(location)[1]);
					readyQueue.remove(location);
					changed = true;
				}
				// now get the new ready processes
				getReady(processes, readyQueue, timeElapsed);	
				minVal = -1;	// reset
				location = 0;
			}
			if( processes.size() > 0 ) { 
				// no ready process so "wait" until next ready 
				if(readyQueue.size() > 0) 
					idleTime += (readyQueue.get(0)[1] - timeElapsed);
				else
					idleTime += (processes.get(0)[1] - timeElapsed);

				timeElapsed += (processes.get(0)[1] - timeElapsed);
				getReady(processes, readyQueue, timeElapsed);
			}
		}
		
		// compute and output Average Wait
		for(int i = 0; i < origCopy.size(); i++) {
			avgWaitTime += ( origCopy.get(i)[3] - origCopy.get(i)[1] );
		}
		System.out.println("Average waiting time: " + round(avgWaitTime/origCopy.size(), 2) + "\n");
		
		// compute and output Avgerage Turnaround
		for(int i = 0; i < origCopy.size(); i++) avgTurnAround += turnAround[i];
		System.out.println("Average turnaround time: " + round(avgTurnAround/origCopy.size(), 2) + "\n");
		
		// compute and output throughput
		System.out.println("Throughput: " + round(origCopy.size()/timeElapsed, 2));
	
		// footer
		System.out.println("=========================================\n");
	}

	public void RR(List<int[]> processes, int quantum, String filename) {
		List<int[]> readyQueue = new ArrayList<>();
		List<int[]> origCopy = new ArrayList<>();
		origCopy = readProcesses(filename);
		
		int sum = 0;
		int size = processes.size();

		double timeElapsed = 0.0, avgWaitTime = 0.0, avgTurnAround = 0.0;
	
		double[] turnAround = new double[size];
		double[] waitTime = new double[size];
		double[] tempBurst = new double[size];
		for(int i = 0; i < size; i++) tempBurst[i] = processes.get(i)[2];	// copy burstTimes
		
		printHeading("ROUND ROBIN");
		processes = sortProcesses(1, processes);	// sort by arivalTime
		getReady(processes, readyQueue, timeElapsed);	
		
		do {
			for(int i = 0; i < readyQueue.size(); i++) {
				// for each process we have in the queue
				if(readyQueue.get(i)[2] > quantum) {
					// if there is still time left process stuff
					System.out.println(readyQueue.get(i)[0] + "\t"
						+ timeElapsed + "\t"
						+ (timeElapsed + quantum) );
			
					timeElapsed += quantum;
					readyQueue.get(i)[2] -= quantum;
					
					if(readyQueue.size() > 1) {
						for(int j = 0; j < readyQueue.size(); j++) {
							// now for all but myself
							if( (j != i) && (readyQueue.get(j)[2] != 0) )
								// if we are still going
								// add to wait b/c they are waiting
								waitTime[j] += quantum; 	
						}
					}
				}
				else {
					// time remaining is less than quantum so just finish
					for(int j = 0; j < readyQueue.size(); j++) {
						// for everyone but me add that much to waitTime
						if( (j != i) && (readyQueue.get(j)[2] != 0) )
							waitTime[j] += readyQueue.get(i)[2];
					}
				System.out.println(readyQueue.get(i)[0] + "\t"
					+ timeElapsed + "\t"
					+ (timeElapsed + readyQueue.get(i)[2]) );
				timeElapsed += readyQueue.get(i)[2];
				readyQueue.remove(i);
				}
			getReady(processes, readyQueue, timeElapsed);
			}
			sum = 0;
//			getReady(processes, readyQueue, timeElapsed);
			for(int j = 0; j < readyQueue.size(); j++) sum += readyQueue.get(j)[2]; // are we done yet?
			if( (sum == 0) && (processes.size() > 0)) {
				// we are idle
				timeElapsed += (processes.get(0)[1] - timeElapsed);
				getReady(processes, readyQueue, timeElapsed);
				sum = 1;
			}
		} while(sum != 0);
		
		System.out.println();
	
		// compute and output Average Wait
		for(int i = 0; i < size; i++) avgWaitTime += waitTime[i];
		System.out.println("Average waiting time: " + round(avgWaitTime/size, 2) + "\n");
		
		// compute and output Avgerage Turnaround
		// turnaround = totalWait + burst
		for(int i = 0; i < size; i++) turnAround[i] = (waitTime[i] + origCopy.get(i)[2]);
		for(int i = 0; i < size; i++) avgTurnAround += turnAround[i];
		System.out.println("Average turnaround time: " + round(avgTurnAround/size, 2) + "\n");
		
		// compute and output throughput
		System.out.println("Throughput: " + round(size/timeElapsed, 2));
	
		// footer
		System.out.println("=========================================\n");	
	}

	public static void main(String[] args) throws IOException {
		scheduler s1 = new scheduler();

		String filename = args[0];
		List<int[]> processes = s1.readProcesses(filename);	
		boolean loop = true;

		while(loop) {
			// get the algorithm selection from the user
			String selection = s1.getSelection();
	
			switch(selection.toUpperCase()) {
				case "FCFS":
					s1.FCFS(processes);
					break;

				case "PRESJF":
					s1.SJF(processes, filename);
					break;

				case "RR":
					s1.RR(processes, Integer.parseInt(args[1]), filename);
					break;

				case "Q":
				case "QUIT":
				case "EXIT":
					loop = false;
					break;

				default:
					throw new IllegalArgumentException("Invalid selection: " + selection);
			}
		processes = s1.readProcesses(filename);
		}
	}
}
