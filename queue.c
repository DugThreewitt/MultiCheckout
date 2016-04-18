/* ************************************************************************ *
 * queue.c
 * Linked List queue for checkout.c
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "queue.h"
//#include "proto.h"

/* **********************************************************************
 * Function: create()
 * inputs: none
 * outputs: queue
 * purpose: initialize the queue
 * *********************************************************************/

queue create()
{
	queue custQ;
//	customerT cust;
//	cust.arrival = 0;
//	cust.service = 0;

	custQ.front = (node *)malloc(sizeof(node));
	//custQ.front -> cust = cust;
	custQ.front -> next = NULL;
	custQ.back = custQ.front;
	custQ.qSize = 0;

	return custQ;
	
}


/* **********************************************************************
 * Function: isEmpty()
 * inputs: queue
 * outputs: int
 * purpose: returns whether the queue is empty or not
 * *********************************************************************/

int isEmpty( queue * custQ )
{
	return (custQ->qSize == 0 );
}



/* **********************************************************************
 * Function: add()
 * inputs: queue, customerT
 * outputs: node pointer
 * purpose: adds a customerT to the queue
 * *********************************************************************/

queue * add( queue* custQ, customerT  cust )
{
	
	node * newNode;
	cust.start = 0;

	newNode = (node *)malloc(sizeof(node));
	newNode->cust = cust;
	newNode->next = NULL;

	custQ->back->next = newNode;
	custQ->back = newNode;
	custQ->qSize++;

	return custQ;


}

/* **********************************************************************
 * Function: take()
 * inputs: queue
 * outputs: customerT 
 * purpose: Removes a customer from the queue
 * *********************************************************************/

customerT take (  queue *  custQ )
{

//	int val = custQ.front->val;
//	node * temp = custQ->front;

	if (custQ->qSize == 0)
	{
		//printf("queue is empty\n");
		return ;
	}

/*	if(custQ->front = custQ->back = NULL)
	{
		custQ->qSize--;
		return temp->cust;
	}
	else
	{
		cu
*/	
		customerT cust = custQ->front->cust;	
		custQ->front = custQ->front->next;
		custQ->qSize--;
		return cust;
/*	}
	free(temp); */
}
/*
customerT front (queue *  custQ)
{
	if( custQ->qSize == 0 )
	{
		customerT cust; // needed this to avoid seg faults when empty
		cust.arrival = -1;

		printf("queue is empty\n");
//		custQ.back->cust.arrival = -1;
		return cust;
	}
	
	return custQ->front->cust;
}
*/
