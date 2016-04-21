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
	int empty = 11; 

	for( i ; i < arrSize ; i++ )
	{
		if( qArr[i].qSize != 0 )
		{
			empty = i;
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
	int test = 0;
	int i = 0;
	int allWait = 0;
	int allIdle = 0;
	int allCust = 0;
	int allLine = 0;
	int diff = 0;
	int startCust;
	float avgIdle, avgWait, avgLIdle, avgLWait, avgLine, avgLLine;
	customerT temp, innerTemp, discard;
	
	temp = take(custQ);
	innerTemp.arrival =  0;
	innerTemp.service = 0;
	innerTemp.start = 0;




	for( i ; i < checkQty ; i++) // intialize values as needed
	{
		lanes[i].nextAvailable = 0 ;
		lanes[i].currentWait = 0;
		lanes[i].totalWait = 0;
		lanes[i].currentIdle = 0;
		lanes[i].totalIdle = 0;
		lanes[i].currentCust.arrival = 0;
		lanes[i].currentCust.service = 0;
		lanes[i].lineWait = 0;
		lanes[i].totalLineWait = 0;
		lanes[i].totalCustomers = 0;
		lines[i] = create();	//initialize each queu in the array
		discard = take(&lines[i]); // get rid of junk customer
	}

	while( checkSubs( lines, checkQty ) != 11 || ! isEmpty (custQ)  )
	{
		if(! isEmpty(custQ) )
		{
			temp = take(custQ);

			loopCount = temp.arrival;

			chosenQ = findNextQueue( lines , checkQty ); // chooses queue
			add(&lines[chosenQ], temp ); //taken from main queue and moved to queue array
			discard = take(&lines[chosenQ]); // removes junk at beginning of array[chosenQ] queu
			add(&lines[chosenQ], temp);
			startCust = custQ->qSize; // counts to see how many customers are remaining
		}

		for( i = 0 ; i < checkQty ; i++ )
		{
			

			if( lanes[i].nextAvailable <= loopCount && loopCount != 0)
			{

				if( lines[i].qSize > 0 )
				{
					innerTemp = take(&lines[i]);

					lanes[i].currentCust = innerTemp;
					lanes[i].totalCustomers++;

					diff = lanes[i].nextAvailable - innerTemp.arrival;

					if( diff > 0 )
					{
						lanes[i].currentWait = diff;
						lanes[i].lineWait = diff + innerTemp.service;
						lanes[i].totalLineWait += lanes[i].lineWait;
						lanes[i].totalWait += lanes[i].currentWait;
						lanes[i].nextAvailable += innerTemp.service;
					}
					else
					{
						lanes[i].currentIdle =( diff * -1 );
						lanes[i].lineWait = innerTemp.service;
						lanes[i].totalLineWait += lanes[i].lineWait;
						lanes[i].totalIdle += lanes[i].currentIdle;
						lanes[i].nextAvailable = innerTemp.arrival + innerTemp.service;
					}


					printf("Lane: %-2d   Total Wait: %-3d    Average Total Wait: %6.2f    Line Wait : %-4d    Average Line Wait: %6.2f    Current Idle: %-5d    Average Idle: %7.2f    Customers Served: %-4d    Customers Waiting: %-4d\n",i+1, lanes[i].lineWait, (float)lanes[i].totalLineWait/(float)lanes[i].totalCustomers, lanes[i].currentWait,(float)lanes[i].currentWait/(float)lanes[i].totalCustomers,lanes[i].currentIdle,(float)(lanes[i].totalIdle/lanes[i].totalCustomers),  lanes[i].totalCustomers, startCust, lanes[i].nextAvailable);
				}

			}
		}
			
		loopCount++;

	}
	
	for( i = 0 ; i < checkQty ; i++ )
	{
		allWait += lanes[i].totalWait;
		allIdle += lanes[i].totalIdle;
		allLine += lanes[i].totalLineWait;
		allCust += lanes[i].totalCustomers;
	}
	
	avgIdle = (float)allIdle / (float)allCust;
	avgWait = (float)allWait / (float)allCust;
	avgLine = (float)allLine / (float)allCust;

	printf("\nShortest Line report:\n\n");
	printf("Total Customers Served: %-4d\tAverage Line Wait Time %7.2f\t    Average Total Wait Time: %7.2f\tAverage Cashier Idle Time: %7.2f\n\n", allCust, avgWait, avgLine, avgIdle);
	
	for( i = 0 ; i < checkQty ; i++ )
	{
		if(lanes[i].totalCustomers == 0)
		{
			avgLIdle = 0;
			avgLLine = 0;
			avgLWait = 0;
		}
		else
		{
			avgLIdle = (float)lanes[i].totalIdle / (float)lanes[i].totalCustomers;
			avgLWait = (float)lanes[i].totalWait / (float)lanes[i].totalCustomers;
			avgLLine = (float)lanes[i].totalLineWait / (float)lanes[i].totalCustomers;
		}

		printf("Lane %-5d:\tTotal Customers: %-6d\tAverage Wait Time: %7.2f\tAverage Total Wait: %7.2f\tAverage Cashier Idle Time: %7.2f\n", (i+1), lanes[i].totalCustomers, avgLWait, avgLLine, avgLIdle);
	}

	printf("\n");
}


