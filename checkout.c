/* ************************************************************************ *
 * checkout.c
 * Driver program for checkout lanes
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "queue.h"
//#include "lanes.h"
#include "proto.h"


// Main program
int main ()
{

	queue custQ;
	customerT cust;
	int count = 250 ;
	int i = 0;
	int laneCount = 10;

	custQ = create();

	createFile(count);

	FILE * fd;
	
	if ( ( fd = fopen( "customers", "r") ) == NULL )
	{
		printf("The file could not be opened! exiting . . .\n");
		exit(1);
	}

	while ( ! feof( fd) )
	{
		fscanf(fd, "%d", &cust.arrival);
		fscanf(fd, "%d", &cust.service);
		add(&custQ, cust);
	}

	fclose( fd );
	//custQ = readFile( &custQ );


	//custQ=take(custQ);

//	singleLineSim( &custQ, laneCount );
	multiLineSim( &custQ, laneCount);
/*
	for( i = 0 ; i < count ; i++)
	{
		cust = front(custQ);
		printf("Current arrival: %5d\tservice:%5d\n", cust.arrival, cust.service);
		custQ = take(custQ);
	}
*/	
	




   return 0;
}
