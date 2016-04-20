/* ************************************************************************ *
 * func.c
 * functions for checkout.c
 * Dug Threewitt - dstgh6
 * CS2750 - Mon/Wed
 * *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
//#include "proto.h"


/* **********************************************************************
 * Function: popCustomer()
 * inputs: none
 * outputs: customerT
 * purpose: initialize customer variables 
 * *********************************************************************/
/*
customerT popCustomer()
{
	customerT cust;

	srand( time( NULL));
	
	cust.arrival = (rand() %  120) ;
	cust.service = (100 + (rand() % 300));

	return cust;

}


* **********************************************************************
 * Function: createFile()
 * inputs: int  
 * outputs: none
 * purpose: create a file filled with customers
 * *********************************************************************/

void createFile (int x, int min, int max, int avg)
{
	FILE * fd;
	int i = 0;
	customerT cust;
	srand( time( NULL));
	int arr = 0;

	if ( ( fd = fopen ("customers", "w+") ) == NULL)
	{
		printf("File could not be opened!\n");
		exit(1);
	}

	for( i ; i < x ; i++ )
	{
		cust.arrival = arr;
		cust.service = (min + (rand() % (max-min)));


		fprintf(fd, "%d %d\n", cust.arrival, cust.service);

		arr += rand() % (avg * 2);
	}
	
	
	fclose(fd);

}


// tried to use this, but it would seg fault, so I kept it in the main checkout.c program
/* **********************************************************************
 * Function: readFile()
 * inputs: non0e
 * outputs: queue
 * purpose: reads customerT from the file
 * *********************************************************************/
/*
queue * readFile()
{
	FILE * fd;
	queue custQ;
	customerT cust;
	
	custQ = create();

	if ( ( fd = fopen( "customers", "r") ) == NULL )
	{
		printf("The file could not be opened! exiting . . .\n");
		exit(1);
	}

	while ( ! feof( fd) )
	{
		fscanf(fd, "%d", &cust.arrival);
//		cust.arrival = atof(temp);
		fscanf(fd, "%d", &cust.service);
//		cust.service = atof(temp);
		add(custQ, cust);
	}

	fclose( fd );

	return custQ;
}
*/

