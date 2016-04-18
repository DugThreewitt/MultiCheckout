/* ************************************************************************ *
 * queue.h
 * structures for queue.c
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */
#include "types.h"

#ifndef QUEUE_H_
#define QUEUE_H_


typedef struct listNode
{
	customerT cust;
	struct listNode *next;
} node;

typedef struct
{
	node *front;
	node *back;
	int qSize;
} queue;

queue create();
queue * add ( queue * custQ , customerT cust);
customerT take ( queue * custQ );
customerT front( queue * custQ );
int isEmpty( queue * custQ );


#endif
