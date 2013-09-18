#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	double start = MPI_Wtime();
	int niter = 100000;					//number of iterations per FOR loop
	double x,y;						//x,y value for the random coordinate
	int i;							//loop counter
        int count=0;						//Count holds all the number of how many good coordinates
	double z;						//Used to check if x^2+y^2<=1
	double pi;						//holds approx value of pi
	int a = 0;
	double avgpi = 0;
	for(a = 0; a<50; a++)
	{
		#pragma omp parallel firstprivate(x, y, z, i) reduction(+:count) num_threads(16)
		{
			srand48((int)time(NULL) ^ omp_get_thread_num());	//Give random() a seed value
			for (i=0; i<niter; ++i)				//main loop
			{
				x = (double)drand48();//(double)RAND_MAX;		//gets a random x coordinate
				y = (double)drand48();//(double)RAND_MAX;		//gets a random y coordinate
				z = ((x*x)+(y*y));			//Checks to see if number is inside unit square
				if (z<=1)
				{
					++count;			//if it is, consider it a valid random point	
				}	
			}
		} 
		pi = ((double)count/(double)(niter*16))*4.0;
		printf("Pi: %f\n", pi);
		avgpi += pi;
		pi = 0;
		count = 0;
		printf("Avgpi: %f\n", avgpi);
	}
	avgpi = avgpi/50;
	printf("Average pi over 50 operations: %f\n", avgpi);
	double end = MPI_Wtime();
	double time = end-start;
	printf("Elapsed time: %f\n", time);
	return 0;
}
