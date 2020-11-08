#include <stdlib.h>

#include "scheduling.h"

/*
##  Round-Robin Scheduling Algorithm  ##

	Parameters:-

	queue: 1D int array containing the CPU burst time for every process in a ready queue
	np: number of processes (length of `queue` array)
	tq: time quantum for the RR algorithm


	Returns:-

	rr_result struct pointer, where
	rr_result -> order: 1D int array, containing the execution order of processes (i.e. `(rr_result -> order)[0]` is the process number of the first process)
		** hint: p1 is always the first item in order of selection in round-robin and FCFS
    rr_result -> order_n: int, representing the size of the `order` array, described above ^
	rr_result -> turnarounds: 1D int array, containing the turnaround time for each process (i.e. `(rr_result -> turnarounds)[0]` is the turnaround time for p1)
*/




rr_result *rr(int *queue, int np, int tq)
{
	rr_result *result = malloc(sizeof(rr_result));
	result->np = np;
	result->turnarounds = malloc(sizeof(int) * np);

	// Set order_n to np
	result->order_n = np;

	// Create a copy of the queue to store the REMAINING time needed to complete a process, and store the order in the result object
	int remainTime[np];
	result->order = malloc(sizeof(int) * np);
	for(int count = 0; count < np - 1; count ++){
		remainTime[count] = queue[count];
		(result->order)[count] = count + 1;
	}

	int count, time, remain, tat, wt, marker;
	count = 0;
	time = 0;
	remain = np;
	tat = 0;
	wt = 0;
	marker = 0;
	while(remain != 0){
		if(remainTime[count] <= tq && remainTime[count] > 0){
			remainTime[count] = 0;
			marker = 1;
			time += remainTime[count];
		}else if(remainTime[count] > 0){
			remainTime[count] -= tq;
			time += tq;
		}
		if (remainTime[count] == 0 && marker == 1){
			remain--;
			(result->turnarounds)[count] = (time - (result->order)[count] - 1) - (time - (result->order)[count] -1 - queue[count]);
			wt += time - (result->order)[count] - 1 - queue[count];
			tat += time += time - (result->order)[count] - 1;
			marker = 0;
		}
		if(count == (np-1)){
			count = 0;
		}else if(((result->order)[count+1]-1)<=time){
			count++;
		}else{
			count=0;
		}
	}

	return result;
}
