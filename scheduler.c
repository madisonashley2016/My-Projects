/**************
*Title: scheduler.c
*Assignment: Programming Assignment 4
*Description: Simulates a fun variety of CPU Scheduling Algorithms given a set of processes.
*Author: Ashley Madison
*Email: ammadison@coastal.edu
*Date: 12/03/2019
***************/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h>
#include "queue.h"

//Compute the average values for all of the algorithms.
void averages(struct Queue *fqueue, int count, int time_idle, int time){
	float avg_wt = 0; float avg_rt = 0; float avg_tat = 0; float avg_cpu = 0; //what is the repsonse time???
	struct Process current;
	
		while(!isEmpty(fqueue)){
			current = front(fqueue);
			avg_wt = (((float)current.wt / count) + avg_wt);
			avg_tat = (((float)current.tat / count) + avg_tat);
			avg_rt = (((float)current.rt / count) + avg_rt);
			
			dequeue(fqueue);
		}
		avg_cpu = (100 - (((float)time_idle / (float)time) * 100));
		printf("\n");
		printf("Average Wait Time:        %.2f\n", avg_wt);
		printf("Average Turn Around Time: %.2f\n", avg_tat);
		printf("Average Response Time:    %.2f\n", avg_rt);
		printf("Average CPU Usage:        %.0f%\n", avg_cpu);
}

//FCFS algorithm
void FCFS(struct Process p[]){
	printf("FCFS Simulation: \n");
	int time = 0; int count = 0; int processcount = 0; int processcount2 = 0; int time_idle = 0; int i = 0;
	int tick = 1; int booleanbro = 0; int tempst = 0;
	struct Queue *queue = createQueue(25);
	struct Queue *fqueue = createQueue(25);

	for(i = 0; i< 25; i++){ //Check how many processes are in the array.
		if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
			break;
		}
		p[i].temp = 0;
		processcount++; 
	}
	processcount2 = processcount;
	//----------------------------------------------------------------------------------------------------
	struct Process current; //temp
	
	while(1){ //Loops until no more processes to simulate.
		for(i = 0; i< 25; i++){ //Check when process will arrive.
			if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
				break;
			}
			if(p[i].arrival_t == time){
				
				if(isEmpty(queue)){
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;
				}
				else if(p[i].pid != front(queue).pid){
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;	
				}
				else{
					printf("else\n");
				}
			}
		}
		
		if(processcount == 0 && isEmpty(queue)){ //If no more processes and queue is empty, simulation is over.	
			break;
		}
		else if(isEmpty(queue)){ //If there are more processes then the CPU is in an idle state for now.
			printf("%d CPU idle\n", time);
			time_idle++;
		}
		else{
			current = front(queue);
			
			if(count != current.burst_t-1){
				if(booleanbro == 0){ //Gets the start time.
					tempst = time;
					booleanbro = 1;
				}
				printf("%d %d running\n", time, current.pid);
				count++;
			}
			else{
			
				current.st =  tempst; //Start time
				current.ct = time; //Calculate the complete time. 
				current.tat = current.ct - current.arrival_t; //Calculate the turn-around-time.
				current.wt = current.tat - (current.burst_t - 1); //Calculate the wait time.
				current.rt = current.st - current.arrival_t; //Response time
				
				enqueue(fqueue, current); //Switch process to the 'finished' queue
				printf("%d %d finished\n", time, dequeue(queue).pid);
				count = 0;
				booleanbro = 0;
				tempst = 0;
			}	
		}
		time = time + tick; //incrementing the clock
		}	
	//Tally results
	averages(fqueue, processcount2, time_idle, time);
}

//Round Robin!  Cannot get the response time fixed due to how I did the code. If I had time to redo this I could fix it but alassss. Same problem with FCFS but I fixed that because straightforward.
void RR(struct Process p[], int quantum){
	printf("RR Simulation: \n");
	int time = 0; int count = 0; int time_idle = 0; int i = 0; int processcount = 0; int processcount2 = 0;
	int tick = 1; 
	struct Queue *queue = createQueue(25);
	struct Queue *fqueue = createQueue(25);

	for(i = 0; i< 25; i++){ //Check how many processes are in the array.
		if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
			break;
		}
		processcount++; 
		p[i].temp = 0;
		p[i].temp2 = 0;
	}
	processcount2 = processcount;
	//----------------------------------------------------------------------------------------------------
	struct Process current; //temp

	while(1){ //Loops until no more processes to simulate.
		for(i = 0; i< 25; i++){ //Check when process will arrive.
			if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
				break;
			}
			if(p[i].arrival_t == time ){ 
				
				if(isEmpty(queue)){
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;
				}
				else if(p[i].pid != front(queue).pid){
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;	
				}
				else{
					printf("else\n");
				}
				
			}
		}
		
		if(processcount == 0 && isEmpty(queue)){ //If no more processes and queue is empty, simulation is over.	
			break;
		}
		else if(isEmpty(queue)){ //If there are more processes then the CPU is in an idle state for now.
			printf("%d CPU idle\n", time);
			time_idle++;
		}
		else{
			
			current = front(queue);
	
				if(count!=quantum){ //Counts up by the quantum.
					if(current.temp2 == 0){ //Gathering the start time
						changeFront(queue, 1, time);
					}
					
					printf("%d %d running\n", time, current.pid);
					count++;
					
					if(current.temp + count == current.burst_t){ //If the burst time of process is reached then dequeue.
						
						printf("%d %d finished\n", time, current.pid);
						current.ct = time; //Calculate the complete time. 
						current.tat = current.ct - current.arrival_t; //Calculate the turn-around-time.
						current.wt = current.tat - (current.burst_t - 1); //Calculate the wait time.
						current.rt = current.st - current.arrival_t; //Calculate the Response time.
						enqueue(fqueue, current);
						dequeue(queue);
						count = 0;
					
					}
				}
				else{ //If quantum reached but still more burst time, then put process on the end of the queue.
					current.temp = current.temp + count;
					count = 0;
					time--;
					enqueue(queue, current);
					dequeue(queue);
				}
			
		}
		time = time + tick; //incrementing the clock
		}
		
		//Tally results
		averages(fqueue, processcount2, time_idle, time);
}

//Shortest Remaining Time First
void SRTF(struct Process p[]){ 
printf("SRTF Simulation: \n");
	int time = 0; int time_idle = 0; int i = 0; int processcount = 0; int processcount2 = 0;
	int tick = 1; 
	struct Queue *queue = createQueue(25);
	struct Queue *fqueue = createQueue(25);
	struct Process compare[25];
	struct Process basic; basic.burst_t = 10000;

	for(i = 0; i< 25; i++){ //Check how many processes are in the array.
		if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
			break;
		}
		processcount++; 
		p[i].temp = p[i].burst_t;
		p[i].temp2 = 0;
	}
	processcount2 = processcount; //so I have my process count which counts down. My processcount2 stays the same. And reverse process counts up.
	int reverseprocesscount = 0;
	//----------------------------------------------------------------------------------------------------

	while(1){ //Loops until no more processes to simulate.
		
		for(i = 0; i< 25; i++){ //Check when process will arrive.
			if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
				break;
			}
			if(p[i].arrival_t == time ){ 
				
				if(isEmpty(queue)){
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;
					reverseprocesscount++;
				}
				else if(p[i].pid != front(queue).pid){//Prevent duplicate problems
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;	
					reverseprocesscount++;
				}
				else{
					printf("else\n");
				}
				
			}
		}
		
		if(processcount == 0 && isEmpty(queue)){ //If no more processes and queue is empty, simulation is over.	
			break;
		}
		else if(isEmpty(queue)){ //If there are more processes then the CPU is in an idle state for now.
			printf("%d CPU idle\n", time);
			time_idle++;
		}
		else{
		i = 0;
		int tempcount = 0;
		struct Process min = basic;
			//Dequeue the entire queue to prepare for comparisons.
			while(i < reverseprocesscount){ 
				compare[i] = dequeue(queue);
				i++;
			}
			//Compare the burst times of every process. Process with smallest bt will run for 1 unit of time for each compare.
			for(i = 0; i < reverseprocesscount; i++){
		
				if(compare[i].pid == 0){
					break;
				}
				else if(compare[i].burst_t < min.burst_t){ //compare burst times
					min = compare[i];
					tempcount = i;
				}
				
			
			}
			printf("%d %d running\n", time, min.pid);
			if(min.temp2 == 0){ //Getting the start time
				min.st = time;
				min.temp2 = 1;
				}
			min.burst_t = min.burst_t - 1; //Your time is running out ~0.0~
			
			
			if(min.burst_t == 0){ //Process finished, calculate times and make array smaller.
				printf("%d %d finished\n", time, min.pid);
				
				min.burst_t = min.temp; 
				min.ct = time;
				min.tat = min.ct - min.arrival_t;
				min.wt = min.tat - (min.burst_t - 1);
				min.rt = min.st - min.arrival_t;
				
					for(i = tempcount; i<reverseprocesscount-1; i++){
						compare[i] = compare[i+1];
					}
					
				reverseprocesscount--;
				enqueue(fqueue, min);//Queue onto the 'finished' array
				
			}
			else{
			compare[tempcount] = min; //Process is not finished, update temp values from min into the main array
			}
			
			//Place edited process back onto the queue.
			for(i = 0; i < reverseprocesscount; i++){
				if(compare[i].pid == 0 && compare[i].arrival_t == 0 && compare[i].burst_t == 0){
					break;
				}
				enqueue(queue, compare[i]);
				rear(queue).pid;
				}
			
		}
		time = time + tick; //incrementing the clock
		}
		averages(fqueue, processcount2, time_idle, time);
}

//Preemptive Priority With Aging
void PPA(struct Process p[], int increaser){
	int time = 0; int count = 0; int time_idle = 0; int i = 0; int processcount = 0; int processcount2 = 0;
	int tick = 1; int j = 0; 
	struct Queue *queue = createQueue(25);
	struct Queue *fqueue = createQueue(25);
	struct Process compare[25];
	struct Process current;
	struct Process temp;

	for(i = 0; i< 25; i++){ //Check how many processes are in the array.
		if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
			break;
		}
		processcount++; 
		p[i].temp = p[i].burst_t;
		p[i].priority = 0;
		p[i].timer = 0;
		p[i].temp2 = 0;
	}
	processcount2 = processcount; //LOL ok so I have my process count which counts down. My processcount2 stays the same. And reverse process counts up.
	int reverseprocesscount = 0;
	//----------------------------------------------------------------------------------------------------

	while(1){ //Loops until no more processes to simulate.
		
		for(i = 0; i< 25; i++){ //Check when process will arrive.
			if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
				break;
			}
			if(p[i].arrival_t == time ){ 
				
				if(isEmpty(queue)){
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;
					reverseprocesscount++;
				}
				else if(p[i].pid != front(queue).pid){//Prevent duplicate problems
					printf("%d %d arriving\n", time, enqueue(queue, p[i]).pid);
					processcount--;	
					reverseprocesscount++;
				}
				else{
					printf("else\n");
				}
				
			}
		}
		
		if(processcount == 0 && isEmpty(queue)){ //If no more processes and queue is empty, simulation is over.	
			break;
		}
		else if(isEmpty(queue)){ //If there are more processes then the CPU is in an idle state for now.
			printf("%d CPU idle\n", time);
			time_idle++;
		}
		else{ 
		i = 0;
		current = dequeue(queue);
		while(i < reverseprocesscount-1){ //Aquire everyone other than the current process
				compare[i] = dequeue(queue);
				
				compare[i].timer = compare[i].timer + 1;
				if(compare[i].timer == 5){ //Increase priority every 5 seconds based on arrival time
					compare[i].priority = compare[i].priority + increaser;
					compare[i].timer = 0;
				
				}
				
				i++;
				
			}
		for(i = 0; i < reverseprocesscount-1; i++){ //Sort everyone in decreasing order
			for(j = 0; j < reverseprocesscount-1; j++){
				if(compare[j].priority < compare[i].priority){
					temp = compare[i];
					compare[i] = compare[j];
					compare[j] = temp;
				}
			}
		}
		
		printf("%d %d running\n", time, current.pid);
		if(current.temp2 == 0){ //Aquire the start time
			current.st = time;
			current.temp2 = 1;
		}
		current.burst_t = current.burst_t - 1;
		
		if(current.burst_t == 0){ //If the current process is finito
			printf("%d %d finished\n", time, current.pid);
					
				current.burst_t = current.temp;
				current.ct = time;
				current.tat = current.ct - current.arrival_t;
				current.wt = current.tat - (current.burst_t - 1);
				current.rt = current.st - current.arrival_t;
				
				enqueue(fqueue, current);//Queue onto the 'finished' array
				
				for(i = 0; i < reverseprocesscount-1; i++){
				if(compare[i].pid == 0 && compare[i].arrival_t == 0 && compare[i].burst_t == 0){
					break;
				}
				enqueue(queue, compare[i]);
				rear(queue).pid;
				}
				reverseprocesscount--;
		}
		else{
			//Compare current priority to largest in array. Decides what order they get requeued into. 
			if(current.priority < compare[count].priority){ //If current priority is smaller 
	
				for(i = 0; i < reverseprocesscount-1; i++){
					if(compare[i].pid == 0 && compare[i].arrival_t == 0 && compare[i].burst_t == 0){
						break;
					}
					enqueue(queue, compare[i]);
					rear(queue).pid;
					}
					enqueue(queue, current); //Queue current process into the back
			}
			else{ //If current priority is larger
				enqueue(queue, current); //Queue current process into the front
				for(i = 0; i < reverseprocesscount-1; i++){
					if(compare[i].pid == 0 && compare[i].arrival_t == 0 && compare[i].burst_t == 0){
						break;
					}
					enqueue(queue, compare[i]);
					rear(queue).pid; 
				}
			}
		}
		
			
		}
		time = time + tick; //incrementing the clock
		}
		averages(fqueue, processcount2, time_idle, time);
		
}

int main(int argc, char *argv[]){ //main input style: ./scheduler [FCFS|RR|SRTF|PPA] [Optional Quantum/Increaser for RR/PPA]
	int i = 0;
	struct Process p[25];
	int quantIncrease; //was RRquantum
	char *alg; char *quantum; char *a[10];
	
	if(argv[1] == 0){
		printf("Please choose an algorithm. FCFS/RR [quantum]/SRTF/PPA [increaser]\n");
		exit(0);
	}
	for(i = 0; i<10; i++){ //Retrieve command line input
		if(i < argc){
			a[i] = argv[i];
		}
		else{
			a[i] = "wat";
		}
	}
	alg = a[1];
	quantum = a[2];
	quantIncrease = atoi(quantum);
	
	//Insert all of the processes we want from stdin
	printf("Please input the processes that you wish to simulate. Or not. I can't tell you what to do.\n");
	printf("Input them in this format: PID Arrival_Time Burst_Time\n");
	printf("To finish inserting, type 0 0 0\n");
	printf("Example: 1 0 5\n	 2 0 10\n	 0 0 0\n------------------------------------------\n");
	for(i = 0; i < 25; i++){
		scanf("%d %d %d", &p[i].pid, &p[i].arrival_t, &p[i].burst_t);//Read the input
		if(p[i].pid == 0 && p[i].arrival_t == 0 && p[i].burst_t == 0){
			break; //if 0 0 0 then end of input
		}
	}
	if(strcmp(alg, "FCFS") == 0){
		FCFS(p);
	}
	else if(strcmp(alg, "RR") == 0){ 
		if(quantIncrease == 0){
			printf("You need a quantum bro. And no you cant use 0 that defeats the purpose.");
		}
		else{
			RR(p, quantIncrease);
		}
	}
	else if(strcmp(alg, "SRTF") == 0){
		SRTF(p);
	}
	else if(strcmp(alg, "PPA") == 0){
		if(quantIncrease == 0){
			printf("You need an increaser bro. And no you cant increase by 0 that defeats the purpose.");
		}
		else{
			PPA(p, quantIncrease);
		}
	}
	else{
		printf("what the HECK do you think you are doing????");
	}
	
	
	return 0;
}
