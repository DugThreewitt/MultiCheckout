/* ************************************************************************ *
 * lanes.c
 * take a number style checkout for checkout.c
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
 * Function: singleLineSim()
 * inputs: queue pointer
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
	customerT discard;
	custQ = take(custQ);


	temp = front(custQ);
	temp.start = 0;

	for( i ; i < checkQty ; i++)
	{
		lanes[i].totalCustomers =  0 ;
		lanes[i].lineLength =  0 ;
		lanes[i].currentIdle =   0 ;
		lanes[i].totalIdle =  0 ;
		lanes[i].currentWait =  0 ;
		lanes[i].totalWait =  0 ;
		lanes[i].totalCustomers =  0 ;
		lanes[i].nextAvailable = 0;
		

	}

	while( checkSubs() != 0 )
	{
//		custQ = take(custQ);


		if(temp.arrival == loopCount) //customer arrives
		{
			chosenQ = findNextQueue( lines , checkQty ); // choosese queue
			add(&lines[chosenQ], take(custQ)); //taken from main queue and moved to queue array
		}
		
		for( i = 0 ; i < checkQty ; i++ )
		{
			ready = lanes[i].nextAvailable; //finds when checkout i is ready
			
			innerTemp = front(lines[i]); // creates temp from front of queue array i to check out

			if ( innerTemp.arrival >= ready ) // if they arrive after the cashier is ready
			{
					
				lanes[i].nextAvailable += innerTemp.arrival + innerTemp.service; //set cashier next ready
				lanes[i].currentCust = innerTemp;//move customer to checkout
				discard=take(lines[i]); // take them from the first position
				free(discard); // frees discard memory
				continue; //continues to next iteration
			}
			else if(innerTemp.start >= ready) // checks start time of innerTemp(set to 0 outsizde of loop
			{
				lanes[i].nextAvailable = temp.start + temp.service; //set cashier next ready
				lanes[i].currentCust = innerTemp;//move customer to checkout
				discard=take(lines[i]);// takes them from first position
				free(discard); // frees memory
			 	continue; //continues to next iteration	
			}
			else
			{
				innerTemp.start = ready; // sets start time to ready of this cashier
			}
		}
/*		
		printf("Lane: %3d\tArrival: %-5d\tService: %-3d\tNext Available: %-6d\t", next+1, temp.arrival, temp.service, lanes[next].nextAvailable);
		printf("wait: %-3d\tidle: %-3d\ttWait: %d\ttIdle: %d\n", lanes[next].currentWait, lanes[next].currentIdle,lanes[next].totalWait, lanes[next].totalIdle);
*/		
		count++;
	}
/*	
	for( i = 0 ; i < laneSize ; i++ )
	{
		allWait += lanes[i].totalWait;
		allIdle += lanes[i].totalIdle;
		allCust += lanes[i].totalCustomers;
	}
	
	avgIdle = (float)allIdle / (float)allCust;
	avgWait = (float)allWait / (float)allCust;

	printf("\nSingle Line report:\n\n");
	printf("Total Customers Served: %-4d\t\tAverage Total Wait Time: %7.2f\tAverage Cashier Idle Time: %7.2f\n\n", allCust, avgWait, avgIdle);
	
	for( i = 0 ; i < laneSize ; i++ )
	{
		avgLIdle = (float)lanes[i].totalIdle / (float)lanes[i].totalCustomers;
		avgLWait = (float)lanes[i].totalWait / (float)lanes[i].totalCustomers;

		printf("Lane %-5d:\tTotal Customers: %-6d\tAverage Wait Time: %7.2f\tAverage Cashier Idle Time: %7.2f\n", (i+1), lanes[i].totalCustomers, avgLWait, avgLIdle);
	}
*/
	printf("\n");
}


