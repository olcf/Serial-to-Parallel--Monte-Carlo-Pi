#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int niter = 100000;
	int myid;						//hold's process's rank id
	double x,y;						//x,y value for the random coordinate
	int i;
        int count=0;						//Count holds all the number of how many good coordinates
	double z;						//Used to check if x^2+y^2<=1
	double pi;						//holds approx value of pi
	int reducedcount;					//total number of "good" points from all nodes
	int reducedniter;					//total number of ALL points from all nodes

	MPI_Init(&argc, &argv);					//Start MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);			//get rank of node's process

	if(myid != 0)
	{
		srand48(time(NULL));				//Give rand() a seed value
		for (i=0; i<niter; ++i)					//main loop
		{
			x = (double)drand48();//RAND_MAX;			//gets a random x coordinate
			y = (double)drand48();//RAND_MAX;			//gets a random y coordinate
			z = ((x*x)+(y*y));				//Checks to see if number in inside unit circle
			if (z<=1)
			{
				++count;				//if it is, consider it a valid random point	
			}	
		}			
	}	

	MPI_Reduce(&count, &reducedcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&niter, &reducedniter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	reducedniter -= niter;					//to compensate for no loop on master node

	if (myid == 0)						//if root process
	{      
		pi = ((double)reducedcount/(double)reducedniter)*4.0;				//p = 4(m/n)
		printf("Pi: %f\n", pi);			
	}
	MPI_Finalize();						//Close the MPI instance
	return 0;
}
