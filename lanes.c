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
 * Function: findNextLane()
 * inputs: laneT type array
 * outputs: array element with the lowest next arrival
 * purpose: find the next lane that will be open
 * *********************************************************************/

int findNextLane( laneT * lanes, int laneSize )
{
	int i = 0;
	int testNum = 0; 

	for( i ; i < laneSize ; i++ )
	{
		if( lanes[i].nextAvailable < lanes[testNum].nextAvailable )
		{
			testNum = i;
		}
	}

	return testNum;
	
}


/* **********************************************************************
 * Function: singleLineSim()
 * inputs: queue pointer
 * outputs: 
 * purpose: simulates take a number style checkout lanes
 * *********************************************************************/

void singleLineSim( queue * custQ , int laneSize )
{
	laneT lanes[laneSize];
	int next;
	int i = 0;
	int allWait = 0;
	int allIdle = 0;
	int allCust = 0;
	int diff = 0;
	float avgIdle, avgWait, avgLIdle, avgLWait;
	customerT temp ;
	//temp = take(custQ);
	custQ = take(custQ);

	for( i ; i < laneSize ; i++)
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

	while( custQ->qSize != 0 )
	{
//		custQ = take(custQ);

		temp = front(custQ);
		next = findNextLane( lanes , laneSize );
		
		diff = lanes[next].nextAvailable - temp.arrival;

		if ( diff > 0 )
		{
			lanes[next].currentWait = diff; 
			lanes[next].currentIdle = 0;
			lanes[next].nextAvailable += temp.service;
		}
		else
		{
			lanes[next].currentWait = 0;
			lanes[next].currentIdle = (diff * -1);
			lanes[next].nextAvailable = temp.arrival + temp.service;
		}

		lanes[next].totalIdle += lanes[next].currentIdle;
		lanes[next].totalWait += lanes[next].currentWait;

//		lanes[next].nextAvailable += (temp.arrival + temp.service);

		lanes[next].currentCust = temp;
		lanes[next].totalCustomers++;
/*		
		printf("Lane: %3d\tArrival: %-5d\tService: %-3d\tNext Available: %-6d\t", next+1, temp.arrival, temp.service, lanes[next].nextAvailable);
		printf("wait: %-3d\tidle: %-3d\ttWait: %d\ttIdle: %d\n", lanes[next].currentWait, lanes[next].currentIdle,lanes[next].totalWait, lanes[next].totalIdle);
*/		
		custQ = take(custQ);	
		//free(temp);
	}
	
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

	printf("\n");
}


