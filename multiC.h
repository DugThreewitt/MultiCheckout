/* ************************************************************************ *
 * multiC.h
 * header file for multiC.c go to the shortest line for checkout for checkout.c
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */

#include "types.h"
#include "queue.h"
#include "proto.h"

#ifndef MULTIC_H_
#define MUTLIC_H_
/* **********************************************************************
 * Function: findNextQueue()
 * inputs: Array of queues
 * outputs: array element with smallest queue size
 * purpose: find the shortest queue
 * *********************************************************************/

int findNextQueue( queue qArr [] , int arrSize );


/* **********************************************************************
 * Function: checkSubs()
 * inputs: Array of queues
 * outputs: int 0 if all queues in arrar are empty
 * purpose: check if all sub arrays are empty
 * *********************************************************************/

int checkSubs( queue qArr [] , int arrSize );

/* **********************************************************************
 * Function: multiLineSim()
 * inputs: queue pointer, and lane quantity
 * outputs: 
 * purpose: simulates take a number style checkout lanes
 * *********************************************************************/

void multiLineSim( queue * custQ , int checkQty );

#endif
