/* ************************************************************************ *
 * checkout.c
 * Driver program for checkout lanes
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "queue.h"
//#include "lanes.h"
#include "proto.h"


// Main program
int main (int argc, char *argv[])
{
// variables for command line arguments don't think I need lfnd etc , but they were in the example
	int opt, lCount = 10, cCount = 250, maxS = 400, minS = 100, avgA = 60;
	int lfnd, cfnd, mfnd, nfnd, afnd;

	if(argc > 1)
	{
		while((opt = getopt(argc, argv, "l:c:m:n:a:")) != -1)
		{
			switch(opt)
			{
			case 'l':
				lCount = atoi(optarg);
				lfnd = 1;
				break;
			case 'c':
				cCount = atoi(optarg);
				cfnd = 1;
				break;
			case 'm':
				maxS = atoi(optarg);
				mfnd = 1;
				break;
			case 'n':
				minS = atoi(optarg);
				nfnd = 1;
				break;
			case 'a':
				avgA = atoi(optarg);
				afnd = 1;
				break;
			case '?':
				fprintf(stderr,"Usage: %s [-l lanes nLanes] [-c customers nCustomers] [-m maxService nMax] [-n minService nMin] [-a averageArrival nAvg]\n", argv[0]);
				exit(EXIT_FAILURE);
			}
		
		}
		
	}


	queue custQ;
	customerT cust;
	int count = cCount ;
	int i = 0;
	int laneCount = lCount;

	custQ = create();

	createFile(count, minS, maxS, avgA); // create the customers file with count customers, minS minimum service, maxS max and avgA for average arrival

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



	multiLineSim( &custQ, laneCount); // run sim for customer going to shortest available line


	printf("\nLanes: %-3d  Customers: %d\tMax Service Time: %d\tMin Service Time: %d\tAverage Arrival: %d\n\n", lCount, cCount, maxS, minS, avgA);
	




   return 0;
}
