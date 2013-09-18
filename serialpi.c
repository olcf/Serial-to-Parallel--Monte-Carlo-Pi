#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"

void main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	double wallStart = MPI_Wtime();
	double niter = 100000;
	double x,y;						//x,y value for the random coordinate
	int i;
        int count=0;						//Count holds all the number of how many good coordinates
	double z;						//Used to check if x^2+y^2<=1
	double pi;						//holds approx value of pi
	int a = 0;
	double avgpi = 0;
	time_t t;
	for(a = 0; a<50; a++)
	{
		srand48(((unsigned)time(&t)));				//Give rand() a seed value
	
		for (i=0; i<=niter; ++i)					//main loop
		{
			x = (double)drand48();//RAND_MAX;			//gets a random x coordinate
			y = (double)drand48();//RAND_MAX;			//gets a random y coordinate
			z = ((x*x)+(y*y));				//Checks to see if number in inside unit square
			if (z<=1)
			{
				++count;				//if it is, consider it a valid random point	
			}	
		}			
		pi = ((double)count/(double)niter)*4.0;				//p = 4(m/n)
		printf("Pi: %f\n", pi);			
		avgpi += pi;
		printf("avgpi: %f\n", avgpi);
		count = 0;
	}
	avgpi = avgpi/50;
	printf("Average pi: %f\n", avgpi);
	double wallEnd = MPI_Wtime();
	double elapsed = wallEnd-wallStart;
	printf("Seconds elapsed: %f\n", elapsed);
	MPI_Finalize();
}
