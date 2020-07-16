/**************
*Title: war.c
*Description: Simulates a game of war using parallel processes.
*Enter the number of rounds you want when you initialize the program like this
*ex. ./war 5 
*Author: Ashley Madison
*Email: ammadison@coastal.edu
*Date: 10/10/2019
***************/

/**
 * ----Sources----
 * https://www.geeksforgeeks.org/generating-random-number-range-c/ (Where I got my random numbers)
 * https://www.youtube.com/watch?v=7bNMkvcOKlc (Where I got help setting up the pipes)
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <time.h>
#include <signal.h>

int main(int argc, char *argv[]){
	pid_t child1, child2;
	char *cardNames[14] = {"0","2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
	char *cardSuites[5] = {"0","Clubs", "Diamonds", "Hearts", "Spades"};

	int fd1[2]; //Stores the first pipe
	int fd2[2]; //stores the second pipe
	int fd3[2]; //stores the third pipe
	int fd4[2]; //stores the fourth pipe
	
	int ret, ter, doo, dee;
	ret = pipe(fd1); 
	ter = pipe(fd2);
	doo = pipe(fd3);
	dee = pipe(fd4);
	
	if(argc < 2){
		printf("Error --Correct input format: ./war [number of rounds]\n");
		exit(1);
	}
	if(ret || ter || doo || dee == -1){ //error checking
		perror("pipe");
		exit(1);
		}	
	
	
	srand(time(NULL));
	int random1 = 0;
	int random2 = 0;
	int suit1 = 0;
	int suit2 = 0;
	int i = 0; 
	char *c = argv[1];
	int numberOfRounds = atoi(c);
	int signal = 0;
	int wincount1 = 0;
	int wincount2 = 0;
	int tiecounter = 0;
	
	
	child1 = fork();
	
	if(child1 == 0)//child1 code process
	{
		time_t t;
		srand((int) time(&t) % getpid());
		//int d;
		
		while(1){	
			
			//child reads from the parent using pipe 2
			close(fd2[1]);
			read(fd2[0], &signal, sizeof(signal));
		
			if(signal == 0){ //draw
				random1 = (rand() % (13)) + 1;
				//child writes to the parent using pipe 1
				close(fd1[0]);
				write(fd1[1], &random1, sizeof(random1)); //sends parent a random card
				}
			else if(signal == 1){ //suit, will send parent a random card btwn 1 and 4
				suit1 = (rand() % (4)) + 1;
				
				close(fd1[0]);
				write(fd1[1], &suit1, sizeof(suit1)); //sends parent a random card
				}
			else{ //anything but 0 or 1 is exit honestly
				exit(0);
				}

			}	
			close(fd2[0]);	
			close(fd1[1]);
			close(fd1[1]);
		
		}
	else
	{
		child2 = fork();
		
		if(child2 == 0){//child2 code process
		
			time_t t;
			srand((int) time(&t) % getpid());
			
			while(1){
			
				//child reads from the parent using pipe 4
				close(fd4[1]);
				read(fd4[0], &signal, sizeof(signal));
			
				if(signal == 0){ //draw a random card between 1 and 13 
					random2 = (rand() % (13)) + 1;
					
					//child writes to the parent using pipe 3
					close(fd3[0]);
					write(fd3[1], &random2, sizeof(random2)); 
			
				}
				else if(signal == 1){ //suit, will send parent a random card btwn 1 and 4
					suit2 = (rand() % (4)) + 1;
				
					close(fd3[0]);
					write(fd3[1], &suit2, sizeof(suit2));
				
				}
				else{ //anything but 0 or 1 is exit honestly but I am using 2
					exit(0);
				}
		
			}
			close(fd4[0]);
			close(fd3[1]);
			close(fd3[1]);
		
		}
		else{//parent code process
		
			printf("Beginning the game of WARRRR!!!\n\n");
			printf("Fight!\n");
			printf("___________________________\n");
			
			for(i = 0; i<numberOfRounds; i++)
				{ 
				signal = 0;
				//parent sends signal to both children to draw.
				close(fd2[0]);
				write(fd2[1], &signal , sizeof(signal));
			
				close(fd4[0]);
				write(fd4[1], &signal,  sizeof(signal));
				
				//parent reads what the children draw
				close(fd1[1]);
				read(fd1[0], &random1, sizeof(random1));
				printf("Child 1 draws: %s\n", cardNames[random1]);
				
				close(fd3[1]);
				read(fd3[0], &random2, sizeof(random2));
				printf("Child 2 draws: %s\n", cardNames[random2]);
	
				if(random1 > random2){
					wincount1++;
					printf("Child 1 wins!\n");
					printf("___________________________\n");
					signal = 0;
				}
				else if(random2 > random1){
					wincount2++;
					printf("Child 2 wins!\n");
					printf("___________________________\n");
					signal = 0;
				}
				else{ //if there is a tie
					printf("Tye likely! Must check suit!\n");
					printf("___________________________\n");
					signal = 1;
					
					//parent sends signal to both children to draw.
					close(fd2[0]);
					write(fd2[1], &signal , sizeof(signal));
			
					close(fd4[0]);
					write(fd4[1], &signal,  sizeof(signal));
				
					//parent reads what the children draw
					close(fd1[1]);
					read(fd1[0], &suit1, sizeof(suit1));
					printf("Child 1 suit: %s!\n", cardSuites[suit1]);
				
					close(fd3[1]);
					read(fd3[0], &suit2, sizeof(suit2));
					printf("Child 2 suit: %s!\n", cardSuites[suit2]);
					
					if(suit1 > suit2){
						wincount1++;
						printf("Child 1 wins the suit!\n");
						printf("___________________________\n");
						signal = 0;
					}
					else if(suit2 > suit1){
						wincount2++;
						printf("Child 2 wins the suit!\n");
						printf("___________________________\n");
						signal = 0;
					}
					else{
						printf("Suit and Tie! Nobody wins this round!\n");
						printf("___________________________\n");
						signal = 0;
					}
					
					
					
				}
			
			} //this is the bracket to the for loop
			
			signal = 2; //signals everything to end
			close(fd2[0]);
			write(fd2[1], &signal , sizeof(signal));
			
			close(fd4[0]);
			write(fd4[1], &signal,  sizeof(signal));
			
			close(fd2[1]);
			close(fd4[1]);
			close(fd1[0]);
			close(fd3[0]);
			
			wait(NULL);	
		
		}//parent else bracket
	}//big else bracket
	
	printf("Results: \n");
	printf("Child 1 Wins: %d\n", wincount1);
	printf("Child 2 Wins: %d\n", wincount2);
	
		if(wincount1 > wincount2){
			printf("Child 1 wins! End of game.\n");
		}
		else if(wincount2 > wincount1){
			printf("Child 2 wins! End of game.\n");
		}
		else{
			printf("Nobody wins! End of game.\n");
		}

return 0;
}
