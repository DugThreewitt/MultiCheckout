/* ************************************************************************ *
 * multiC.c
 * go to the shortest line for checkout for checkout.c
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "queue.h"
#include "lanes.h"
#include "proto.h"

/* **********************************************************************
 * Function: findNextQueue()
 * inputs: Array of queues
 * outputs: array element with smallest queue size
 * purpose: find the shortest queue
 * *********************************************************************/

int findNextQueue( queue qArr [] , int arrSize )
{
	int i = 0;
	int testNum = 0; 

	for( i ; i < arrSize ; i++ )
	{
		if( qArr[i].qSize < qArr[testNum].qSize )
		{
			testNum = i;
		}
	}

	return testNum;
	
}


/* **********************************************************************
 * Function: checkSubs()
 * inputs: Array of queues
 * outputs: int 0 if all queues in arrar are empty
 * purpose: check if all sub arrays are empty
 * *********************************************************************/

int checkSubs( queue qArr [] , int arrSize )
{
	int i = 0;
	int empty = arrSize; 

	for( i ; i < arrSize ; i++ )
	{
		if( qArr[i].qSize != 0 )
		{
			break;
		}
		else
		{
			empty--;
		}
			
	}

	return empty;
	
}

/* **********************************************************************
 * Function: multiLineSim()
 * inputs: queue pointer, and lane quantity
 * outputs: 
 * purpose: simulates take a number style checkout lanes
 * *********************************************************************/

void multiLineSim( queue * custQ , int checkQty )
{
	queue lines[checkQty];
	laneT lanes[checkQty];
	int chosenQ;
	int loopCount = 0;
	int i = 0;
	int allWait = 0;
	int allIdle = 0;
	int allCust = 0;
	int diff = 0;
	int ready = 0;
	float avgIdle, avgWait, avgLIdle, avgLWait;
	customerT temp ;
	customerT innerTemp;
	//queue * discard;
	
	temp = take(custQ);

	//printf("multi Called\n");


	//temp = front(custQ); // first customer in line
	custQ->front->cust.start = 0;


	for( i ; i < checkQty ; i++) // intialize values as needed
	{
		lanes[i].totalCustomers =  0 ;
		lanes[i].lineLength =  0 ;
		lanes[i].currentIdle =   0 ;
		lanes[i].totalIdle =  0 ;
		lanes[i].currentWait =  0 ;
		lanes[i].totalWait =  0 ;
		lanes[i].totalCustomers =  0 ;
		lanes[i].nextAvailable = 0;
		lines[i] = create();	//initialize each queu in the array

	}

	while(/* checkSubs( lines, checkQty ) != 0 &&*/ ! isEmpty (custQ)/* loopCount < 1000*/ )
	{
		temp = take(custQ);

//		printf("Count: %d\n", loopCount);

		if(temp.arrival == loopCount) //customer arrives
		{
			chosenQ = findNextQueue( lines , checkQty ); // choosese queue
			//printf("Going to %d\n", chosenQ + 1);
			add(&lines[chosenQ], temp ); //taken from main queue and moved to queue array
			/*if(lines[chosenQ].qSize == 1)
			{
				lanes[chosenQ].currentCust = temp;
			//	take(&lines[chosenQ]);
				ready = lanes[chosenQ].currentCust.service;
				lanes[chosenQ].nextAvailable = ready;
				printf("ready: %d\tservice: %d\ttemp Start: %d\n", ready, lanes[chosenQ].currentCust.service, lanes[chosenQ].nextAvailable);
			}i*/
		/*	else
			{
				lanes[chosenQ].currentCust = temp;
				innerTemp = lines[chosenQ].front->next->cust;
				innerTemp.start = temp.start + temp.service;
				//lines[chosenQ].front->next->cust = innerTemp;
				//ready = innerTemp.start + innerTemp.service;
				printf("ready: %d\tservice: %d\ttemp Start: %d\n", ready, lanes[chosenQ].currentCust.service, lanes[chosenQ].nextAvailable);		//temp.start = ready;
			} */
		}
	
		for( i = 0 ; i < checkQty ; i++ )
		{
			if(loopCount == lanes[i].nextAvailable) //finds when checkout i is ready
			{	
				innerTemp = take(&lines[i]); // creates temp from front of queue array i to check out

				if ( innerTemp.arrival <= lanes[i].nextAvailable ) // if they arrive after the cashier is ready
				{
					lanes[i].currentWait = lanes[i].nextAvailable - innerTemp.arrival;
					lanes[i].nextAvailable += innerTemp.service; //set cashier next ready
					lanes[i].currentCust = innerTemp;//move customer to checkout
					printf("Lane: %-4d\tArrival: %d\tNext: %d\n", i+1, innerTemp.arrival, lanes[i].nextAvailable);
					continue; //continues to next iteration
				}
				else  // checks start time of innerTemp(set to 0 outsizde of loop
				{
					lanes[i].currentIdle = innerTemp.arrival - lanes[i].nextAvailable;
					lanes[i].nextAvailable = innerTemp.arrival + innerTemp.service; //set cashier next ready
					lanes[i].currentCust = innerTemp;//move customer to checkout
				 	printf("Lane: %-4d\tArrival: %d\tNext: %d\n", i+1, innerTemp.arrival, lanes[i].nextAvailable);
					continue; //continues to next iteration	
				}
			}
		}
		loopCount++;

//		printf("loop Count: %d\n", loopCount);
		
	}
/*	
	for( i = 0 ; i < checkQty ; i++ )
	{
		allWait += lanes[i].totalWait;
		allIdle += lanes[i].totalIdle;
		allCust += lanes[i].totalCustomers;
	}
	
	avgIdle = (float)allIdle / (float)allCust;
	avgWait = (float)allWait / (float)allCust;

	printf("\nSingle Line report:\n\n");
	printf("Total Customers Served: %-4d\t\tAverage Total Wait Time: %7.2f\tAverage Cashier Idle Time: %7.2f\n\n", allCust, avgWait, avgIdle);
	
	for( i = 0 ; i < checkQty ; i++ )
	{
		avgLIdle = (float)lanes[i].totalIdle / (float)lanes[i].totalCustomers;
		avgLWait = (float)lanes[i].totalWait / (float)lanes[i].totalCustomers;

		printf("Lane %-5d:\tTotal Customers: %-6d\tAverage Wait Time: %7.2f\tAverage Cashier Idle Time: %7.2f\n", (i+1), lanes[i].totalCustomers, avgLWait, avgLIdle);
	}
*/
	printf("\n");
}


