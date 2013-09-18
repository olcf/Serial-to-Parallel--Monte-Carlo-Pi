#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
#include <omp.h>

int main(int argc, char* argv[])
{
	int niter = 100000;					//number of iterations per FOR loop
	int myid;						//hold's process's rank id
	double x,y;						//x,y value for the random coordinate
	int i;							//loop counter
        int count=0;						//Count holds all the number of how many good coordinates
	double z;						//Used to check if x^2+y^2<=1
	double pi;						//holds approx value of pi
	int reducedcount;					//total number of "good" points from all nodes
	int reducedniter;					//total number of ALL points from all nodes
	int ranknum = 0;					//total number of nodes available
	MPI_Init(&argc, &argv);					//Start MPI
	double start = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);			//get rank of node's process
	MPI_Comm_size(MPI_COMM_WORLD, &ranknum);		//Gets number of nodes availible to process
	int a = 0;
	double avgpi = 0;
	for(a = 0; a<50; a++)
	{
		if(myid != 0)						//Do the following on all except the master node
		{
			//Start OpenMP code: 16 threads/node
			#pragma omp parallel firstprivate(x, y, z, i) reduction(+:count) num_threads(16)
			{
				/*random() was used here because it is supposed to give a more random/cryptographically
					 * better random number so that it increases the randomness of the points which should 
				 * increase the accuacy of the result by at least a small degree*/
	
				srand48((int)time(NULL) ^ omp_get_thread_num());	//Give random() a seed value
				for (i=0; i<niter; ++i)				//main loop
				{
					x = (double)drand48();//RAND_MAX;		//gets a random x coordinate
					y = (double)drand48();//RAND_MAX;		//gets a random y coordinate
					z = ((x*x)+(y*y));			//Checks to see if number is inside unit square
					if (z<=1)
					{
						++count;			//if it is, consider it a valid random point	
					}	
				}
			
				//print the value of each thread/rank
			} 
		}
		MPI_Barrier(MPI_COMM_WORLD);
		/*Use MPI_Reduce() to get all the values of count and add them together (MPI_SUM) and return it to
		 * reducedcount
		 * The reason MPI_Reduce is used here is because its a more streamlined way of gathering together all count data
		 * into one variable and performing an operation on it. Its also possible to use MPI_Send() and MPI_Recv(), but
		 * it tends to make the code less readable in my opinion, though it could possibly make it faster since its not
			 * an all-to-one communication like MPI_Reduce() is; while MPI_Send() and MPI_Recv() is a one to one 
		 * comm	unication */
		MPI_Reduce(&count, &reducedcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		/*Since, from the point of view of the code, you know the number of iterations per loop/thread/node is, you can
		 * calculate it without using an MPI routine like above. 
		 * 16 threads with niter iterations each on (the number of nodes - the master node) nodes */
	
		reducedniter = 16*niter*(ranknum-1);					
		MPI_Barrier(MPI_COMM_WORLD);
		if (myid == 0)						//if root process/master node
		{
		    	//p = 4(m/n) | Compute the ratio of good hits to bad hits (monte carlo)
			pi = ((double)reducedcount/(double)reducedniter)*4.0;
			//Print the calculated value of pi
			printf("Pi: %f\n", pi);			
			avgpi += pi;
			printf("Avgpi: %f\n", avgpi);
			pi = 0;
			reducedcount = 0;
		}
		count = 0;	
		
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(myid==0)
	{
		avgpi = avgpi/50;
		printf("Average pi over 50 iterations per node: %f\n", avgpi);
	}
	double end = MPI_Wtime();
	double time = end-start;
	printf("Time elapsed: %f\n", time);

	MPI_Finalize();						//Close the MPI instance
	return 0;
}
