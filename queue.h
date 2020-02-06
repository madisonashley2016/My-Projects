#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/**************
*Title: queue.h
*Assignment: Programming Assignment 4 - Queue
*Description: Queue
*Author: Ashley Madison (Modified Queue from GeeksforGeeks.org)
*Email: ammadison@coastal.edu
*Date: 12/03/2019
***************/

// C program for array implementation of queue 
//Using a modified Queue found at geeksforgeeks.org, without their permission,
//Slightly modified version of their queue to fit my needs.

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

struct Process//my process structure
{
	int pid;          //Process ID
	int arrival_t;	  //time it arrives
	int burst_t;       //time requested by the cpu (Burst time)
	int ct;		  //complete time time that it completes
	int tat;	  //turn around time 
	int wt;		  //wait time time spent waiting
	int temp;
	int priority;
	int timer;
	int rt;		 //response time
	int st;		 //start time
	int temp2;
	
};
  
// A structure to represent a queue 
struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    //int* array; 
    struct Process *array;
}; 
  
// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->array = (struct Process*) malloc(queue->capacity * sizeof(struct Process));  //replaced int
    return queue; 
} 
  
// Queue is full when size becomes equal to the capacity  
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 
  
// Queue is empty when size is 0 
int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 
  
// Function to add an item to the queue.   
// It changes rear and size 
struct Process enqueue(struct Queue* queue, struct Process item)  //replaced int item
{ 
    if (isFull(queue)) {
        printf("Queue is full!\n");
	}else{
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
    //printf("%d enqueued to queue\n", item.pid); 
    return item;
    }
} 
  
// Function to remove an item from queue.  
// It changes front and size
struct Process dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) {
        printf("Queue is empty!\n"); 
	}else{
    struct Process item = queue->array[queue->front]; //replaced int item
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
    }
} 
  
// Function to get front of queue 
struct Process front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) {
        printf("Queue is empty!\n"); 
	}else{
    return queue->array[queue->front]; 
    }
} 

//Function to change temp2 and st value at front of queue specifically for RR function
void changeFront(struct Queue* queue, int boolean, int st){
     if (isEmpty(queue)) {
        printf("Queue is empty!\n"); 
	}else{
        queue->array[queue->front].temp2 = boolean;
        queue->array[queue->front].st = st;
    }
}
  
// Function to get rear of queue 
struct Process rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) {
        printf("Queue is empty!\n"); 
	}else{
    return queue->array[queue->rear]; 
    }
} 
  

#endif