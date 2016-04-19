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
		lanes[i].nextAvailable = 0 ;
		lanes[i].currentWait = 0;
		lanes[i].totalWait = 0;
		lanes[i].currentIdle = 0;
		lanes[i].totalIdle = 0;
		lanes[i].totalCustomers = 0;
		lines[i] = create();	//initialize each queu in the array

	}

	while( /*! checkSubs( lines, checkQty ) ||*/ ! isEmpty (custQ)/* loopCount < 1000*/ )
	{
		if(! isEmpty(custQ) )
		{
			temp = take(custQ);

			//printf("arrival: %d\tservice: %d\n", temp.arrival, temp.service);

			loopCount = temp.arrival;

			chosenQ = findNextQueue( lines , checkQty ); // choosese queue
			add(&lines[chosenQ], temp ); //taken from main queue and moved to queue array

			printf("lane %d\tsize: %d\n", chosenQ+1, lines[chosenQ].qSize);
		}

	/*	for( i = 0 ; i < checkQty ; i++ )
		{
			if( lanes[i].nextAvailable <= loopCount && loopCount != 0)
			{
				if( lines[i].qSize > 0 )
				{
					innerTemp = take(&lines[i]);
					diff = lanes[i].nextAvailable - innerTemp.arrival;

					if( diff > 0 )
					{
						lanes[i].currentWait = diff;
						lanes[i].totalWait += lanes[i].currentWait;
						lanes[i].nextAvailable += innerTemp.service;
					}
					else
					{
						lanes[i].currentIdle = diff * -1;
						lanes[i].totalIdle += lanes[i].currentIdle;
						lanes[i].nextAvailable = innerTemp.arrival + innerTemp.service;
					}
					lanes[i].currentCust = innerTemp;
					lanes[i].totalCustomers++;
					printf("Lane: %-3d\tCustomer Wait: %3d\tNext Available: %-4d\tCustomers Served: %-3d\tWaiting: %-3d\n", i+1, lanes[i].currentWait, lanes[i].nextAvailable, lanes[i].totalCustomers, lines[i].qSize);
				}
			}
		}*/

//		printf("Lane: %-4d\tArrival: %d\tService: %d\n", chosenQ+1, lines[chosenQ].back->cust.arrival, lines[chosenQ].back->cust.service);

		loopCount++;

//		printf("loop Count: %d\n", loopCount);
		
	}
	
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

	printf("\n");
}


