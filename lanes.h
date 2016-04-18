/* ************************************************************************ *
 * lanes.h
 * structures for lanes.c
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */
#include "types.h"
#include "queue.h"

#ifndef LANES_H_
#define LANES_H_

typedef struct
{
	int totalCustomers;
	int lineLength;
	int currentIdle;
	int totalIdle;
	int nextAvailable;
	int currentWait;
	int totalWait;
	customerT currentCust;
} laneT;

int findNextLane ( laneT * lanes , int size );
void singleLaneSim ( queue * custQ , int size );
void multiLineSim( queue * custQ , int checkQty );
int checkSubs( queue qArr [] , int arrSize );
int findNextQueue( queue qArr [] , int arrSize );


#endif
